//
// Created by rafael on 5/17/22.
//

#include "../headers/SequentialInputReader.h"

SequentialInputReader::SequentialInputReader(std::ifstream & file, std::string & output)
    : InputReader(file, output) { }

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
