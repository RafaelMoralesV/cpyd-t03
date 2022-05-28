//
// Created by rafael on 5/19/22.
//

#include "../headers/MPIInputReader.h"


namespace cpyd {
    MPIInputReader::MPIInputReader(std::string &input, std::string &output)
            : BaseInputReader(input, output) {
        m_rank = MPI::COMM_WORLD.Get_rank();
        m_size = MPI::COMM_WORLD.Get_size();

        m_Info = m_Info.Create();
        m_Info.Set("cb_config_list", "*:1");
        m_InputFile = m_InputFile.Open(MPI::COMM_WORLD, m_InputFilename.c_str(), MPI::MODE_RDONLY, m_Info);
    }

    void MPIInputReader::readFile() {
        const int overlap = 1;
        char *data;
        int ndata;

        readdataMPI(overlap, &data, &ndata);

        std::cout << "MPI: Rank " << m_rank << " has " << ndata << " characters." << std::endl;

        std::stringstream s(data), out, fault_string;
        std::string row;

        // El primer nodo siempre tiene la linea inicial, asi que vale la pena quitarsela nomas.
        if (m_rank == 0) std::getline(s, row);
        while (std::getline(s, row)) {
            std::string word;
            std::stringstream rowstream(row);

            out << processRow(row) << std::endl;
        }


        if (m_rank != 0) {
            std::string out_str = out.str();
            MPI::COMM_WORLD.Send(out_str.c_str(), (int) out_str.length() + 1, MPI_CHAR, 0, 0);
        } else {
            std::ofstream outputfile(this->m_OutputFilename);
            outputfile << out.str();
            for (int source = 1; source < m_size; source++) {
                char *buff = new char[ndata + 1];
                MPI::COMM_WORLD.Recv(buff, ndata + 1, MPI_CHAR, source, 0);

                outputfile << buff;
                delete[] buff;
            }

            outputfile.close();
        }

        delete[] data;

        m_InputFile.Close();
    }

    void MPIInputReader::partitionFile(const int overlap, int *start, int *end) const {
        const int FIRST_LINE = sizeof(char) * 190;

        const int relevant_filesize = (int) m_InputFile.Get_size() - FIRST_LINE;

        const int lines = relevant_filesize / 87;

        int localsize = (lines / m_size) * 87;
        *start = FIRST_LINE + (m_rank * localsize);
        *end = FIRST_LINE + (*start + localsize - 1);

        if (m_rank != 0) *start -= overlap;
        if (m_rank != m_size - 1) *end += overlap;
    }

    void MPIInputReader::readdataMPI(const int overlap, char **data, int *ndata) {
        int start;
        int end;

        // figure out who reads what

        partitionFile(overlap, &start, &end);

        *ndata = end - start + 1;

        // allocate memory
        *data = new char[*ndata + 1];

        // everyone reads in their part
        m_InputFile.Read_at_all(MPI::Offset(start), *data, *ndata, MPI::CHAR);
        (*data)[*ndata] = '\0';
    }

    bool MPIInputReader::invalidInputFile() {
        std::ifstream file(m_InputFilename);
        bool invalid = !file;
        file.close();
        return invalid;
    }

    bool MPIInputReader::invalidOutputFile() {
        std::ofstream file(m_OutputFilename);
        bool invalid = !file;
        file.close();
        return invalid;
    }
} // cpyd