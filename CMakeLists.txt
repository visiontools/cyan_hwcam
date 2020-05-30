### CMake file for cyan_hwcam 
###
###     Author : seb@codices.org
###
###############################################################################

cmake_minimum_required (VERSION 2.6)

project (cyan_hwcam)
set (cyan_hwcam_VERSION_MAJOR 0)
set (cyan_hwcam_VERSION_MINOR 1)
set (cyan_hwcam_VERSION_PATCH 1)
set (cyan_hwcam_VERSION_STRING
	${cyan_hwcam_VERSION_MAJOR}.${cyan_hwcam_VERSION_MINOR}.${cyan_hwcam_VERSION_PATCH} )

set( CMAKE_LIBRARY_PATH ${CMAKE_LIBRARY_PATH} /lib /usr/lib /usr/local/lib )
set( CMAKE_INCLUDE_PATH ${CMAKE_INCLUDE_PATH} /usr/include /usr/local/include )
set( CMAKE_MODULE_PATH  ${CMAKE_MODULE_PATH} "${PROJECT_SOURCE_DIR}/cmake" ) 

set ( INSTALL_BIN_PATH bin )
set ( INSTALL_LIB_PATH lib )
set ( INSTALL_AR_PATH  lib )
set ( INSTALL_HEADERS_PATH include )
set ( INSTALL_PLUGINS_PATH share/cyan_hwcam )

# Make relative paths absolute (needed later on)

foreach(p LIB BIN HEADERS AR PLUGINS)
        set(var INSTALL_${p}_PATH)
        if(NOT IS_ABSOLUTE "${${var}}")
                set(${var} "${CMAKE_INSTALL_PREFIX}/${${var}}")
        endif()
endforeach()


### Options

option(BUILD_TEST   "Build cyan_hwcam tests" ON)

### Search for Lib/Headers

    ### I need pthreads

    set(THREADS_PREFER_PTHREAD_FLAG ON)
    find_package(Threads REQUIRED)

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

add_library( "cyan_hwcam" SHARED ${src} ${hdr} ) 

set_target_properties(cyan_hwcam PROPERTIES VERSION ${cyan_hwcam_VERSION_STRING}
                                       SOVERSION ${cyan_hwcam_VERSION_MAJOR})

### Linking

target_link_libraries( "cyan_hwcam" ${CMAKE_DL_LIBS} Threads::Threads )

### Cmake file

configure_file(cyan_hwcamConfig.cmake.in "${PROJECT_BINARY_DIR}/cyan_hwcamConfig.cmake" @ONLY)

install ( FILES "${PROJECT_BINARY_DIR}/cyan_hwcamConfig.cmake" 
      DESTINATION "${INSTALL_LIB_PATH}/cyan_hwcam" COMPONENT dev )  

### Install 

install( TARGETS "cyan_hwcam"
	    RUNTIME DESTINATION ${INSTALL_BIN_PATH}  COMPONENT main
	    LIBRARY DESTINATION ${INSTALL_LIB_PATH}  COMPONENT main
            ARCHIVE DESTINATION ${INSTALL_AR_PATH}   COMPONENT main )

install( FILES ${hdr}
	    DESTINATION ${INSTALL_HEADERS_PATH}/cyan_hwcam/${name}
	    COMPONENT main )

### tests

if (BUILD_TEST)
    enable_testing()
endif()

### plugins

add_subdirectory(plugins)



