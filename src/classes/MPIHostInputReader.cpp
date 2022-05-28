//
// Created by rafael on 5/28/22.
//

#include "../headers/MPIHostInputReader.h"

namespace cpyd {
    MPIHostInputReader::MPIHostInputReader(std::string &input, std::string &output) : MPIInputReader(input, output) {}

    void MPIHostInputReader::readFile() {
        const int overlap = 1;
        char *data;
        int ndata;

        readdataMPI(overlap, &data, &ndata);

        //std::cout << "MPI: Rank " << m_rank << " has " << ndata << " characters." << std::endl;

        std::stringstream s(data), out, fault_string;
        std::string row;

        // El primer nodo siempre tiene la linea inicial, asi que vale la pena quitarsela nomas.
        if (m_rank == 0) std::getline(s, row);
        while (std::getline(s, row)) {
            std::string word;
            std::stringstream rowstream(row);

            out << processRow(row) << std::endl;
        }

        std::ofstream outputfile(this->m_OutputFilename);
        outputfile << out.str();
        for (int source = 1; source < m_size; source++) {
            char *buff = new char[ndata + 1];
            MPI::COMM_WORLD.Recv(buff, ndata + 1, MPI_CHAR, source, 0);

            outputfile << buff;
            delete[] buff;
        }

        outputfile.close();

        delete[] data;

        m_InputFile.Close();
    }
} // cpyd