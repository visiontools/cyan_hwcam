option(ENABLE_CAM_STILLIMAGE   "Enable the StillImage virtual cam" ON)

if (ENABLE_CAM_STILLIMAGE)

    ### File lists

    file( GLOB stillimage_src "*.c" )
    file( GLOB stillimage_hdr "*.h" )

    ### Targets

    add_library( "cam_stillimage" SHARED ${stillimage_src} ${stillimage_hdr} ) 
    
    set_target_properties( cam_stillimage PROPERTIES VERSION ${cyan_hwcam_VERSION_STRING}
        SOVERSION ${cyan_hwcam_VERSION_MAJOR})

    ### Linking

    target_link_libraries( "cam_stillimage" "m" )

    ### Install 

    install( TARGETS "cam_stillimage"
        LIBRARY DESTINATION "${INSTALL_PLUGINS_PATH}" ) 

    if (BUILD_TEST)
        add_subdirectory(test)
    endif()

endif()
