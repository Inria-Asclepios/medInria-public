function(ZLIB_project)

    set(external_project ZLIB)

    list(APPEND ${external_project}_dependencies
        )

    EP_Initialisation(${external_project}
        USE_SYSTEM OFF
        BUILD_SHARED_LIBS ON
        REQUIRED_FOR_PLUGINS OFF
        NO_CMAKE_PACKAGE
        )

    if (NOT USE_SYSTEM_${external_project})

        set(git_url ${GITHUB_PREFIX}madler/zlib.git)
        set(git_tag v1.2.11)

        set(cmake_args
            ${ep_common_cache_args}
            -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE_externals_projects}
            -DCMAKE_INSTALL_PREFIX:PATH=<INSTALL_DIR>
            -DBUILD_SHARED_LIBS:BOOL=${BUILD_SHARED_LIBS_${external_project}}
            )

        epComputPath(${external_project})

        ExternalProject_Add(${external_project}
            PREFIX ${EP_PATH_SOURCE}
            SOURCE_DIR ${EP_PATH_SOURCE}/${external_project}
            BINARY_DIR ${build_path}
            INSTALL_DIR ${build_path}
            TMP_DIR ${tmp_path}
            STAMP_DIR ${stamp_path}

            GIT_REPOSITORY ${git_url}
            GIT_TAG ${git_tag}
            CMAKE_GENERATOR ${gen}
            CMAKE_GENERATOR_PLATFORM ${CMAKE_GENERATOR_PLATFORM}
            CMAKE_ARGS ${cmake_args}
            DEPENDS ${${external_project}_dependencies}
            UPDATE_COMMAND ""
            )

        set(${external_project}_ROOT ${build_path} PARENT_SCOPE)

    endif()

endfunction()
