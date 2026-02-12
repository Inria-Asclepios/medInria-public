# cmake/FindQwt.cmake
# Find script for Qwt library
#
# This module defines:
#   Qwt::Qwt - imported target for Qwt
#   qwt_LIBRARIES - path to the Qwt library/framework
#   qwt_DLL - path to Windows dll
#   qwt_INCLUDE_DIR_SYSTEM - path to headers if qwt is used on system
#
# Variables in input:
#   qwt_ROOT - build path for Qwt
#   qwt_INCLUDE_DIR - include path for Qwt (on macOS it is recomputed from qwt_LIBRARIES)

find_package(Qt5 REQUIRED COMPONENTS Core Gui Widgets)

# First we search needed paths
# ...installed as external project
if(qwt_ROOT)
    find_library(qwt_LIBRARIES qwt
        NAMES qwt libqwt qwtd
        PATHS ${qwt_ROOT}
        PATH_SUFFIXES lib
        NO_DEFAULT_PATH
        NO_SYSTEM_ENVIRONMENT_PATH
    )
    message(STATUS "Qwt root: ${qwt_ROOT}")
    message(STATUS "Qwt include: ${qwt_INCLUDE_DIR}")

    if(WIN32)
        find_file(qwt_DLL
            NAMES qwt.dll qwtd.dll
            PATHS ${qwt_ROOT}
            PATH_SUFFIXES lib
            NO_DEFAULT_PATH
            NO_SYSTEM_ENVIRONMENT_PATH
        )
        message(STATUS "Qwt DLL: ${qwt_DLL}")
        if(NOT qwt_DLL)
            message(FATAL_ERROR "Qwt dll not found in external project installation!")
        endif()
    endif()
# ...installed on system
else()
    find_path(qwt_INCLUDE_DIR_SYSTEM
        NAMES qwt.h
        PATHS /opt/homebrew/lib/qwt.framework/Versions/Current/Headers # mac
              /usr/include                                             # linux
              ${CMAKE_PREFIX_PATH}/include                             # windows
              ${VCPKG_INSTALLED_DIR}/include                           # windows
              ${VCPKG_ROOT}/installed/${VCPKG_TARGET_TRIPLET}/include  # windows
    )
    find_library(qwt_LIBRARIES
        NAMES qwt qwt-qt6 libqwt-qt5.so
        PATHS /opt/homebrew/lib                                    # mac
              /usr/lib                                             # linux
              ${CMAKE_PREFIX_PATH}/lib                             # windows
              ${VCPKG_INSTALLED_DIR}/lib                           # windows
              ${VCPKG_ROOT}/installed/${VCPKG_TARGET_TRIPLET}/lib  # windows
    )

    if(WIN32)
        message(STATUS "CMAKE_PREFIX_PATH: ${CMAKE_PREFIX_PATH}")
        message(STATUS "VCPKG_ROOT: ${VCPKG_ROOT}")
        message(STATUS "VCPKG_TARGET_TRIPLET: ${VCPKG_TARGET_TRIPLET}")
        message(STATUS "VCPKG_INSTALLED_DIR: ${VCPKG_INSTALLED_DIR}")
        message(STATUS "CMAKE_TOOLCHAIN_FILE: ${CMAKE_TOOLCHAIN_FILE}")

        find_file(qwt_DLL
            NAMES qwt.dll qwtd.dll
            PATHS ${CMAKE_PREFIX_PATH}/bin
                  ${VCPKG_INSTALLED_DIR}/bin
                  ${VCPKG_ROOT}/installed/${VCPKG_TARGET_TRIPLET}/bin
            NO_DEFAULT_PATH
        )
        message(STATUS "Qwt DLL: ${qwt_DLL}")
        if(NOT qwt_DLL)
            message(FATAL_ERROR "Qwt dll not found on Windows!")
        endif()
    endif()

    message(STATUS "Qwt system include: ${qwt_INCLUDE_DIR_SYSTEM}")
    if(NOT qwt_INCLUDE_DIR_SYSTEM)
        message(FATAL_ERROR "Qwt headers not found on system!")
    endif()
endif()

if(NOT qwt_LIBRARIES)
    message(FATAL_ERROR "Qwt library not found!")
endif()
message(STATUS "Qwt library: ${qwt_LIBRARIES}")

# Then import Qwt module
if(APPLE AND qwt_LIBRARIES MATCHES "\\.framework$")

    set(QWT_BINARY "${qwt_LIBRARIES}/Versions/6/qwt")

    # Qwt as external project
    if(qwt_ROOT)
        execute_process(
            COMMAND install_name_tool -id "@rpath/qwt.framework/Versions/6/qwt" "${QWT_BINARY}"
            RESULT_VARIABLE install_name_result
        )
        add_library(Qwt::Qwt SHARED IMPORTED)

        set_target_properties(Qwt::Qwt PROPERTIES
            IMPORTED_LOCATION "${QWT_BINARY}"
            FRAMEWORK TRUE
            INTERFACE_INCLUDE_DIRECTORIES "${qwt_LIBRARIES}/Headers"
            INTERFACE_COMPILE_DEFINITIONS "QWT_DLL"
        )
        message(STATUS "Qwt framework include: ${qwt_LIBRARIES}/Headers")

    # System Qwt for macos
    else()
        add_library(Qwt::Qwt SHARED IMPORTED)

        set_target_properties(Qwt::Qwt PROPERTIES
            IMPORTED_LOCATION "${QWT_BINARY}"
            FRAMEWORK TRUE
            INTERFACE_INCLUDE_DIRECTORIES ${qwt_INCLUDE_DIR_SYSTEM}
            INTERFACE_COMPILE_DEFINITIONS "QWT_DLL"
        )
        message(STATUS "Qwt framework include: ${qwt_INCLUDE_DIR_SYSTEM}")
    endif()
elseif(WIN32)
    add_library(Qwt::Qwt SHARED IMPORTED)

    # Qwt as external project
    if(qwt_ROOT)
        set_target_properties(Qwt::Qwt PROPERTIES
            IMPORTED_IMPLIB "${qwt_LIBRARIES}"        # .lib
            INTERFACE_INCLUDE_DIRECTORIES "${qwt_INCLUDE_DIR}"
            INTERFACE_COMPILE_DEFINITIONS "QWT_DLL"
            IMPORTED_LOCATION "${qwt_DLL}"            # .dll
        )
    # System Qwt for Windows
    else()
        set_target_properties(Qwt::Qwt PROPERTIES
            IMPORTED_IMPLIB "${qwt_LIBRARIES}"        # .lib
            INTERFACE_INCLUDE_DIRECTORIES "${qwt_INCLUDE_DIR_SYSTEM}"
            INTERFACE_COMPILE_DEFINITIONS "QWT_DLL"
            IMPORTED_LOCATION "${qwt_DLL}"            # .dll
        )
    endif()

else() # Linux
    add_library(Qwt::Qwt SHARED IMPORTED)

    # Qwt as external project
    if(qwt_ROOT)
        set_target_properties(Qwt::Qwt PROPERTIES
            IMPORTED_LOCATION ${qwt_LIBRARIES}
            INTERFACE_INCLUDE_DIRECTORIES ${qwt_INCLUDE_DIR}
            INTERFACE_COMPILE_DEFINITIONS "QWT_DLL"
        )
    # System Qwt for linux
    else()
        set_target_properties(Qwt::Qwt PROPERTIES
            IMPORTED_LOCATION ${qwt_LIBRARIES}
            INTERFACE_INCLUDE_DIRECTORIES ${qwt_INCLUDE_DIR_SYSTEM}
            INTERFACE_COMPILE_DEFINITIONS "QWT_DLL"
        )
    endif()
endif()
