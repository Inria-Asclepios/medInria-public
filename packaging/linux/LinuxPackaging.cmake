##############################################################################
#
# medInria
#
# Copyright (c) INRIA 2013. All rights reserved.
# See LICENSE.txt for details.
# 
#  This software is distributed WITHOUT ANY WARRANTY; without even
#  the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
#  PURPOSE.
#
################################################################################

# Get distribution name and architecture

execute_process(COMMAND lsb_release -a
                COMMAND grep "^Distributor ID:" 
                COMMAND sed -e "s/Distributor ID:[ \t]*//ig"
                OUTPUT_VARIABLE DISTRIBUTOR_ID
                OUTPUT_STRIP_TRAILING_WHITESPACE)
  
execute_process(COMMAND lsb_release -a
                COMMAND grep "^Release:"
                COMMAND sed -e "s/Release:[ \t]*//ig"
                OUTPUT_VARIABLE RELEASE
                OUTPUT_STRIP_TRAILING_WHITESPACE)

execute_process(COMMAND arch 
                OUTPUT_VARIABLE ARCH 
                OUTPUT_STRIP_TRAILING_WHITESPACE)
  
set(CPACK_PACKAGE_FILE_NAME 
    "${CPACK_PACKAGE_NAME}-${CPACK_PACKAGE_VERSION}-${DISTRIBUTOR_ID}_${RELEASE}-${ARCH}")
 
set(CPACK_GENERATOR "ZIP")

# Remember the linux packaging source dir
set(CURRENT_SRC_DIR ${PROJECT_SOURCE_DIR}/linux)
set(CURRENT_BIN_DIR ${PROJECT_BINARY_DIR}/linux)

# Generate CPACK_PROJECT_CONFIG_FILE
configure_file(${CURRENT_SRC_DIR}/GeneratorConfig.cmake.in
               ${CURRENT_BIN_DIR}/GeneratorConfig.cmake
               @ONLY)
set(CPACK_PROJECT_CONFIG_FILE ${CURRENT_BIN_DIR}/GeneratorConfig.cmake)

# Add postinst and prerm script
configure_file(${CURRENT_SRC_DIR}/postinst.in ${CURRENT_BIN_DIR}/postinst)
configure_file(${CURRENT_SRC_DIR}/prerm.in    ${CURRENT_BIN_DIR}/prerm)

# Generate desktop file
configure_file(${CURRENT_SRC_DIR}/MUSICardio.desktop.in ${CURRENT_BIN_DIR}/MUSICardio.desktop @ONLY)
install(FILES ${CURRENT_BIN_DIR}/MUSICardio.desktop DESTINATION .)

# Add application icon
set(ICON_SOURCE ${PROJECT_SOURCE_DIR}/../src/app/medInria/resources/MUSICardio_logo_small_light.png)
install(FILES ${ICON_SOURCE} DESTINATION . RENAME musicardio.png)

# Create a small README for the package
file(WRITE ${CURRENT_BIN_DIR}/README.txt "MUSICardio

How to run:
  ./bin/MUSICardio.sh

More info on https://mds-data.ihu-liryc.fr/tools/musicardio
")
install(FILES ${CURRENT_BIN_DIR}/README.txt DESTINATION .)

# Save the medinria-packaging install target to add it last
set(backup_CPACK_INSTALL_CMAKE_PROJECTS ${CPACK_INSTALL_CMAKE_PROJECTS})

# Add libraries to package directory
set(CPACK_INSTALL_CMAKE_PROJECTS "")
foreach(external_project ${external_projects})
    if(NOT USE_SYSTEM_${external_project} AND DEFINED ${external_project}_ROOT)

        # Special case for non CMake external projects
        if(${external_project} STREQUAL "qwt")
            install(DIRECTORY ${${external_project}_ROOT}/lib/
                    DESTINATION lib
                    FILES_MATCHING PATTERN "*.so*")
        else()
            # CMake projects
            if(BUILD_SHARED_LIBS_${external_project})
                install(CODE "
                    execute_process(
                        COMMAND ${CMAKE_COMMAND} --install ${${external_project}_ROOT} --prefix \"\${CMAKE_INSTALL_PREFIX}\"
                        OUTPUT_QUIET
                    )
                ")
            endif()
        endif()
    endif()
endforeach()

foreach(dir ${PRIVATE_PLUGINS_DIRS})
    set(CPACK_INSTALL_CMAKE_PROJECTS ${CPACK_INSTALL_CMAKE_PROJECTS} ${dir} ${dir} ALL "/bin")
endforeach()

foreach(dir ${PRIVATE_PLUGINS_LEGACY_DIRS})
    set(CPACK_INSTALL_CMAKE_PROJECTS ${CPACK_INSTALL_CMAKE_PROJECTS} ${dir} ${dir} ALL "/bin")
endforeach()

install(PROGRAMS ${CMAKE_BINARY_DIR}/superbuild/MUSICardio.sh DESTINATION bin)
install(CODE "include(${CURRENT_BIN_DIR}/PostArchiveCleanupScript.cmake)")

# force the medinria-packaging install target to run last so we can use it
# to cleanup
set(CPACK_INSTALL_CMAKE_PROJECTS ${CPACK_INSTALL_CMAKE_PROJECTS} ${backup_CPACK_INSTALL_CMAKE_PROJECTS})
