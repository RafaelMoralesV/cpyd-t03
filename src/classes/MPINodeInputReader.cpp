//
// Created by rafael on 5/28/22.
//

#include "../headers/MPINodeInputReader.h"

namespace cpyd {
    MPINodeInputReader::MPINodeInputReader(std::string &input, std::string &output) : MPIInputReader(input, output) {}

    void MPINodeInputReader::readFile() {
        readdataMPI();

        std::stringstream s(m_Data), out, fault_string;
        std::string row;

        while (std::getline(s, row)) {
            std::string word;
            std::stringstream rowstream(row);

            out << processRow(row) << std::endl;
        }

        std::string out_str = out.str();
        MPI::COMM_WORLD.Send(out_str.c_str(), (int) out_str.length() + 1, MPI_CHAR, 0, 0);
    }
} // cpyd