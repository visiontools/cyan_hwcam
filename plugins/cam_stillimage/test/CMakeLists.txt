add_executable ( test_cam_still cam_still.c)
target_link_libraries ( test_cam_still cyan cyan_hwcam )

add_test(NAME cam_still_01 COMMAND ./test_cam_still
    ${CYAN_DATASETS_DIR}/images/lena.cyan )

# add_test( NAME cam_still_01_bis 
#     COMMAND ${CMAKE_COMMAND} -E compare_files ./output.txt
#     ${PROJECT_SOURCE_DIR}/plugins/cam_still/test/reference_output/output.txt )

