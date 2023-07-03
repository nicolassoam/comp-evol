cmake_minimum_required(VERSION 3.10)
project(COMP_EVOL)

include_directories(${PROJECT_SOURCE_DIR}/include)
file(GLOB SOURCES "src/*.cpp" "include/*.h")
add_library(library ${SOURCES})

set(PROJECT_DIR "${PROJECT_SOURCE_DIR}/")
set(INSTANCES "${PROJECT_SOURCE_DIR}/instances")

set(FALKENAUER_U "${INSTANCES}/Falkenauer/Falkenauer_U")
set(FALKENAUER_T "${INSTANCES}/Falkenauer/Falkenauer_T")

set(WAESCHER "${INSTANCES}/instances/Waescher/")

set(SCHOLL "${INSTANCES}/instances/Scholl/")
set(SCHOLL_1 "${SCHOLL}Scholl_1")
set(SCHOLL_2 "${SCHOLL}Scholl_2")
set(SCHOLL_3 "${SCHOLL}Scholl_3")

set(AI "${INSTANCES}/Difficult_Instances/AI")

set(ANI "${INSTANCES}/Difficult_Instances/ANI")

set(OUTPUT_DIR "${PROJECT_SOURCE_DIR}/output/")

option(CPU_TIME  "Enable cputime build" ON)

configure_file(${PROJECT_SOURCE_DIR}/include/config.h.in ${PROJECT_SOURCE_DIR}/include/config.h)

add_executable(main ${SOURCES})
find_package(OpenMP)

target_link_libraries(main PRIVATE OpenMP::OpenMP_CXX)

add_compile_options(-std=c++20 -Ofast -fPIC -march=native -fopenmp)