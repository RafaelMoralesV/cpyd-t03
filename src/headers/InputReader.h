//
// Created by rafael on 5/17/22.
//

#ifndef CPYD_01_INPUTREADER_H
#define CPYD_01_INPUTREADER_H

#include <sstream>
#include <fstream>

#include "BaseInputReader.h"

namespace cpyd {
    class InputReader : public BaseInputReader {
    protected:
        InputReader(std::string &inputFilename, std::string &outputFilename);

        std::ifstream m_InputFileStream;
        std::ofstream m_OutputFileStream;
    public:
        bool invalidInputFile() override;

        bool invalidOutputFile() override;

        ~InputReader();
    };
}

#endif //CPYD_01_INPUTREADER_H
