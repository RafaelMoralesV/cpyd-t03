cmake_minimum_required(VERSION 3.22)
project(cpyd_01)

set(CMAKE_CXX_STANDARD 20)
#set(CMAKE_CXX_FLAGS "-Wall -g3" )

add_executable(test-check
        src/main.cpp
        src/classes/InputReader.cpp src/headers/InputReader.h
        src/classes/SequentialInputReader.cpp src/headers/SequentialInputReader.h
        src/classes/OpenMPInputReader.cpp src/headers/OpenMPInputReader.h
        src/classes/MPIInputReader.cpp src/headers/MPIInputReader.h
        src/classes/BaseInputReader.cpp src/headers/BaseInputReader.h)

find_package(OpenMP REQUIRED)
find_package(MPI REQUIRED)
target_link_libraries(test-check OpenMP::OpenMP_CXX MPI::MPI_CXX)
