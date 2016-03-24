cmake_minimum_required(VERSION 2.8.4)
project(GravityLaw)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(CMAKE_MODULE_PATH "/usr/share/cmake-2.8/Modules" ${CMAKE_MODULE_PATH})
find_package(SFML 2 REQUIRED system window graphics network audio)
find_package(OpenGL REQUIRED)
find_package(PkgConfig)
pkg_check_modules(GTKMM gtkmm-3.0)
pkg_check_modules(GTKGLMM gtkglextmm-1.2)




include_directories( ${OPENGL_INCLUDE_DIRS} ${GTKMM_INCLUDE_DIRS})
LINK_DIRECTORIES(${GTKMM_LIBRARY_DIRS})

ADD_DEFINITIONS(${GTKMM_CFLAGS_OTHER})

set(SOURCE_FILES main.cpp Corps.cpp Corps.h Simulation.cpp Simulation.h Painter.cpp Painter.h Controller.cpp Controller.h)
add_executable(GravityLaw ${SOURCE_FILES})

target_link_libraries(GravityLaw ${SFML_LIBRARIES} ${OPENGL_LIBRARIES} ${GTKMM_LIBRARIES} ${GTKGLMM_LIBRARIES})