//
// Created by rafael on 5/19/22.
//

#ifndef CPYD_01_OPENMPINPUTREADER_H
#define CPYD_01_OPENMPINPUTREADER_H

#include "InputReader.h"

namespace cpyd {

    class OpenMPInputReader: public InputReader {
    public:
        explicit OpenMPInputReader(std::ifstream & file);

        void readFile() override;
    };

} // cpyd

#endif //CPYD_01_OPENMPINPUTREADER_H
