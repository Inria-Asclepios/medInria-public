function(gvirtualXRay_project) 

set(ep gvirtualXRay)

## #############################################################################
## List the dependencies of the project
## #############################################################################

list(APPEND ${ep}_dependencies)
## #############################################################################
## Prepare the project
## ############################################################################# 

EP_Initialisation(${ep}
  USE_SYSTEM OFF
  BUILD_SHARED_LIBS ON
  REQUIRED_FOR_PLUGINS OFF
)

if (NOT USE_SYSTEM_${ep})

set(LIB_EXT "dylib")  
if(UNIX)
	set(LIB_EXT "so") 
endif() 

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

message( ExternalProject_Get_Property(${TARGET_NAME} install_dir))

set(cmake_args
  ${ep_common_cache_args}
  -DCMAKE_C_FLAGS=${${ep}_c_flags}
  -DCMAKE_CXX_FLAGS=${${ep}_cxx_flags}
  -DCMAKE_SHARED_LINKER_FLAGS=${${ep}_shared_linker_flags}
  -DBUILD_TUTORIALS:bool=OFF
  -DBUILD_EXAMPLES:bool=OFF
  -DUSE_ITK:bool=OFF
  -DCMAKE_INSTALL_PREFIX:PATH=${EP_PATH_SOURCE}/../build/${ep}
 
  -DUSE_SYSTEM_ZLIB:bool=ON
  -DUSE_SYSTEM_LIBTIFF:bool=OFF
  -DUSE_LIBTIFF:bool=OFF
  -DUSE_FFTW3:bool=OFF
  -DUSE_FREETYPE:bool=OFF
  -DUSE_GDCM:bool=OFF
  -DUSE_ITK:bool=OFF
  -DUSE_assimp=OFF
)

if(UNIX) 
set(cmake_args ${cmake_args} 
  -G "Unix Makefiles"
  -DGLEW_LIBRARY_DIR="${EP_PATH_SOURCE}/../build/glew/build/lib/"
  -DCMAKE_BUILD_TYPE=RELEASE
  -DZLIB_LIBRARY_RELEASE="/lib/x86_64-linux-gnu/libz.so.1"
  -DZLIB_LIBRARY_DEBUG="/lib/x86_64-linux-gnu/libz.so.1"
)
else() 
set(cmake_args ${cmake_args}
  -DCMAKE_BUILD_TYPE=RELEASE 
  -DZLIB_LIBRARY_RELEASE="/usr/lib/libz.1.${LIB_EXT}"
  -DZLIB_LIBRARY_DEBUG="/usr/lib/libz.1.${LIB_EXT}"
)
endif()
 
## #############################################################################
## Add external-project
## ############################################################################# 
if(APPLE)
  set (cmake_args
  ${cmake_args}
  -DCMAKE_MACOSX_RPATH=OFF)
endif(APPLE)

set(patch_dir ${EP_PATH_SOURCE}/../../medInria-public/superbuild/patches)

set(source_dir ${EP_PATH_SOURCE}/${ep})

epComputPath(${ep})

ExternalProject_Add(${ep}
  PREFIX ${EP_PATH_SOURCE}
  SOURCE_DIR ${source_dir}

  BINARY_DIR ${build_path}
  TMP_DIR ${tmp_path}
  STAMP_DIR ${stamp_path} 
  
  CMAKE_GENERATOR ${gen}
  CMAKE_GENERATOR_PLATFORM ${CMAKE_GENERATOR_PLATFORM}
  CMAKE_ARGS ${cmake_args}
  DEPENDS ${${ep}_dependencies}
  DOWNLOAD_COMMAND curl -Lo gVirtualXRay-1.1.0.zip https://sourceforge.net/projects/gvirtualxray/files/1.1/gVirtualXRay-1.1.0-Source.zip/download
  DOWNLOAD_NAME   gVirtualXRay-1.1.0.zip
  PATCH_COMMAND  unzip  ${EP_PATH_SOURCE}/src/gVirtualXRay-1.1.0.zip -d ${source_dir}
  CONFIGURE_COMMAND cd ${build_path} && cmake  ${cmake_args} ${source_dir}/gvxr
  BUILD_COMMAND  cd ${build_path} && make install
  INSTALL_COMMAND ""
  UPDATE_COMMAND ""
)
## #############################################################################
## Set variable to provide infos about the project
## #############################################################################
ExternalProject_Get_Property(${ep} binary_dir)


set(${ep}_DIR ${binary_dir} PARENT_SCOPE)

endif() #NOT USE_SYSTEM_ep

endfunction()
