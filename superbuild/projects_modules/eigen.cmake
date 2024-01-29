function(eigen_project)

set(ep eigen)

###############################################################################
## List the dependencies of the project
###############################################################################

list(APPEND ${ep}_dependencies "")
  
###############################################################################
## Prepare the project
############################################################################### 

set(Eigen3_ROOT "${eigen_ROOT}")

EP_Initialisation(${ep}
  USE_SYSTEM OFF 
  BUILD_SHARED_LIBS OFF
  REQUIRED_FOR_PLUGINS ON
  PACKAGE_NAME Eigen3
  )


if (NOT USE_SYSTEM_${ep})

## #############################################################################
## Define repository for sources
## #############################################################################

set(git_url ${GITLAB_PREFIX}libeigen/eigen)
set(git_tag 3.3.8)

## #############################################################################
## Check if patch has to be applied
## #############################################################################

ep_GeneratePatchCommand(${ep} ${ep}_PATCH_COMMAND eigen-3.3.8.patch)

## #############################################################################
## Add external-project
## #############################################################################
epComputPath(${ep})

set(cmake_args
    ${ep_common_cache_args}
    -DCMAKE_C_FLAGS:STRING=${${ep}_c_flags}
    -DCMAKE_CXX_FLAGS:STRING=${${ep}_cxx_flags}
    -DCMAKE_SHARED_LINKER_FLAGS:STRING=${${ep}_shared_linker_flags}
    -DCMAKE_INSTALL_PREFIX:PATH=<INSTALL_DIR>
  )

ExternalProject_Add(${ep}
  PREFIX ${EP_PATH_SOURCE}
  SOURCE_DIR ${EP_PATH_SOURCE}/${ep}
  BINARY_DIR ${build_path}
  INSTALL_DIR ${build_path}
  TMP_DIR ${tmp_path}
  STAMP_DIR ${stamp_path}
  GIT_REPOSITORY ${git_url}
  GIT_TAG ${git_tag}
  PATCH_COMMAND ${${ep}_PATCH_COMMAND}
  DEPENDS ${${ep}_dependencies}
  CMAKE_GENERATOR ${gen}
  CMAKE_GENERATOR_PLATFORM ${CMAKE_GENERATOR_PLATFORM}
  CMAKE_ARGS ${cmake_args}
)

ExternalProject_Add_Step(${ep} post_install
    DEPENDEES install
    COMMAND ${CMAKE_COMMAND} -E rm "<BINARY_DIR>/Eigen3Config.cmake"
    )

## #############################################################################
## Set variable to provide infos about the project
## #############################################################################

set(${ep}_ROOT ${build_path} PARENT_SCOPE)

endif()

endfunction()
