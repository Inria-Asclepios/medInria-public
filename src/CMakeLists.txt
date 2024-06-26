################################################################################
#
# medInria

# Copyright (c) INRIA. All rights reserved.

# See LICENSE.txt for details in the root of the sources or:
# https://github.com/medInria/medInria-public/blob/master/LICENSE.txt

# This software is distributed WITHOUT ANY WARRANTY; without even
# the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
# PURPOSE.
#
################################################################################

cmake_minimum_required(VERSION 3.19)

if(NOT DEFINED ${medInria_VERSION})
    set(medInria_VERSION 4.0.4)
endif()

project(medInria VERSION ${medInria_VERSION})

string(TOUPPER ${PROJECT_NAME} PROJECT_NAME_UP)

set(${PROJECT_NAME}_IDENTIFIER fr.inria.${PROJECT_NAME})

add_compile_definitions(
  ${PROJECT_NAME_UP}_VERSION="${${PROJECT_NAME}_VERSION}"
  ${PROJECT_NAME_UP}_IDENTIFIER="${${PROJECT_NAME}_IDENTIFIER}"
  )

## #############################################################################
## Macro
## #############################################################################

add_definitions( -DPROJECT_NAME="MUSICardio" )
add_definitions( -DPROJECT_CONTACT="music-dev@inria.fr" )

## #############################################################################
## Options
## #############################################################################

option(${PROJECT_NAME}_BUILD_TESTS
  "Build tests"
  OFF
  )
if(${PROJECT_NAME}_BUILD_TESTS)
    enable_testing()
endif()

option(${PROJECT_NAME}_BUILD_DOCUMENTATION
  "Build documentation"
  OFF
  )

option(USE_OSPRay
  "Build with OSPRay support"
  OFF
  )

if (NOT WIN32)
option(USE_FFmpeg
  "Build with FFmpeg video export support"
  OFF
  )
endif()

option(USE_Python
  "Build with Python support"
  ON
  )

## #############################################################################
## Find package
## #############################################################################

find_package(Qt5 REQUIRED COMPONENTS
  Concurrent
  Core
  Gui
  Network
  OpenGL
  Quick
  Sql
  Svg
  Test
  Widgets
  Xml
  )

find_package(dtk REQUIRED)
include_directories(${dtk_INCLUDE_DIRS})

if(USE_Python)
    find_package(pyncpp REQUIRED COMPONENTS CPP_API Qt5)
endif()

## #############################################################################
## enable c++ 17
## #############################################################################

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_MACOSX_RPATH OFF)

## #############################################################################
## Global policies
## #############################################################################

if (${CMAKE_VERSION} VERSION_GREATER_EQUAL "3.10.0")
    # Prevent warning of generated files not being moc'd
    cmake_policy(SET CMP0071 NEW)
endif()

## #############################################################################
## Additionals modules
## #############################################################################

set(${PROJECT_NAME}_CMAKE_DIR
  ${CMAKE_CURRENT_SOURCE_DIR}/cmake
  ${CMAKE_CURRENT_SOURCE_DIR}/cmake/module
  )

set(CMAKE_MODULE_PATH
  ${${PROJECT_NAME}_CMAKE_DIR}
  ${CMAKE_MODULE_PATH}
  )

include(list_source_files)
include(list_header_directories_to_include)
include(set_exe_install_rules)
include(set_lib_install_rules)
include(set_lib_properties_variables)
include(set_plugin_install_rules)
include(set_external_resources)
include(import_external_resources)

include(add_plugins)
if(APPLE)
  set(CMAKE_MACOSX_RPATH OFF)
endif()



## #############################################################################
## Qt Auto tools
## #############################################################################

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
#   Find includes in corresponding build (and source) directories
#   (nedded for generated files)
if(CMAKE_VERSION VERSION_LESS "3.7.0")
    set(CMAKE_INCLUDE_CURRENT_DIR ON)
endif()

## #############################################################################
## add definitions
## #############################################################################

if (CMAKE_CXX_COMPILER MATCHES clang)
    add_definitions(-DCLANG)
endif()

if (NOT MSVC) #TODO :why not this warings ?
  add_definitions(-Wno-write-strings)
  add_definitions(-Wformat=0)
endif()

if(NOT ${CMAKE_BUILD_TYPE} STREQUAL "Debug")
  message(STATUS "Add -DQT_NO_DEBUG")
  add_definitions(-DQT_NO_DEBUG)
endif()

## #############################################################################
## Windows specificity
## #############################################################################

if (WIN32)
  set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /LARGEADDRESSAWARE")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /MP /wd4068")
endif()

## #############################################################################
## Add subdirectory
## #############################################################################

add_subdirectory(layers)
add_subdirectory(app)
add_subdirectory(plugins)

if(${PROJECT_NAME}_BUILD_DOCUMENTATION)
  add_subdirectory(doc)
endif()

set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT medInria)

################################################################################
# Setup Configuration files
################################################################################

set_lib_properties_variables(
    medCoreLegacy
    medLog
    medRegistration
    medCore
    medImageIO
    medVtkInria
    medWidgets
    medUtilities
    medVtkDataMeshBase
    )

if(EXISTS ${CMAKE_SOURCE_DIR}/cmake/${PROJECT_NAME}Config.cmake.in)
  configure_file( ## Build tree configure file
    ${CMAKE_SOURCE_DIR}/cmake/${PROJECT_NAME}Config.cmake.in
    ${${PROJECT_NAME}_BINARY_DIR}/${PROJECT_NAME}Config.cmake
    @ONLY IMMEDIATE
    )
endif()
