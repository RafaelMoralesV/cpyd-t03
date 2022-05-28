//
// Created by rafael on 5/19/22.
//

#include "../headers/MPIInputReader.h"


namespace cpyd {
    MPIInputReader::MPIInputReader(std::string & input, std::string & output)
        : InputReader(input, output), m_input(input), m_output(output){
        this->m_InputFileStream.close();
        this->m_OutputFileStream.close();
    }

    void MPIInputReader::readFile() {
        MPI_File in;
        int rank, size;

        MPI_Comm_rank(MPI_COMM_WORLD, &rank);
        MPI_Comm_size(MPI_COMM_WORLD, &size);

        MPI_Info info;
        MPI_Info_create(&info);
        MPI_Info_set(info, "cb_config_list","*:1");

        MPI_File_open(MPI_COMM_WORLD, m_input.c_str(), MPI_MODE_RDONLY, info, &in);

        const int overlap=1;
        char *data;
        int ndata;
        readdataMPI(&in, rank, size, overlap, &data, &ndata);

        std::cout << "MPI: Rank " << rank << " has " << ndata << " characters." << std::endl;

        std::stringstream s(data), out, fault_string;
        std::string row;

        // El primer nodo siempre tiene la linea inicial, asi que vale la pena quitarsela nomas.
        if(rank == 0) std::getline(s, row);
        while(std::getline(s, row)){
            std::string word;
            std::stringstream rowstream(row);

            out << processRow(row) << std::endl;
        }


        if(rank != 0) {
            std::string out_str = out.str();
            MPI_Send(out_str.c_str(), (int) out_str.length() + 1, MPI_CHAR, 0, 0, MPI_COMM_WORLD);
        }
        else {
            std::ofstream outputfile(this->m_output);
            outputfile << out.str();
            for(int source = 1; source < size; source++) {
                MPI_Status status;
                char* buff = new char[ndata + 1];
                MPI_Recv(buff, ndata + 1, MPI_CHAR, source, 0, MPI_COMM_WORLD, &status);

                outputfile << buff;
                delete [] buff;
            }

            outputfile.close();
        }

        delete [] data;

        MPI_File_close(&in);
        MPI_Info_free(&info);
    }

    void partitionFile(const int filesize, const int rank, const int size, const int overlap, int *start, int *end) {
        const int FIRST_LINE = sizeof(char) * 190;
        const int relevant_filesize = filesize - FIRST_LINE;

        const int lines = relevant_filesize / 87;

        int localsize = (lines/size) * 87;
        *start = FIRST_LINE + (rank * localsize);
        *end   = FIRST_LINE + (*start + localsize-1);

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