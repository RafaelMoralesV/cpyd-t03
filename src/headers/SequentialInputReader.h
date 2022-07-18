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
#include "Resultado.h"

namespace cpyd {
    /**
     * Lector de archivo .csv secuencial.
     * No hay mucha magia ocurriendo aca. Obtengo una linea desde mi ifstream, la proceso, y la escribo a mi ofstream.
     */
    class SequentialInputReader : public InputReader {
    public:
        /** \brief Constructor */
        explicit SequentialInputReader(std::string &input);

        /**
         * \brief Lector de archivo .csv secuencial
         *
         * Este lector del archivo lee de manera secuencial y con un solo núcleo. Esta alternativa no ocupa ninguna
         * forma de paralelismo o concurrencia.
         */
        void readFile() override;
    };
}

#endif //CPYD_01_SEQUENTIALINPUTREADER_H
