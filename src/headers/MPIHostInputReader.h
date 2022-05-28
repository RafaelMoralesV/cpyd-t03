//
// Created by rafael on 5/28/22.
//

#ifndef CPYD_01_MPIHOSTINPUTREADER_H
#define CPYD_01_MPIHOSTINPUTREADER_H

#include "MPIInputReader.h"

namespace cpyd {

    class MPIHostInputReader : public MPIInputReader {
    public:
        MPIHostInputReader(std::string &input, std::string &output);

        void readFile() override;
    };

} // cpyd

#endif //CPYD_01_MPIHOSTINPUTREADER_H
