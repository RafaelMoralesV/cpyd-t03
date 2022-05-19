//
// Created by rafael on 5/17/22.
//

#ifndef CPYD_01_INPUTREADER_H
#define CPYD_01_INPUTREADER_H

#include <fstream>

class InputReader {
protected:
    explicit InputReader(std::ifstream & file);
    std::ifstream & csvFile;
    std::ofstream output;
public:
    virtual void readFile() = 0;
    virtual void processRow() = 0;

    ~InputReader();
};

#endif //CPYD_01_INPUTREADER_H
