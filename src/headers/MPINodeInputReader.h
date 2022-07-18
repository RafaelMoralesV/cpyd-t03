//
// Created by rafael on 5/28/22.
//

#ifndef CPYD_01_MPINODEINPUTREADER_H
#define CPYD_01_MPINODEINPUTREADER_H

#include "MPIInputReader.h"

namespace cpyd {
    /**
     *  Lector de archivo .csv con MPI exclusivo para el proceso principal
     *  Esta clase lanza un error en caso de ser instanciada por el proceso principal.
     */
    class MPINodeInputReader : public MPIInputReader {
    public:
        /**
         * \brief Constructor
         * @throws std::logic_error en caso de ser instanciada por proceso con rango igual a 0
         */
        explicit MPINodeInputReader(std::string &input);

        /**
         * Procesa el archivo, luego envia el resultado hacia el proceso principal
         */
        void readFile() override;
    };

} // cpyd

#endif //CPYD_01_MPINODEINPUTREADER_H
