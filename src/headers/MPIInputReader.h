//
// Created by rafael on 5/19/22.
//

#ifndef CPYD_01_MPIINPUTREADER_H
#define CPYD_01_MPIINPUTREADER_H

#include "InputReader.h"
#include <mpi.h>

#define OVERLAP 1

namespace cpyd {

    class MPIInputReader : public BaseInputReader {
    protected:
        int m_rank;
        int m_size;

        MPI::Info m_Info;
        MPI::File m_InputFile;

        char* m_Data;
        unsigned long m_DataLen;

        /**
         * Lee el archivo de entrada y carga en m_Data los datos leidos.
         */
        void readdataMPI();

        /**
         * Consigue un trozo del archivo que debe leer el proceso, y escribe en los parametros 'start' y 'end'
         * los bytes de inicio y fin de este trozo.
         *
         * @param start [int] Bite de inicio de lectura a ser conseguido
         * @param end [int] Ultimo bite del archivo a ser leido
         */
        void partitionFile(int *start, int *end) const;
    public:
        /**
         * \brief Constructor
         * Abre el archivo de Input, y consigue el Rango y Cantidad de procesos
         *
         * @param input [std::string] Direccion al archivo de entrada
         * @param output [std::string] Direccion del archivo de salida
         */
        MPIInputReader(std::string &input, std::string &output);

        /**
         * \brief Destructor
         * Cierra el archivo y libera el buffer de lectura.
         */
        virtual ~MPIInputReader();

        /**
         * Implementa la funcion que verifica si el archivo de entrada es invalido
         *
         * @return true, en caso de ser invalido
         */
        bool invalidInputFile() override;

        /**
         * Implementa la funcion que verifica si el archivo de salida es invalido
         *
         * @return true, en caso de ser invalido
         */
        bool invalidOutputFile() override;
    };


} // cpyd

#endif //CPYD_01_MPIINPUTREADER_H
