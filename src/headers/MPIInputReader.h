//
// Created by rafael on 5/19/22.
//

#ifndef CPYD_01_MPIINPUTREADER_H
#define CPYD_01_MPIINPUTREADER_H

#include "InputReader.h"
#include <mpi.h>

namespace cpyd {

    class MPIInputReader : public BaseInputReader {
    protected:
        int m_rank;
        int m_size;

        MPI::Info m_Info;
        MPI::File m_InputFile;

    public:
        MPIInputReader(std::string &input, std::string &output);

        void partitionFile(int overlap, int *start, int *end) const;

        void readdataMPI(int overlap, char **data, int *ndata);

        bool invalidInputFile() override;

        bool invalidOutputFile() override;
    };


} // cpyd

#endif //CPYD_01_MPIINPUTREADER_H
