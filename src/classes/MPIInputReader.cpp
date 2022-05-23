//
// Created by rafael on 5/19/22.
//

#include "../headers/MPIInputReader.h"

namespace cpyd {
    MPIInputReader::MPIInputReader(std::string & input, std::string & output)
        : InputReader(input, output), m_input(input), m_output(output){ }

    void MPIInputReader::readFile() {
        MPI::File in;
        int rank, size;
        int ierr;

        MPI_Comm_rank(MPI_COMM_WORLD, &rank);
        MPI_Comm_size(MPI_COMM_WORLD, &size);


    }
} // cpyd