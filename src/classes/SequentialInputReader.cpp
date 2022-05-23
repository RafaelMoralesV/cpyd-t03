//
// Created by rafael on 5/17/22.
//

#include "../headers/SequentialInputReader.h"

SequentialInputReader::SequentialInputReader(std::string & input, std::string & output)
    : InputReader(input, output) { }

void SequentialInputReader::readFile() {
    if(!this->csvFile.is_open()){
        return;
    }

    std::string line, word;
    std::vector<std::string> row;

    while(std::getline(this->csvFile, line)){
        output << processRow(line) << std::endl;
    }
}
