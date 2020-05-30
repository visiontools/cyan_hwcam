option(ENABLE_CAM_DUMMY   "Enable the Dummy virtual cam based ( for test purpose only)" ON)

if (ENABLE_CAM_DUMMY)

    ### File lists

    file( GLOB dummy_src "*.c" )
    file( GLOB dummy_hdr "*.h" )

    ### Targets

    add_library( "cam_dummy" SHARED ${dummy_src} ${dummy_hdr} ) 
    
    set_target_properties( cam_dummy PROPERTIES VERSION ${cyan_hwcam_VERSION_STRING}
        SOVERSION ${cyan_hwcam_VERSION_MAJOR})

    ### Linking

    target_link_libraries( "cam_dummy" "m" )

    ### Install 

    install( TARGETS "cam_dummy"
        LIBRARY DESTINATION "${INSTALL_PLUGINS_PATH}" ) 

    if (BUILD_TEST)
        add_subdirectory(test)
    endif()

endif()
