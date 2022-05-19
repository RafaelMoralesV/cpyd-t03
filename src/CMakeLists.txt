add_executable(test-check
        main.cpp
        classes/InputReader.cpp headers/InputReader.h
        classes/SequentialInputReader.cpp headers/SequentialInputReader.h
        classes/OpenMPInputReader.cpp headers/OpenMPInputReader.h
        classes/MPIInputReader.cpp headers/MPIInputReader.h
        )
