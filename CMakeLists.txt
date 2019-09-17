### CMake file for hwcam 
###
###     Author : glaconbleu@codices.org
###
###############################################################################


cmake_minimum_required (VERSION 2.6)

project (hwcam)
set (hwcam_VERSION_MAJOR 0)
set (hwcam_VERSION_MINOR 1)
set (hwcam_VERSION_PATCH 1)
set (hwcam_VERSION_STRING
	${hwcam_VERSION_MAJOR}.${hwcam_VERSION_MINOR}.${hwcam_VERSION_PATCH} )

set( CMAKE_LIBRARY_PATH ${CMAKE_LIBRARY_PATH} /lib /usr/lib /usr/local/lib )
set( CMAKE_INCLUDE_PATH ${CMAKE_INCLUDE_PATH} /usr/include /usr/local/include )
set( CMAKE_MODULE_PATH  ${CMAKE_MODULE_PATH} "${PROJECT_SOURCE_DIR}/cmake" ) 

set ( INSTALL_BIN_PATH bin )
set ( INSTALL_LIB_PATH lib )
set ( INSTALL_AR_PATH  lib )
set ( INSTALL_HEADERS_PATH include )

# Make relative paths absolute (needed later on)

foreach(p LIB BIN HEADERS AR)
        set(var INSTALL_${p}_PATH)
        if(NOT IS_ABSOLUTE "${${var}}")
                set(${var} "${CMAKE_INSTALL_PREFIX}/${${var}}")
        endif()
endforeach()


### Options ###

option(ENABLE_CAM_FFMPEG    "Enable virtual cameras based on video files (FFMPEG)" ON)
option(ENABLE_CAM_GSTREAMER "Enable Gstreamer cameras" ON)
option(ENABLE_CAM_V4L2      "Enable V4L2 cameras (USB/webcams)" ON)

### Search for Lib/Headers


### Config File

configure_file ( "${PROJECT_SOURCE_DIR}/config.h.in"
		 "${PROJECT_SOURCE_DIR}/src/config.h" )

### Set include directories 
        
include_directories( "${CMAKE_CURRENT_SOURCE_DIR}/include/"
	                 "${CMAKE_CURRENT_BINARY_DIR}" 
                      )

# link_directories( "${HWCAM_LIBRARY_DIR}" )

### File lists

file( GLOB src "src/*.c"  )
file( GLOB hdr "include/*.h"  )

### Targets

add_library( "hwcam" SHARED ${src} ${hdr} ) 

set_target_properties(hwcam PROPERTIES VERSION ${hwcam_VERSION_STRING}
                                       SOVERSION ${hwcam_VERSION_MAJOR})

### Linking

target_link_libraries( "hwcam" "m" )

### Cmake file

configure_file(hwcamConfig.cmake.in "${PROJECT_BINARY_DIR}/hwcamConfig.cmake" @ONLY)

install ( FILES "${PROJECT_BINARY_DIR}/hwcamConfig.cmake" 
      DESTINATION "${INSTALL_LIB_PATH}/hwcam" COMPONENT dev )  

configure_file(hwcamConfigVersion.cmake.in
	"${PROJECT_BINARY_DIR}/hwcamConfigVersion.cmake" @ONLY)

install ( FILES "${PROJECT_BINARY_DIR}/hwcamConfigVersion.cmake" 
      DESTINATION "${INSTALL_LIB_PATH}/hwcam" COMPONENT dev )  

### Install 

install( TARGETS "hwcam"
	    RUNTIME DESTINATION ${INSTALL_BIN_PATH}  COMPONENT main
	    LIBRARY DESTINATION ${INSTALL_LIB_PATH}  COMPONENT main
            ARCHIVE DESTINATION ${INSTALL_AR_PATH}   COMPONENT main )

install( FILES ${hdr}
	    DESTINATION ${INSTALL_HEADERS_PATH}/hwcam/${name}
	    COMPONENT main )

