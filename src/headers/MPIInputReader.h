//
// Created by rafael on 5/19/22.
//

#ifndef CPYD_01_MPIINPUTREADER_H
#define CPYD_01_MPIINPUTREADER_H

#include "InputReader.h"
#include <mpi.h>

namespace cpyd {

    class MPIInputReader: public InputReader {
    protected:
        std::string m_input;
        std::string m_output;
    public:
        MPIInputReader(std::string & input, std::string & output);

        void readFile() override;
    };

    void partitionFile(int filesize, int rank, int size, int overlap, int *start, int *end);
    void readdataMPI(MPI_File *in, int rank, int size, int overlap, char **data, int *ndata);
} // cpyd

#endif //CPYD_01_MPIINPUTREADER_H
