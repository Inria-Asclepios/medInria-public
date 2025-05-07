function(libarchive_project)

set(ep libarchive)

## #############################################################################
## List the dependencies of the project
## #############################################################################

list(APPEND ${ep}_dependencies
     ZLIB
     xz)
  
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

set(git_url ${GITHUB_PREFIX}libarchive/libarchive.git)
set(git_tag v3.7.9)

## #############################################################################
## Add specific cmake arguments for configuration step of the project
## #############################################################################

set(LZMA_INCLUDE_DIR "${xz_ROOT}/include")

find_library(LZMA_LIBRARY
  NAMES lzma liblzma
  PATHS ${xz_ROOT}
  PATH_SUFFIXES lib
  NO_DEFAULT_PATH
  NO_SYSTEM_ENVIRONMENT_PATH
)

set(cmake_args
  ${ep_common_cache_args}
  -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE_externals_projects}
  -DBUILD_SHARED_LIBS=${BUILD_SHARED_LIBS_${ep}}
  -DCMAKE_C_FLAGS:STRING=${${ep}_c_flags}
  -DCMAKE_CXX_FLAGS:STRING=${${ep}_cxx_flags}
  -DCMAKE_SHARED_LINKER_FLAGS:STRING=${${ep}_shared_linker_flags}
  -DCMAKE_INSTALL_PREFIX:PATH=<INSTALL_DIR>
  -DCMAKE_PREFIX_PATH:STRING=${ZLIB_ROOT}
  -DZLIB_ROOT:PATH=${ZLIB_ROOT}
  -DLIBLZMA_LIBRARY=${LZMA_LIBRARY}
  -DLIBLZMA_INCLUDE_DIR=${LZMA_INCLUDE_DIR}
  -DENABLE_LZMA=ON
)
# LZMA is compiled through XZ

## #############################################################################
## Add external-project
## #############################################################################

epComputPath(${ep})

ExternalProject_Add(${ep}
  PREFIX ${EP_PATH_SOURCE}
  SOURCE_DIR ${EP_PATH_SOURCE}/${ep}
  BINARY_DIR ${build_path}
  INSTALL_DIR ${build_path}/install
  TMP_DIR ${tmp_path}
  STAMP_DIR ${stamp_path}
  GIT_REPOSITORY ${git_url}
  GIT_TAG ${git_tag}
  CMAKE_GENERATOR ${gen}
  CMAKE_GENERATOR_PLATFORM ${CMAKE_GENERATOR_PLATFORM}
  CMAKE_ARGS ${cmake_args}
  DEPENDS ${${ep}_dependencies}
  UPDATE_COMMAND ""
)

## #############################################################################
## Set variable to provide infos about the project
## #############################################################################

ExternalProject_Get_Property(${ep} install_dir)
set(${ep}_ROOT ${install_dir} PARENT_SCOPE)

endif() #NOT USE_SYSTEM_ep

endfunction()
