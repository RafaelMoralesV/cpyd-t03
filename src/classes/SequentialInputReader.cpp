//
// Created by rafael on 5/17/22.
//

#include "../headers/SequentialInputReader.h"

SequentialInputReader::SequentialInputReader(std::ifstream & file)
    : InputReader(file) { }

void SequentialInputReader::readFile() {
    if(!this->csvFile.is_open()){
        return;
    }

    std::string line, word;
    std::vector<std::string> row;
    int rowline = 0;

    getline(this->csvFile, line);
    while(std::getline(this->csvFile, line)){
        std::stringstream s(line);

        this->processRow(s);

        if(rowline++ == 30) break;
    }
}
