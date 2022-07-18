//
// Created by rafael on 5/19/22.
//
#include "../headers/InputReader.h"

namespace cpyd {
    InputReader::InputReader(std::string &inputFilename)
            : BaseInputReader(inputFilename),
              m_InputFileStream(inputFilename),
              m_auxOFStream("./aux.csv"),
              m_MathOFStream("./matematicas.csv"),
              m_StemOFStream("./ciencias.csv"),
              m_HumOFStream("./humanidades.csv") {
        std::string aux;

        // La primera linea contiene informacion meta sobre que es cada columna, por lo que eliminarla
        // en este espacio es buena idea.
        std::getline(m_InputFileStream, aux);

        m_MathOFStream << "Identificador de estudiante;Puntaje de área específica;Puntaje" << std::endl;
        m_StemOFStream << "Identificador de estudiante;Puntaje de área específica;Puntaje" << std::endl;
        m_HumOFStream << "Identificador de estudiante;Puntaje de área específica;Puntaje" << std::endl;
    }

    InputReader::~InputReader() {
        m_InputFileStream.close();
        m_MathOFStream.close();
        m_StemOFStream.close();
        m_HumOFStream.close();
    }

    bool InputReader::invalidInputFile() {
        return !m_InputFileStream;
    }
}