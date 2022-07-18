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

        double puntaje_math = 0, puntaje_stem = 0, puntaje_hum = 0;

        std::getline(stream, uuid, ';');
        for (int i = 1; i < COLUMNAS; i++) {
            std::getline(stream, word, ';');

            if (word == "\"-\"") {
                continue;
            }

            int correcta = (int)(word[1] == respuestas[i - 1]);
            switch ((i - 1) / 3) {
                case 0:
                    puntaje_math += correcta * PUNTAJE_CORRECTA - !correcta * PUNTAJE_INCORRECTA;
                    break;
                case 1:
                    puntaje_stem += correcta * PUNTAJE_CORRECTA - !correcta * PUNTAJE_INCORRECTA;
                    break;
                case 2:
                    puntaje_hum += correcta * PUNTAJE_CORRECTA - !correcta * PUNTAJE_INCORRECTA;
                    break;
                default:
                    break;
            }
        }

        double puntaje = puntaje_math + puntaje_stem + puntaje_hum;

        std::stringstream out;

        out << uuid << ';'
            << puntaje_math << ';'
            << puntaje_stem << ';'
            << puntaje_hum << ';'
            << puntaje;
        return out.str();
    }
}