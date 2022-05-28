//
// Created by rafael on 5/19/22.
//

#ifndef CPYD_01_OPENMPINPUTREADER_H
#define CPYD_01_OPENMPINPUTREADER_H

#include "InputReader.h"
#include<omp.h>

namespace cpyd {

    class OpenMPInputReader: public InputReader {
    public:
        OpenMPInputReader(std::string & input, std::string & output);

        void readFile() override;
    };

} // cpyd

#endif //CPYD_01_OPENMPINPUTREADER_H
