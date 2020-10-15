function(jsoncons_project)

set(ep jsoncons)
## #############################################################################
## List the dependencies of the project
## #############################################################################
list(APPEND ${ep}_dependencies  "") 
## #############################################################################
## Prepare the project
## ############################################################################# 

EP_Initialisation(${ep}
  USE_SYSTEM OFF 
  BUILD_SHARED_LIBS OFF
  REQUIRED_FOR_PLUGINS ON
  )

if (NOT USE_SYSTEM_${ep})

## #############################################################################
## Define repository where get the sources
## #############################################################################

set(git_url ${GITHUB_PREFIX}danielaparker/jsoncons.git)
set(git_tag 0.118.0)

## #############################################################################
## Add external-project
## #############################################################################
epComputPath(${ep})

ExternalProject_Add(${ep}
  PREFIX ${EP_PATH_SOURCE}
  SOURCE_DIR ${EP_PATH_SOURCE}/${ep}
  BINARY_DIR ${build_path}
  TMP_DIR ${tmp_path}
  STAMP_DIR ${stamp_path}
  GIT_REPOSITORY ${git_url}
  GIT_TAG ${git_tag}
  DEPENDS ${${ep}_dependencies}
  UPDATE_COMMAND ""
  CONFIGURE_COMMAND ${CMAKE_COMMAND} -E echo "Jsoncons - no configure step required."
  # Nothing to build
  BUILD_COMMAND ""
  INSTALL_COMMAND ""
  )
## #############################################################################
## Set variable to provide infos about the project
## #############################################################################
set(${ep}_DIR ${EP_PATH_SOURCE}/${ep} PARENT_SCOPE)

endif() #NOT USE_SYSTEM_ep

endfunction()
