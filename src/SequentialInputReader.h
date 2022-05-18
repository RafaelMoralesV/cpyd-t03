//
// Created by rafael on 5/17/22.
//

#ifndef CPYD_01_SEQUENTIALINPUTREADER_H
#define CPYD_01_SEQUENTIALINPUTREADER_H

#include <fstream>
#include "InputReader.h"

class SequentialInputReader: InputReader {
private:
    std::ifstream csvFile;
public:
    explicit SequentialInputReader(const std::string& filename);

    void readFile() override;
};


#endif //CPYD_01_SEQUENTIALINPUTREADER_H
