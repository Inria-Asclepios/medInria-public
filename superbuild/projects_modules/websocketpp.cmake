function(websocketpp_project)

set(ep websocketpp)

## #############################################################################
## List the dependencies of the project
## #############################################################################
list(APPEND ${ep}_dependencies "")  
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

set(git_url ${GITHUB_PREFIX}zaphoyd/websocketpp.git)
set(git_tag master)


## #############################################################################
## Add external-project
## #############################################################################
epComputPath(${ep})

ExternalProject_Add(${ep}
  PREFIX ${EP_PATH_SOURCE}
  SOURCE_DIR ${EP_PATH_SOURCE}/${ep}
  GIT_REPOSITORY ${git_url}
  GIT_TAG ${git_tag}
  BINARY_DIR ${build_path}
  TMP_DIR ${tmp_path}
  STAMP_DIR ${stamp_path}
  CMAKE_GENERATOR ${gen}
  CMAKE_GENERATOR_PLATFORM ${CMAKE_GENERATOR_PLATFORM}
  CMAKE_ARGS ${cmake_args}
  DEPENDS ${${ep}_dependencies}
  INSTALL_COMMAND ""
  )

## #############################################################################
## Set variable to provide infos about the project
## #############################################################################

ExternalProject_Get_Property(${ep} binary_dir)
set(${ep}_DIR ${binary_dir} PARENT_SCOPE)

## #############################################################################
## Add custom targets
## #############################################################################

endif() #NOT USE_SYSTEM_ep

endfunction()