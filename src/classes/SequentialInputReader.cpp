//
// Created by rafael on 5/17/22.
//

#include "../headers/SequentialInputReader.h"

namespace cpyd {
    SequentialInputReader::SequentialInputReader(std::string &input)
            : InputReader(input) {}

    void SequentialInputReader::readFile() {
        const unsigned int CANT_ROWS = 100000;
        std::vector<char> buffer(ROW_LEN * CANT_ROWS, 0);

        std::vector<cpyd::Resultado> res;

        while(!m_InputFileStream.eof()) {
            m_InputFileStream.read(buffer.data(), (long) buffer.size());
            std::stringstream buffer_stream(buffer.data());

            std::vector<std::string> rows(CANT_ROWS, "");
            std::string aux;

            for (auto &row: rows) {
                std::getline(buffer_stream, row);
            }

            for (auto &row: rows) {
                if (row.empty()) {
                    continue;
                }
                row = processRow(row);
                res.emplace_back(row);
            }

            buffer = std::vector<char>(ROW_LEN * CANT_ROWS, 0);
//            res = std::vector<Resultado>();
        }
        std::sort(res.begin(), res.end(),
                  [](const auto& first, const auto& other){
                      if(first.m_puntaje_math < other.m_puntaje_math){
                          return false;
                      }

                      return other.m_puntaje_math < first.m_puntaje_math;
                  });
        std::stringstream s;

        std::string asdf = "dfg;0;0;0;0";
        res.resize(1000000, Resultado(asdf));
        for(auto &ress: res){
            s << ress.math_output() << '\n';
        }
        m_MathOFStream << s.str();
    }
}
