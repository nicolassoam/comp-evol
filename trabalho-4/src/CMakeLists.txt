add_executable(main main.cpp)
find_package(OpenMP)
target_link_libraries(main PRIVATE OpenMP::OpenMP_CXX)