//
// Created by rafael on 5/19/22.
//
#include "../headers/InputReader.h"

namespace cpyd {
    InputReader::InputReader(std::string &inputFilename, std::string &outputFilename)
            : BaseInputReader(inputFilename, outputFilename), m_InputFileStream(inputFilename),
              m_OutputFileStream(outputFilename) {
        std::string aux;

        // La primera linea contiene informacion meta sobre que es cada columna, por lo que eliminarla
        // en este espacio es buena idea.
        std::getline(m_InputFileStream, aux);
    }

    InputReader::~InputReader() {
        m_InputFileStream.close();
        m_OutputFileStream.close();
    }

    bool InputReader::invalidInputFile() {
        return !m_InputFileStream;
    }

    bool InputReader::invalidOutputFile() {
        return !m_OutputFileStream;
    }
}