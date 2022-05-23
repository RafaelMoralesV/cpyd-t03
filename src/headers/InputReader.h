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
    InputReader(std::string & input, std::string & output);
    std::ifstream csvFile;
    std::ofstream output;
public:
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
     * @returns [std::string] Retorna un string con la fila lista para insertarse en el archivo output.csv
     */
    virtual std::string processRow(std::string & row);

    bool invalidInputFile();
    bool invalidOutputFile();

    ~InputReader();
};

#endif //CPYD_01_INPUTREADER_H
