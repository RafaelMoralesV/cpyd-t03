//
// Created by rafael on 5/19/22.
//
#include "InputReader.h"

InputReader::~InputReader() {
    csvFile.close();
    output.close();
}
