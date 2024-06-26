################################################################################
#
# medInria

# Copyright (c) INRIA 2013. All rights reserved.

# See LICENSE.txt for details in the root of the sources or:
# https://github.com/medInria/medInria-public/blob/master/LICENSE.txt

# This software is distributed WITHOUT ANY WARRANTY; without even
# the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
# PURPOSE.
#
################################################################################

set(TARGET_NAME medVtkInria)

## #############################################################################
## Find required
## #############################################################################

find_package(VTK REQUIRED COMPONENTS vtkRenderingVolumeOpenGL2 vtkInteractionWidgets vtkRenderingAnnotation vtkInteractionStyle vtkImagingStatistics vtkIOLegacy )
include(${VTK_USE_FILE})

find_package(OpenGL REQUIRED)

if (USE_OSPRay)
  add_definitions(-DMED_USE_OSPRAY_4_VR_BY_CPU)
  set(VTK_OSPRAY_RENDERING_LIBRARY "vtkRenderingOSPRay")
ELSE()
  set(VTK_OSPRAY_RENDERING_LIBRARY "")
endif()

## #############################################################################
## List sources
## #############################################################################

list_source_files(${TARGET_NAME}
  ${CMAKE_CURRENT_SOURCE_DIR}
  vtkImageView
  vtkWidgetsAddOn
  vtkVisuManagement
  vtkVisuManagement/lut
  medClutEditorToolBox
  )

list_header_directories_to_include(${TARGET_NAME}
  ${${TARGET_NAME}_HEADERS}
  )


## #############################################################################
## add library
## #############################################################################

add_library(${TARGET_NAME} SHARED
  ${${TARGET_NAME}_CFILES}
  )

## #############################################################################
## include directorie.
## #############################################################################

target_include_directories(${TARGET_NAME}
  PUBLIC
  ${${TARGET_NAME}_INCLUDE_DIRS}
  )

## #############################################################################
## Link
## #############################################################################

target_link_libraries(${TARGET_NAME}
  ${OPENGL_LIBRARIES}
  Qt5::Core
  Qt5::Widgets
  medCoreLegacy
  vtkCommonCore
  vtkCommonSystem
  vtkImagingColor
  vtkImagingGeneral
  vtkImagingHybrid
  vtkIOCore
  vtkIOExportOpenGL2
  vtkIOGeometry
  vtkIOImage
  vtkIOLegacy
  vtkIOXML
  vtkRenderingAnnotation
  vtkRenderingCore
  vtkRenderingOpenGL2
  vtkRenderingVolumeOpenGL2
  vtkRenderingContextOpenGL2
  ${VTK_OSPRAY_RENDERING_LIBRARY}
  vtkInteractionWidgets
  vtkInteractionStyle
  vtkFiltersExtraction
  vtkFiltersModeling
  vtkImagingStencil
  vtkFiltersGeometry
  vtksys
  )


## #############################################################################
## install
## #############################################################################

set_lib_install_rules(${TARGET_NAME} HEADERS
  ${${TARGET_NAME}_HEADERS}
  )

