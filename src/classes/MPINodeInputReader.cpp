//
// Created by rafael on 5/28/22.
//

#include "../headers/MPINodeInputReader.h"

namespace cpyd {
    MPINodeInputReader::MPINodeInputReader(std::string &input) : MPIInputReader(input) {
        if(m_rank == 0) {
            throw std::logic_error("Esta clase debe ser instanciada solo por los procesos adicionales");
        }
    }

    void MPINodeInputReader::readFile() {
        int chunk = 0;
        while (chunk * CHUNK_SIZE < m_InputFile.Get_size()) {
            readdataMPI(chunk++);

            std::stringstream s(m_Data), out;
            std::string row;

            while (std::getline(s, row)) {
                std::stringstream rowstream(row);

                if (row.empty()) continue;

                out << processRow(row) << std::endl;
            }

            std::string out_str = out.str();
            MPI::COMM_WORLD.Send(out_str.c_str(), (int) out_str.length() + 1, MPI_CHAR, 0, 0);
        }
    }
} // cpyd