function(music_plugins_project)

    set(external_project music-plugins)

    list(APPEND ${external_project}_dependencies
        dtk
        ITK
        VTK
        DCMTK
        medInria
        mmg
        tetgen
        eigen
        qwt
        quazip
        zlib
        )

    if (${USE_RealTimeWorkspace})
        list(APPEND ${external_project}_dependencies
            jsoncons
            asio
            websocketpp
            openssl
        )
    endif()

    if (USE_Python)
        list(APPEND ${external_project}_dependencies
            pyncpp
            )
    endif()

    EP_Initialisation(${external_project}
        USE_SYSTEM OFF
        BUILD_SHARED_LIBS ON
        REQUIRED_FOR_PLUGINS ON
        )

    if (NOT USE_SYSTEM_${external_project})

        set(git_url ${GITHUB_PREFIX}Inria-Asclepios/music.git)
        set(git_tag master)

        set(cmake_args
            ${ep_common_cache_args}
            -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE_medInria}
            -DCMAKE_INSTALL_PREFIX:PATH=<INSTALL_DIR>
            -DBUILD_SHARED_LIBS:BOOL=${BUILD_SHARED_LIBS_${external_project}}
            -DQt5_DIR=${Qt5_DIR}
            -Ddtk_DIR:FILEPATH=${dtk_DIR}
            -DITK_DIR:FILEPATH=${ITK_DIR}
            -DVTK_DIR:FILEPATH=${VTK_DIR}
            -DDCMTK_DIR:FILEPATH=${DCMTK_DIR}
            -DmedInria_DIR:FILEPATH=${medInria_DIR}
            -DBoost_INCLUDE_DIR=${Boost_INCLUDE_DIR}
            -Djsoncons_DIR:FILEPATH=${jsoncons_DIR}
            -Dasio_DIR:FILEPATH=${asio_DIR}
            -Dwebsocketpp_DIR:FILEPATH=${websocketpp_DIR}
            -Dopenssl_DIR:FILEPATH=${openssl_DIR}
            -DOPENSSL_ROOT_DIR:FILEPATH=${OPENSSL_ROOT_DIR} 
            -DOPENSSL_BUILD:FILEPATH=${OPENSSL_BUILD}
            -DEIGEN_INCLUDE_DIR:FILEPATH=${eigen_INCLUDE_DIR}
            -DQWT_INCLUDE_DIR:FILEPATH=${qwt_INCLUDE_DIR}
            -DQWT_DIR:FILEPATH=${qwt_DIR}
            -DMMG_INCDIR:FILEPATH=${mmg_INCDIR}
            -DMMG_LIBDIR:FILEPATH=${mmg_LIBDIR}
            -DTETGEN_INCLUDE_DIR:FILEPATH=${tetgen_INCLUDE_DIR}
            -DTETGEN_DIR:FILEPATH=${tetgen_DIR}
            -DQUAZIP_DIR:FILEPATH=${quazip_DIR}
            -DQUAZIP_INCLUDE_DIR:FILEPATH=${quazip_INCLUDE_DIR}
            -DZLIB_DIR:FILEPATH=${zlib_DIR}
            -DUSE_RealTimeWorkspace=${USE_RealTimeWorkspace}
            )

        if (USE_Python)
          list(APPEND cmake_args
              -Dpyncpp_DIR:PATH=${pyncpp_DIR}
              )
        endif()

        epComputPath(${external_project})
        ExternalProject_Add(${external_project}
            PREFIX ${EP_PATH_SOURCE}
            SOURCE_DIR ${EP_PATH_SOURCE}/${external_project}
            BINARY_DIR ${build_path}
            TMP_DIR ${tmp_path}
            STAMP_DIR ${stamp_path}
            GIT_REPOSITORY ${git_url}
            GIT_TAG ${git_tag}
            CMAKE_GENERATOR ${gen}
            CMAKE_GENERATOR_PLATFORM ${CMAKE_GENERATOR_PLATFORM}
            CMAKE_ARGS ${cmake_args}
            DEPENDS ${${external_project}_dependencies}
            INSTALL_COMMAND ""
            UPDATE_COMMAND ""
            BUILD_ALWAYS 1
            )

        set(EXTERNAL_PROJECT_PLUGINS_LEGACY_DIRS ${EXTERNAL_PROJECT_PLUGINS_LEGACY_DIRS} "${build_path}" PARENT_SCOPE)

        ExternalProject_Get_Property(${external_project} binary_dir)
        set(${external_project}_DIR ${binary_dir} PARENT_SCOPE)

        ExternalProject_Get_Property(${external_project} source_dir)
        set(${external_project}_SOURCE_DIR ${source_dir} PARENT_SCOPE)

    endif()

if (WIN32)
    get_property(GENERATOR_MULTI_CONFIG GLOBAL PROPERTY GENERATOR_IS_MULTI_CONFIG)
    if(${GENERATOR_MULTI_CONFIG})
        file(TO_NATIVE_PATH ${zlib_DIR} ZLIB_BIN_BASE)  
        set(CONFIG_MODE $<$<CONFIG:debug>:Debug>$<$<CONFIG:release>:Release>$<$<CONFIG:MinSizeRel>:MinSizeRel>$<$<CONFIG:RelWithDebInfo>:RelWithDebInfo>)  
        set(MED_BIN_BASE ${MED_BIN_BASE}\\${CONFIG_MODE}\\bin)  
  
        add_custom_command(TARGET ${external_project}
                           POST_BUILD
                           COMMAND for %%I in ( ${ZLIB_BIN_BASE}\\bin\\${CONFIG_MODE}\\*.dll ) do (if EXIST ${MED_BIN_BASE}\\%%~nxI (del /S ${MED_BIN_BASE}\\%%~nxI & mklink /H ${MED_BIN_BASE}\\%%~nxI %%~fI) else mklink /H ${MED_BIN_BASE}\\%%~nxI %%~fI) 
        )
    endif()
endif()

endfunction()
