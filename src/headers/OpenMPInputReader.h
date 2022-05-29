//
// Created by rafael on 5/19/22.
//

#ifndef CPYD_01_OPENMPINPUTREADER_H
#define CPYD_01_OPENMPINPUTREADER_H

#include "InputReader.h"
#include<omp.h>

namespace cpyd {
    /**
     * Lector de archivo .csv con OpenMP
     *
     * Debido a que la lectura y escritura de archivos no es thread safe, hay una pequeña
     * cantidad de magia ocurriendo acá.
     */
    class OpenMPInputReader: public InputReader {
    public:
        /** \brief Constructor */
        OpenMPInputReader(std::string & input, std::string & output);

        /**
         * \brief Lector de archivo .csv con OpenMP
         *
         * Lee un trozo del archivo como un arreglo de caracteres, lo separa por filas
         * hacia un vector de strings, procesa con OpenMP cada linea, guardandola de vuelta
         * en su mismo lugar, y cuando cada hilo termina, escribe el resultado entero en
         * el output file stream
         */
        void readFile() override;
    };

} // cpyd

#endif //CPYD_01_OPENMPINPUTREADER_H
