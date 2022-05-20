//
// Created by rafael on 5/19/22.
//
#include <cmath>
#include "../headers/InputReader.h"


InputReader::~InputReader() {
    csvFile.close();
    output.close();
}

InputReader::InputReader(std::ifstream & file)
    : csvFile(file), output("output.csv") {
    std::string aux;
    std::getline(csvFile, aux);
}

void InputReader::processRow(std::stringstream & stream) {
    const char respuestas[] = {'A', 'E', 'C',
                              'B', 'B', 'D',
                              'A', 'B', 'E',
                              'C', 'B', 'D' };

    std::string word;
    std::string uuid;
    int correctas = 0, incorrectas = 0, omitidas = 0;
    double puntaje, nota;
    std::getline(stream, uuid, ';');
    for(int i = 1; i < COLUMNAS; i++) {
        std::getline(stream, word, ';');

        if(word == "\"-\"") {
            omitidas++;
            continue;
        }

        bool correcta = word[1] == respuestas[i-1];
        correctas += (int) correcta;
        incorrectas += (int) !correcta;
    }

    puntaje = correctas * PUNTAJE_CORRECTA - incorrectas * PUNTAJE_INCORRECTA;
    nota = puntaje > 0 ? 1 + puntaje : 1;

    nota = round(nota * 10) / 10.0;

    output  << uuid         << ','
            << correctas    << ','
            << incorrectas  << ','
            << omitidas     << ','
            << puntaje      << ','
            << nota         << std::endl;
}
