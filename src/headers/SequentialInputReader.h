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

/**
 * Lector de archivo .csv secuencial. Al igual que el resto de lectores, escribe su resultado en un archivo
 * output.csv que existe en el mismo directorio que el archivo ejecutable.
 */
class SequentialInputReader: public InputReader {
public:
    SequentialInputReader(std::ifstream & file, std::string & output);

    /**
     * \brief Lector de archivo .csv secuencial
     *
     * Este lector del archivo lee de manera secuencial y con un solo núcleo. Esta alternativa no ocupa ninguna forma
     * de paralelismo o concurrencia.
     *
     * @param none
     *
     * @returns void
     */
    void readFile() override;
};


#endif //CPYD_01_SEQUENTIALINPUTREADER_H
