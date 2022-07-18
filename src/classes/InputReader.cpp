//
// Created by rafael on 5/19/22.
//
#include "../headers/InputReader.h"

namespace cpyd {
    InputReader::InputReader(std::string &inputFilename)
            : BaseInputReader(inputFilename),
              m_InputFileStream(inputFilename),
              m_auxOFStream("./aux.csv") {
        std::string aux;

        // La primera linea contiene informacion meta sobre que es cada columna, por lo que eliminarla
        // en este espacio es buena idea.
        std::getline(m_InputFileStream, aux);
    }

    InputReader::~InputReader() {
        m_InputFileStream.close();
    }

    bool InputReader::invalidInputFile() {
        return !m_InputFileStream;
    }
}