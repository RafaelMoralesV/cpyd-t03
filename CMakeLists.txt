cmake_minimum_required(VERSION 3.22)
project(cpyd_01)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(src)

find_package(OpenMP REQUIRED)
target_link_libraries(test-check OpenMP::OpenMP_CXX)
