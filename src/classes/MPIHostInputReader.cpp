//
// Created by rafael on 5/28/22.
//

#include "../headers/MPIHostInputReader.h"

namespace cpyd {
    MPIHostInputReader::MPIHostInputReader(std::string &input) : MPIInputReader(input) {
        if(m_rank != 0) {
            throw std::logic_error("Esta clase debe ser instanciada solo por el proceso principal");
        }
    }

    void MPIHostInputReader::readFile() {
        int chunk = 0;
        std::ofstream outputfile("./aux.csv");

        while (chunk * CHUNK_SIZE < m_InputFile.Get_size()) {
            readdataMPI(chunk++);

            std::stringstream dataStream(m_Data), processedRows;
            std::string row;

            while (std::getline(dataStream, row)) {
                std::stringstream rowstream(row);

                if (row.empty()) continue;

                processedRows << processRow(row) << std::endl;
            }

            outputfile << processedRows.str();
            for (int source = 1; source < m_size; source++) {
                char *buff = new char[m_DataLen + 1];
                MPI::COMM_WORLD.Recv(buff, (int) m_DataLen + 1, MPI_CHAR, source, 0);

                outputfile << buff;
                delete[] buff;
            }
        }
        outputfile.close();
    }
} // cpyd