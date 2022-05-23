//
// Created by rafael on 5/19/22.
//

#include "../headers/MPIInputReader.h"

namespace cpyd {
    MPIInputReader::MPIInputReader(std::string & input, std::string & output)
        : InputReader(input, output), m_input(input), m_output(output){ }

    void MPIInputReader::readFile() {
        MPI_File in;
        int rank, size;
        int ierr;

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

        delete [] data;

        MPI_File_close(&in);
        MPI_Info_free(&info);
    }

    void partitionFile(const int filesize, const int rank, const int size,
                       const int overlap, int *start, int *end) {
        int localsize = filesize/size;
        *start = rank * localsize;
        *end   = *start + localsize-1;

        if (rank != 0)      *start -= overlap;
        if (rank != size-1) *end   += overlap;
    }

    void readdataMPI(MPI_File *in, const int rank, const int size, const int overlap,
                     char **data, int *ndata) {
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
                             (MPI_Offset)(*ndata), MPI_CHAR, MPI_STATUS_IGNORE);
        (*data)[*ndata] = '\0';
    }
} // cpyd