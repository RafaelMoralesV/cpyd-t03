//
// Created by rafael on 5/17/22.
//

#ifndef CPYD_01_INPUTREADER_H
#define CPYD_01_INPUTREADER_H

#include <sstream>
#include <fstream>

#include "BaseInputReader.h"

namespace cpyd {
    /**
     * Implementación basada en std::filestreams, utilizada para algoritmos secuenciales y OpenMP.
     * Esta clase básica no implementa readFile, por lo que no es instanciable, sino que se encarga de
     * la creacion y cierre de un input file stream y output file stream.
     */
    class InputReader : public BaseInputReader {
    protected:
        InputReader(std::string &inputFilename, std::string &outputFilename);

        std::ifstream m_InputFileStream;
        std::ofstream m_OutputFileStream;
    public:
        bool invalidInputFile() override;

        bool invalidOutputFile() override;

        ~InputReader();
    };
}

#endif //CPYD_01_INPUTREADER_H
