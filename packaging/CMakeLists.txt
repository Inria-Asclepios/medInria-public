##############################################################################
#
# medInria
#
# Copyright (c) INRIA 2018. All rights reserved.
# See LICENSE.txt for details.
# 
#  This software is distributed WITHOUT ANY WARRANTY; without even
#  the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
#  PURPOSE.
#
################################################################################

project(MEDINRIA_PACKAGING VERSION ${MEDINRIA_SUPERBUILD_VERSION})

# Set common CPACK variables

set(CPACK_PACKAGE_NAME MUSICardio CACHE STRING "Name of the package for the superproject")
mark_as_advanced(CPACK_PACKAGE_NAME)

set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "${CPACK_PACKAGE_NAME} - medical image visualisation and processing tool")

set(CPACK_PACKAGE_DESCRIPTION 
    "${CPACK_PACKAGE_NAME} is a cardiac image visualization and processing tool developed in collaboration between INRIA and the IHU LIRYC.")

set(CPACK_PACKAGE_VENDOR  https://www.ihu-liryc.fr/fr/music/)
set(CPACK_PACKAGE_CONTACT "MUSICardio Team <music@inria.fr>")

set(CPACK_PACKAGE_VERSION_MAJOR ${${PROJECT_NAME}_VERSION_MAJOR})
set(CPACK_PACKAGE_VERSION_MINOR ${${PROJECT_NAME}_VERSION_MINOR})
set(CPACK_PACKAGE_VERSION_PATCH ${${PROJECT_NAME}_VERSION_PATCH})
set(CPACK_PACKAGE_VERSION ${${PROJECT_NAME}_VERSION})

set(CPACK_PACKAGE_DESCRIPTION_FILE "${PROJECT_SOURCE_DIR}/Description.txt")
set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_SOURCE_DIR}/LICENSE_MUSICardio.txt")
set(CPACK_RESOURCE_FILE_README "${PROJECT_SOURCE_DIR}/Readme.txt")
set(CPACK_RESOURCE_FILE_WELCOME "${PROJECT_SOURCE_DIR}/Welcome.txt")

set(CPACK_BINARY_STGZ OFF)
set(CPACK_BINARY_TBZ2 OFF)
set(CPACK_BINARY_TGZ ON)
set(CPACK_BINARY_TZ OFF)

option(CPACK_SOURCE_RPM  "Enable to build RPM source packages"  OFF)
option(CPACK_SOURCE_TBZ2 "Enable to build TBZ2 source packages" OFF)
option(CPACK_SOURCE_TGZ  "Enable to build TGZ source packages"  OFF)
option(CPACK_SOURCE_TXZ  "Enable to build TXZ source packages"  OFF)
option(CPACK_SOURCE_TZ   "Enable to build TZ source packages"   OFF)
option(CPACK_SOURCE_ZIP  "Enable to build ZIP source packages"  OFF)

set(CPACK_INSTALL_CMAKE_PROJECTS ${PROJECT_BINARY_DIR} ${PROJECT_NAME} ALL "/")

if(USE_Python)
    set(PYTHON_PLUGINS_DIR "${medInria_ROOT}/bin/python_plugins")
    make_directory("${PYTHON_PLUGINS_DIR}")

    install(DIRECTORY "${PYTHON_PLUGINS_DIR}"
        DESTINATION bin
        COMPONENT Runtime
        )
endif()

# Set cpack variables specific to the plateform

if (WIN32)
    set(WIN_PACK_DIR ${PROJECT_SOURCE_DIR}/windows)
    include(${WIN_PACK_DIR}/WindowsLaunchers.cmake)
    include(${WIN_PACK_DIR}/WindowsPackaging.cmake)
endif()

if (UNIX)
    if(APPLE)
        include(${PROJECT_SOURCE_DIR}/apple/ApplePackaging.cmake)
    else()
        include(${PROJECT_SOURCE_DIR}/linux/LinuxPackaging.cmake)
    endif()
endif()

# Include cpack modules

include (InstallRequiredSystemLibraries)
include (CPack)
