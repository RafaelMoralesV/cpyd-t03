//
// Created by rafael on 5/28/22.
//

#include "../headers/MPIHostInputReader.h"

namespace cpyd {
    MPIHostInputReader::MPIHostInputReader(std::string &input, std::string &output) : MPIInputReader(input, output) {}

    void MPIHostInputReader::readFile() {
        readdataMPI();

        std::stringstream dataStream(m_Data), processedRows;
        std::string row;

        while (std::getline(dataStream, row)) {
            std::string word;
            std::stringstream rowstream(row);

            processedRows << processRow(row) << std::endl;
        }

        std::ofstream outputfile(this->m_OutputFilename);
        outputfile << processedRows.str();
        for (int source = 1; source < m_size; source++) {
            char *buff = new char[m_DataLen + 1];
            MPI::COMM_WORLD.Recv(buff, (int) m_DataLen + 1, MPI_CHAR, source, 0);

            outputfile << buff;
            delete[] buff;
        }

        outputfile.close();
    }
} // cpyd