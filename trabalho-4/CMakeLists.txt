cmake_minimum_required(VERSION 3.10)
project(COMP_EVOL)

include_directories(${PROJECT_SOURCE_DIR}/include)
file(GLOB SOURCES "src/*.cpp" "include/*.h")
add_library(library ${SOURCES})

set(PROJECT_DIR "${PROJECT_SOURCE_DIR}/")
set(INSTANCES "${PROJECT_SOURCE_DIR}/instances")


configure_file(${PROJECT_SOURCE_DIR}/include/config.h.in ${PROJECT_SOURCE_DIR}/include/config.h)



add_subdirectory(src)