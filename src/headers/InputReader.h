//
// Created by rafael on 5/17/22.
//

#ifndef CPYD_01_INPUTREADER_H
#define CPYD_01_INPUTREADER_H

#include <sstream>
#include <fstream>

#define COLUMNAS 13
#define PUNTAJE_CORRECTA 0.5
#define PUNTAJE_INCORRECTA 0.12

class InputReader {
protected:
    explicit InputReader(std::ifstream & file);
    std::ifstream & csvFile;
    std::ofstream output;
public:
    virtual void readFile() = 0;
    void processRow(std::stringstream & stream);

    ~InputReader();
};

#endif //CPYD_01_INPUTREADER_H
