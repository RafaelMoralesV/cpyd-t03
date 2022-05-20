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

    /**
     * \brief Procesador de una línea singular
     *
     * Espera recibir un string stream de un archivo csv que utilice un separador ';', y que contenga 13 columnas, las
     * cuales deben ser un uuidv4, seguido por 12 columnas de respuesta a una pregunta n, de tal manera de que el valor de
     * esta sea "A", "B", "C", "D", "E" o "-".
     *
     * @param [std::stringstream] stream contiene una fila entera del archivo .csv que se está analizando
     *
     * @returns [void]
     */
    virtual void processRow(std::stringstream & stream);

    ~InputReader();
};

#endif //CPYD_01_INPUTREADER_H
