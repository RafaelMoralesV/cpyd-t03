//
// Created by rafael on 5/28/22.
//

#ifndef CPYD_01_MPIHOSTINPUTREADER_H
#define CPYD_01_MPIHOSTINPUTREADER_H

#include "MPIInputReader.h"

namespace cpyd {

    /**
     *  Lector de archivo .csv con MPI exclusivo para el proceso principal
     *  Esta clase lanza un error en caso de ser instanciada por un proceso adicional.
     */
    class MPIHostInputReader : public MPIInputReader {
    public:
        /**
         * \brief Constructor
         * @throws std::logic_error en caso de ser instanciada por proceso con rango distinto de 0
         */
        MPIHostInputReader(std::string &input, std::string &output);

        /**
         * Procesa el archivo, luego recibe lo que el resto de procesos ha procesado
         * y lo escribe en un outputstream.
         */
        void readFile() override;
    };

} // cpyd

#endif //CPYD_01_MPIHOSTINPUTREADER_H
