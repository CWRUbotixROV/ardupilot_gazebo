cmake_minimum_required(VERSION 2.8 FATAL_ERROR)


project(ardupilot_sitl_gazebo)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake")


#######################
## Find Dependencies ##
#######################

find_package(gazebo REQUIRED)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${GAZEBO_CXX_FLAGS}")

if("${GAZEBO_VERSION}" VERSION_LESS "7.0")
    message(FATAL_ERROR "You need at least Gazebo 7.0. Your version: ${GAZEBO_VERSION}")
else()
    message("Gazebo version: ${GAZEBO_VERSION}")
endif()

find_package(OpenCV REQUIRED)

# find_package(PkgConfig REQUIRED)
# pkg_search_module(GLIB REQUIRED glib-2.0)
set(GStreamer_FIND_VERSION "1.0")
find_package(GStreamer REQUIRED)

###########
## Build ##
###########

include_directories(
        ${PROJECT_SOURCE_DIR}
        include
        ${GAZEBO_INCLUDE_DIRS}
        ${GSTREAMER_INCLUDE_DIRS}
        ${GSTREAMER_APP_INCLUDE_DIRS}
        )

link_libraries(
        ${GAZEBO_LIBRARIES}
        ${OpenCV_LIBRARIES}
        ${GSTREAMER_LIBRARIES}
        ${GSTREAMER_APP_LIBRARIES}
        ${GLIB_LDFLAGS}
        gobject-2.0
        )

link_directories(
        ${GAZEBO_LIBRARY_DIRS}
        )

set (plugins_single_header
        ArduPilotPlugin
        ArduCopterIRLockPlugin
        GimbalSmall2dPlugin
        )

add_library(ArduCopterIRLockPlugin SHARED src/ArduCopterIRLockPlugin.cc)
target_link_libraries(ArduCopterIRLockPlugin ${GAZEBO_LIBRARIES})

add_library(ArduPilotPlugin SHARED src/ArduPilotPlugin.cc)
target_link_libraries(ArduPilotPlugin ${GAZEBO_LIBRARIES})

add_library(gazebo_gst_camera_plugin SHARED src/gazebo_gst_camera_plugin.cpp)

add_library(freebuoyancy_gazebo SHARED
    src/freebuoyancy.cpp
)

target_link_libraries(freebuoyancy_gazebo ${GAZEBO_LIBRARIES})

add_library(random_rotation SHARED src/random_rotation.cc)
target_link_libraries(random_rotation ${GAZEBO_LIBRARIES})

if("${GAZEBO_VERSION}" VERSION_LESS "8.0")
    add_library(GimbalSmall2dPlugin SHARED src/GimbalSmall2dPlugin.cc)
    target_link_libraries(GimbalSmall2dPlugin ${GAZEBO_LIBRARIES})
    install(TARGETS GimbalSmall2dPlugin DESTINATION ${GAZEBO_PLUGIN_PATH})
endif()

install(TARGETS ArduCopterIRLockPlugin DESTINATION ${GAZEBO_PLUGIN_PATH})
install(TARGETS ArduPilotPlugin DESTINATION ${GAZEBO_PLUGIN_PATH})
install(TARGETS gazebo_gst_camera_plugin DESTINATION ${GAZEBO_PLUGIN_PATH})
install(TARGETS freebuoyancy_gazebo DESTINATION ${GAZEBO_PLUGIN_PATH})
install(TARGETS random_rotation DESTINATION ${GAZEBO_PLUGIN_PATH})

#install(DIRECTORY models DESTINATION ${GAZEBO_RESOURCE_PATH})
#install(DIRECTORY worlds DESTINATION ${GAZEBO_RESOURCE_PATH})
