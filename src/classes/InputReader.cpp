//
// Created by rafael on 5/19/22.
//
#include "../headers/InputReader.h"

InputReader::~InputReader() {
    csvFile.close();
    output.close();
}

InputReader::InputReader(std::ifstream & file)
    : csvFile(file), output("output.csv") {
}
