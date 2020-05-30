add_executable ( test_cam_dummy cam_dummy.c)
target_link_libraries ( test_cam_dummy cyan cyan_hwcam )

add_test(NAME cam_dummy_01 COMMAND sh -c "./test_cam_dummy > output.txt")

add_test( NAME cam_dummy_01_bis 
    COMMAND ${CMAKE_COMMAND} -E compare_files ./output.txt
    ${PROJECT_SOURCE_DIR}/plugins/cam_dummy/test/reference_output/output.txt )


