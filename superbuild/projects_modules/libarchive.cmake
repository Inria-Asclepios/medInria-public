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

set(release_url https://github.com/libarchive/libarchive/releases/download/v3.8.5/libarchive-3.8.5.tar.xz)

## #############################################################################
## Add specific cmake arguments for configuration step of the project
## #############################################################################

if (UNIX)
    set(${ep}_cxx_flags "${${ep}_cxx_flags} -w") # remove warnings
endif()

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
  -DLIBLZMA_LIBRARY_DEBUG=${LZMA_LIBRARY}
  -DLIBLZMA_LIBRARY_RELEASE=${LZMA_LIBRARY}
  -DLIBLZMA_INCLUDE_DIR=${LZMA_INCLUDE_DIR}
  -DENABLE_LZMA:BOOL=ON
  -DENABLE_LZ4:BOOL=OFF
  -DENABLE_ZSTD:BOOL=OFF
  -DENABLE_BZip2:BOOL=OFF
  -DENABLE_LIBXML2:BOOL=OFF
  -DENABLE_WIN32_XMLLITE:BOOL=OFF
  -DENABLE_XAR:BOOL=OFF
  -DENABLE_EXPAT:BOOL=OFF
  -DENABLE_ICONV:BOOL=OFF
  -DENABLE_LIBB2:BOOL=OFF
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
  URL ${release_url}
  URL_HASH SHA256=d68068e74beee3a0ec0dd04aee9037d5757fcc651591a6dcf1b6d542fb15a703
  CMAKE_GENERATOR ${gen}
  CMAKE_GENERATOR_PLATFORM ${CMAKE_GENERATOR_PLATFORM}
  CMAKE_ARGS ${cmake_args}
  DEPENDS ${${ep}_dependencies}
  UPDATE_COMMAND ""
)
# URL_HASH found with 'sha256sum libarchive-3.x.y.tar.xz' or on github in release section

## #############################################################################
## Set variable to provide infos about the project
## #############################################################################

ExternalProject_Get_Property(${ep} install_dir)
set(${ep}_ROOT ${install_dir} PARENT_SCOPE)

endif() #NOT USE_SYSTEM_ep

endfunction()
