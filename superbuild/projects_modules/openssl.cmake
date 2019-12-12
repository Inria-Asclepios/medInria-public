function(openssl_project)

set(ep openssl)

## #############################################################################
## List the dependencies of the project
## #############################################################################

list(APPEND ${ep}_dependencies
  ""
  )
## #############################################################################
## Prepare the project
## ############################################################################# 

EP_Initialisation(${ep}
  USE_SYSTEM OFF 
  BUILD_SHARED_LIBS ON
  REQUIRED_FOR_PLUGINS OFF
  )

if (NOT USE_SYSTEM_${ep})

## #############################################################################
## Define repository where get the sources
## #############################################################################
set(git_url ${GITHUB_PREFIX}openssl/openssl.git)
set(git_tag OpenSSL_1_1_1b)
## #############################################################################
## Add specific cmake arguments for configuration step of the project
## #############################################################################

# set compilation flags
if (UNIX OR APPLE)
  if (CMAKE_COMPILER_IS_GNUCC AND CMAKE_C_COMPILER_VERSION VERSION_LESS 5.4)
    set(${ep}_c_flags "${${ep}_c_flags} -std=c99")
  else()
    set(${ep}_c_flags "${${ep}_c_flags}")
  endif()
  set(${ep}_cxx_flags "${${ep}_cxx_flags}")
endif()

set(cmake_args
	${ep_common_cache_args}
	-DCMAKE_C_FLAGS:STRING=${${ep}_c_flags}
	-DCMAKE_CXX_FLAGS:STRING=${${ep}_cxx_flags}
    -DCMAKE_SHARED_LINKER_FLAGS:STRING=${${ep}_shared_linker_flags}
    -DCMAKE_INSTALL_PREFIX:PATH=${EP_PATH_SOURCE}/../build/openssl/
  )

if(APPLE)
  set (cmake_args 
  ${cmake_args} 
  -DCMAKE_MACOSX_RPATH=OFF)
endif(APPLE)

## #############################################################################
## Add external-project
## #############################################################################
set(source_dir ${EP_PATH_SOURCE}/openssl)
#set(build_dir ${EP_PATH_SOURCE}/../build/openssl)

epComputPath(${ep})

ExternalProject_Add(${ep}
  PREFIX ${EP_PATH_SOURCE}
  SOURCE_DIR ${EP_PATH_SOURCE}/${ep}
  BINARY_DIR ${build_path}
  TMP_DIR ${tmp_path}
  STAMP_DIR ${stamp_path}

  GIT_REPOSITORY ${git_url}
  GIT_TAG ${git_tag}
  CMAKE_GENERATOR ${gen}
  CMAKE_GENERATOR_PLATFORM ${CMAKE_GENERATOR_PLATFORM}
  CMAKE_ARGS ${cmake_args}
  DEPENDS ${${ep}_dependencies}

  #CONFIGURE_COMMAND  mkdir ${build_dir} && cd  ${source_dir} &&  
  #                  ./config no-zlib  shared --prefix=${build_dir}  --openssldir=${build_dir} 

  CONFIGURE_COMMAND  cd  ${source_dir} &&  ./config no-zlib  shared --prefix=${build_path}  --openssldir=${build_path} 
  BUILD_COMMAND cd ${source_dir} &&  make install  ## might have to put 
  INSTALL_COMMAND ""
  UPDATE_COMMAND ""
  )

## #############################################################################
## Set variable to provide infos about the project
## #############################################################################

ExternalProject_Get_Property(${ep} binary_dir)
set(${ep}_DIR ${binary_dir} PARENT_SCOPE)

endif() #NOT USE_SYSTEM_ep

endfunction()
