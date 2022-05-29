//
// Created by rafael on 5/19/22.
//

#include "../headers/MPIInputReader.h"


namespace cpyd {
    MPIInputReader::MPIInputReader(std::string &input, std::string &output)
            : BaseInputReader(input, output), m_Data(nullptr),  m_DataLen(0){
        m_rank = MPI::COMM_WORLD.Get_rank();
        m_size = MPI::COMM_WORLD.Get_size();

        m_Info = m_Info.Create();
        m_Info.Set("cb_config_list", "*:1");
        m_InputFile = m_InputFile.Open(MPI::COMM_WORLD, m_InputFilename.c_str(), MPI::MODE_RDONLY, m_Info);
    }

    void MPIInputReader::readdataMPI(int chunk_number) {
        int start;
        int end;

        partitionFile(chunk_number, &start, &end);

        m_DataLen = end - start + 1;
        m_Data = new char[m_DataLen + 1];

        m_InputFile.Read_at_all(MPI::Offset(start), m_Data, (int) m_DataLen, MPI::CHAR);
        (m_Data)[m_DataLen] = '\0';
    }

    void MPIInputReader::partitionFile(int chunk_number, int *start, int *end) const {

        int chunk_start = FIRST_LINE_LEN + CHUNK_SIZE * chunk_number;

        int localsize = CHUNK_SIZE / m_size;
        *start = chunk_start + (m_rank * localsize);
        *end = *start + localsize - 1;

        int last_byte = (int) m_InputFile.Get_size();

        if(*start > last_byte) *start = last_byte;
        if(*end > last_byte) *end = last_byte;
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

    MPIInputReader::~MPIInputReader() {
        m_InputFile.Close();
        m_Info.Free();

        delete [] m_Data;
    }
} // cpyd