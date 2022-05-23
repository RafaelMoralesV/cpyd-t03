//
// Created by rafael on 5/19/22.
//

#include "../headers/MPIInputReader.h"

namespace cpyd {
    MPIInputReader::MPIInputReader(std::string & input, std::string & output)
        : InputReader(input, output), m_input(input), m_output(output){
        csvFile.close();
    }

    void MPIInputReader::readFile() {
        MPI_File in;
        int rank, size;

        MPI_Comm_rank(MPI_COMM_WORLD, &rank);
        MPI_Comm_size(MPI_COMM_WORLD, &size);

        MPI_Info info;
        MPI_Info_create(&info);
        MPI_Info_set(info, "cb_config_list","*:1"); // ROMIO: one reader per node
        // Eventually, should be able to use io_nodes_list or similar

        MPI_File_open(MPI_COMM_WORLD, m_input.c_str(), MPI_MODE_RDONLY, info, &in);

        const int overlap=1;
        char *data;
        int ndata;
        readdataMPI(&in, rank, size, overlap, &data, &ndata);

        std::cout << "MPI: Rank " << rank << " has " << ndata << " characters." << std::endl;

        std::stringstream s(data), out, fault_string;
        std::string row;
        if(rank == 0) std::getline(s, row);
        while(std::getline(s, row)){
            std::string word;
            std::stringstream rowstream(row);

            if(row.length() < 86){
                if(rank == 0) {
                    fault_string << row;
                    continue;
                }
                // La linea es menor a lo esperado.
                MPI_Send(&row, (int) row.length() + 1, MPI_CHAR, 0, 1, MPI_COMM_WORLD);
                continue;
            }

            out << processRow(row) << std::endl;
        }


        if(rank != 0) {
            std::string out_str = out.str();
            MPI_Send(&out_str, (int) out_str.length(), MPI_CHAR, 0, 0, MPI_COMM_WORLD);
        }
        else {
            std::string out_str;
            output << out.str();
            for(int source = 1; source < size; source++) {
                MPI_Status status;
                MPI_Recv(&out_str, ndata, MPI_CHAR, source, 0, MPI_COMM_WORLD, &status);

                std::cout << "SOURCE " << source << ": " << out_str << std::endl;

                output << out_str;
            }
        }

        delete [] data;

        MPI_File_close(&in);
        MPI_Info_free(&info);
    }

    void partitionFile(const int filesize, const int rank, const int size, const int overlap, int *start, int *end) {
        int localsize = filesize/size;
        *start = rank * localsize;
        *end   = *start + localsize-1;

        if (rank != 0)      *start -= overlap;
        if (rank != size-1) *end   += overlap;
    }

    void readdataMPI(MPI_File *in, const int rank, const int size, const int overlap, char **data, int *ndata) {
        MPI_Offset filesize;
        int start;
        int end;

        // figure out who reads what

        MPI_File_get_size(*in, &filesize);
        partitionFile((int)filesize, rank, size, overlap, &start, &end);

        *ndata =  end - start + 1;

        // allocate memory
        *data = new char[*ndata + 1];

        // everyone reads in their part
        MPI_File_read_at_all(*in, (MPI_Offset)start, *data,
                             (int)(MPI_Offset)(*ndata), MPI_CHAR, MPI_STATUS_IGNORE);
        (*data)[*ndata] = '\0';
    }
} // cpyd