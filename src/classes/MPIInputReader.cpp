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

    void MPIInputReader::readdataMPI() {
        int start;
        int end;

        // figure out who reads what

        partitionFile(&start, &end);

        m_DataLen = end - start + 1;

        // allocate memory
        m_Data = new char[m_DataLen + 1];

        // everyone reads in their part
        m_InputFile.Read_at_all(MPI::Offset(start), m_Data, (int) m_DataLen, MPI::CHAR);
        (m_Data)[m_DataLen] = '\0';
    }

    void MPIInputReader::partitionFile(int *start, int *end) const {
        const int FIRST_LINE = sizeof(char) * 190;

        const int relevant_filesize = (int) m_InputFile.Get_size() - FIRST_LINE;

        const int lines = relevant_filesize / 87;

        int localsize = (lines / m_size) * 87;
        *start = FIRST_LINE + (m_rank * localsize);
        *end = FIRST_LINE + (*start + localsize - 1);

        if (m_rank != 0) *start -= OVERLAP;
        if (m_rank != m_size - 1) *end += OVERLAP;
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