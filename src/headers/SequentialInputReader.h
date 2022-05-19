//
// Created by rafael on 5/17/22.
//

#ifndef CPYD_01_SEQUENTIALINPUTREADER_H
#define CPYD_01_SEQUENTIALINPUTREADER_H

#include <fstream>
#include "InputReader.h"
#include <vector>
#include <iostream>
#include <sstream>

class SequentialInputReader: public InputReader {
public:
    explicit SequentialInputReader(std::ifstream & file);

    void readFile() override;
};


#endif //CPYD_01_SEQUENTIALINPUTREADER_H
