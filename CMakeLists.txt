################################################################################
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

cmake_minimum_required(VERSION 3.19)

if(POLICY CMP0020)
  cmake_policy(SET CMP0020 NEW)
endif()

cmake_policy(SET CMP0074 NEW)

if(NOT DEFINED ${MEDINRIA_SUPERBUILD_VERSION})
    set(MEDINRIA_SUPERBUILD_VERSION 4.0.4)
endif()

SET(CMAKE_CXX_STANDARD 17)

project(MEDINRIA_SUPERBUILD VERSION ${MEDINRIA_SUPERBUILD_VERSION})

add_subdirectory(superbuild)
add_subdirectory(packaging)
