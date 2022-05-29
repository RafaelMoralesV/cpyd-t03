//
// Created by rafael on 5/19/22.
//

#ifndef CPYD_01_MPIINPUTREADER_H
#define CPYD_01_MPIINPUTREADER_H

#include "InputReader.h"
#include <mpi.h>

/**
 * 30,030 es divisible por 2, 3, 5, 7, 11, y 13
 * por lo que procesar una cantidad de lineas que sea un factor de este numero
 * hace que dividirlo en una cantidad de procesos sea muy poco problematico.
 *
 * En general, no deberia haber problema hasta que se spawneen una cantidad extraña de procesos, como 17, por ejemplo.
 */
#define CANT_ROWS 90090

#define CHUNK_SIZE (CANT_ROWS * ROW_LEN)


namespace cpyd {
    /**
     *  Implementación NO basada en std::filestreams. Debido a que en MPI es ligeramente más
     *  sencillo trabajar en su propio tipo de datos [MPI::File], generamos esta clase que se
     *  encarga de:
     *      - Abrir el archivo de Input.
     *      - Particionar el archivo para cada proceso.
     *      - Leer el archivo.
     *      - Cerrar y Limpiar lo que reste.
     *
     *  Esta clase no implementa readFile, por lo que no es instanciable.
     */
    class MPIInputReader : public BaseInputReader {
    protected:
        /** Rango del proceso */
        int m_rank;

        /** Cantidad de procesos */
        int m_size;

        /** MPI::Info Object, necesario para el archivo de entrada */
        MPI::Info m_Info;

        /** Archivo de entrada */
        MPI::File m_InputFile;

        /** Bytes leídos del archivo de entrada */
        char* m_Data;

        /** Cantidad de bytes leídos */
        unsigned long m_DataLen;

        /**
         * Lee el archivo de entrada y carga en m_Data los datos leidos.
         */
        void readdataMPI(int chunk_number);

        /**
         * Consigue un trozo del archivo que debe leer el proceso, y escribe en los parametros 'start' y 'end'
         * los bytes de inicio y fin de este trozo.
         *
         * @param chunk_number [int] Numero del trozo de archivo que se desea particionar
         * @param start [int] Bite de inicio de lectura a ser conseguido
         * @param end [int] Ultimo bite del archivo a ser leido
         */
        void partitionFile(int chunk_number, int *start, int *end) const;
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
        ~MPIInputReader();

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
