//
// Created by rafael on 5/27/22.
//

#include "../headers/BaseInputReader.h"

namespace cpyd {
    BaseInputReader::BaseInputReader(std::string &inputFilename, std::string &outputFilename)
            : m_InputFilename(inputFilename), m_OutputFilename(outputFilename) {}


    std::string BaseInputReader::processRow(std::string &row) {
        const char respuestas[] = {'A', 'E', 'C',
                                   'B', 'B', 'D',
                                   'A', 'B', 'E',
                                   'C', 'B', 'D'};

        std::stringstream stream(row);

        std::string word;
        std::string uuid;
        int correctas = 0, incorrectas = 0, omitidas = 0;
        double puntaje, nota;
        std::getline(stream, uuid, ';');
        for (int i = 1; i < COLUMNAS; i++) {
            std::getline(stream, word, ';');

            if (word == "\"-\"") {
                omitidas++;
                continue;
            }

            bool correcta = word[1] == respuestas[i - 1];
            correctas += (int) correcta;
            incorrectas += (int) !correcta;
        }

        puntaje = correctas * PUNTAJE_CORRECTA - incorrectas * PUNTAJE_INCORRECTA;
        nota = puntaje > 0 ? 1 + puntaje : 1;

        nota = round(nota * 10) / 10.0;

        std::stringstream out;

        out << uuid << ','
            << correctas << ','
            << incorrectas << ','
            << omitidas << ','
            << puntaje << ','
            << nota;
        return out.str();
    }
}