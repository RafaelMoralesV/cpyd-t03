//
// Created by rafael on 5/28/22.
//

#ifndef CPYD_01_MPINODEINPUTREADER_H
#define CPYD_01_MPINODEINPUTREADER_H

#include "MPIInputReader.h"

namespace cpyd {

    class MPINodeInputReader : public MPIInputReader {
    public:
        MPINodeInputReader(std::string &input, std::string &output);

        void readFile() override;
    };

} // cpyd

#endif //CPYD_01_MPINODEINPUTREADER_H
