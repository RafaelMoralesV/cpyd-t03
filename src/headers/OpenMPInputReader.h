//
// Created by rafael on 5/19/22.
//

#ifndef CPYD_01_OPENMPINPUTREADER_H
#define CPYD_01_OPENMPINPUTREADER_H

#include "InputReader.h"
#include<omp.h>

#define ROW_LEN 87 * sizeof(char)

namespace cpyd {

    class OpenMPInputReader: public InputReader {
    public:
        OpenMPInputReader(std::ifstream & file, std::string & output);

        void readFile() override;
    };

} // cpyd

#endif //CPYD_01_OPENMPINPUTREADER_H
