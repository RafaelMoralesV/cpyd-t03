//
// Created by rafael on 5/17/22.
//

#include "../headers/SequentialInputReader.h"

namespace cpyd {
    SequentialInputReader::SequentialInputReader(std::string &input, std::string &output)
            : InputReader(input, output) {}

    void SequentialInputReader::readFile() {
        std::string line, word;
        std::vector<std::string> row;

        while (std::getline(this->m_InputFileStream, line)) {
            m_OutputFileStream << processRow(line) << std::endl;
        }
    }
}
