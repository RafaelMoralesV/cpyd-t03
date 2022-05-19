//
// Created by rafael on 5/19/22.
//

#ifndef CPYD_01_MPIINPUTREADER_H
#define CPYD_01_MPIINPUTREADER_H

#include "InputReader.h"

namespace cpyd {

    class MPIInputReader: public InputReader {
    public:
        explicit MPIInputReader(std::ifstream & file);

        void readFile() override;
        void processRow() override;
    };

} // cpyd

#endif //CPYD_01_MPIINPUTREADER_H
