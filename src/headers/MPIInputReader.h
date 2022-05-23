//
// Created by rafael on 5/19/22.
//

#ifndef CPYD_01_MPIINPUTREADER_H
#define CPYD_01_MPIINPUTREADER_H

#include "InputReader.h"

namespace cpyd {

    class MPIInputReader: public InputReader {
    public:
        MPIInputReader(std::string & input, std::string & output);

        void readFile() override;
    };

} // cpyd

#endif //CPYD_01_MPIINPUTREADER_H
