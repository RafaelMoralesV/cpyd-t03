//
// Created by rafael on 5/17/22.
//

#ifndef CPYD_01_SEQUENTIALINPUTREADER_H
#define CPYD_01_SEQUENTIALINPUTREADER_H

#include <fstream>
#include "InputReader.h"

class SequentialInputReader: public InputReader {
public:
    explicit SequentialInputReader(const std::string& filename);

    void readFile() override;
    void processRow() override;
};


#endif //CPYD_01_SEQUENTIALINPUTREADER_H
