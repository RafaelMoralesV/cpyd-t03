//
// Created by rafael on 5/27/22.
//

#ifndef CPYD_01_BASEINPUTREADER_H
#define CPYD_01_BASEINPUTREADER_H

#include <iostream>
#include <sstream>
#include <cmath>

namespace cpyd{
#define COLUMNAS 13
#define PUNTAJE_CORRECTA 0.5
#define PUNTAJE_INCORRECTA 0.12

#define FIRST_LINE_LEN 190
#define ROW_LEN 87

    /**
     * Base Input Reader
     *
     * Esta clase es una interfaz para los lectores de input de cada uno de los modos de lectura
     * Este header, ademas, define Macros con informacion relevante para la lectura del archivo de entrada.
     *
     * Para heredar de esta clase, se requiere implementar 3 funciones:
     *  - readfile, funcion principal de la clase
     *  - invalidInputFile
     *  - invalidOutputFile
     *
     *  Ademas, es posible sobrescribir la funcion de procesamiento de cada fila, en caso de ser necesario.
     */
    class BaseInputReader {
    protected:
        std::string m_InputFilename;

    public:
        /**
         * \brief Constructor base
         *
         * @param inputFilename [std::string] Ruta o Nombre del archivo .csv a procesar
         */
        explicit BaseInputReader(std::string &inputFilename);


        /**
         * \brief Lee el archivo de entrada.
         *
         * Esta funcion tiene 3 partes. Leer el archivo de entrada, procesar cada una de las filas
         * y luego generar el archivo de salida. Esto lo vuelve la funcion 'principal' para esta clase.
         */
        virtual void readFile() = 0;

        /**
         * \brief Procesador de una línea singular
         *
         * Espera recibir un string stream de un archivo csv que utilice un separador ';', y que contenga 13 columnas, las
         * cuales deben ser un uuidv4, seguido por 12 columnas de respuesta a una pregunta n, de tal manera de que el valor de
         * esta sea "A", "B", "C", "D", "E" o "-".
         *
         * @param [std::string] row contiene una fila entera del archivo .csv que se está analizando
         *
         * @returns [std::string] Retorna un string con la fila lista para insertarse en el archivo m_OutputFileStream.csv
         */
        virtual std::string processRow(std::string &row);

        /**
         * \brief Verifica si el archivo de entrada es invalido
         *
         * @return true, si el archivo de entrada es inaccesible
         */
        virtual bool invalidInputFile() = 0;
    };
}


#endif //CPYD_01_BASEINPUTREADER_H
