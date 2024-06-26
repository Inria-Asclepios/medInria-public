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

# Install a launcher scripts for the application with right environment variable

#   For developpers.

foreach (dir ${PRIVATE_PLUGINS_DIRS})
	set(DEV_PLUGINS_DIRS "${DEV_PLUGINS_DIRS}:${dir}/bin/plugins")
endforeach() 

foreach (dir ${PRIVATE_PLUGINS_LEGACY_DIRS})
	set(DEV_PLUGINS_LEGACY_DIRS "${DEV_PLUGINS_LEGACY_DIRS}:${dir}/bin/plugins_legacy")
endforeach()

set(LOCATE "")
set(MEDINRIA_DIR ${medInria_ROOT})

if (APPLE)
  set(MEDINRIA_BIN ${medInria_ROOT}/bin/MUSICardio.app/Contents/MacOS/MUSICardio)
else()
  set(MEDINRIA_BIN ${medInria_ROOT}/bin/MUSICardio)
endif()

set(MEDINRIA_PLUGINS_DIRS "${medInria_ROOT}/bin/plugins:${DEV_PLUGINS_DIRS}")
set(MEDINRIA_PLUGINS_LEGACY_DIRS "${medInria_ROOT}/bin/plugins_legacy:${DEV_PLUGINS_LEGACY_DIRS}")

configure_file(${CMAKE_CURRENT_LIST_DIR}/MUSICardio.sh.in ${CMAKE_BINARY_DIR}/MUSICardio.sh @ONLY)

#   For end users.

file(READ "${CMAKE_CURRENT_LIST_DIR}/locate_bin.sh" LOCATE)
set(MEDINRIA_DIR "$(locate)")

if (APPLE)
  set(MEDINRIA_BIN "\${MEDINRIA_DIR}/bin/MUSICardio.app/Contents/MacOS/MUSICardio")
else()
  set(MEDINRIA_BIN "\${MEDINRIA_DIR}/bin/MUSICardio")
endif()

set(MEDINRIA_PLUGINS_DIRS "\${MEDINRIA_DIR}/plugins:\${MEDINRIA_DIR}/bin/plugins:\${MEDINRIA_USER_PLUGINS_DIRS}")
set(MEDINRIA_PLUGINS_LEGACY_DIRS "\${MEDINRIA_DIR}/plugins_legacy:\${MEDINRIA_DIR}/bin/plugins_legacy:\${MEDINRIA_USER_PLUGINS_DIRS_LEGACY}")

configure_file(${CMAKE_CURRENT_LIST_DIR}/MUSICardio.sh.in ${CMAKE_CURRENT_BINARY_DIR}/MUSICardio.sh @ONLY)
