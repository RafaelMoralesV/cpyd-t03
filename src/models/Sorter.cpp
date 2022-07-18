//
// Created by rafael on 7/17/22.
//

#include "../headers/Sorter.h"

namespace cpyd {
    void Sorter::sort() {
        std::ifstream m_aux("./aux.csv");

        std::ofstream m_maths("./matematicas.csv");
        std::ofstream m_stem("./ciencias.csv");
        std::ofstream m_humanities("./humanities.csv");
        m_maths << "Identificador de estudiante;Puntaje de área específica;Puntaje" << std::endl;
        m_stem << "Identificador de estudiante;Puntaje de área específica;Puntaje" << std::endl;
        m_humanities << "Identificador de estudiante;Puntaje de área específica;Puntaje" << std::endl;

        std::vector<Resultado*> math;
        std::vector<Resultado*> stem;
        std::vector<Resultado*> hum;

        while(!m_aux.eof()){
            std::string aux;
            std::getline(m_aux, aux);
            if(aux.empty()) continue;
            auto* res = new Resultado(aux);

            math.push_back(res);
            stem.push_back(res);
            hum.push_back(res);
        }
        m_aux.close();

        std::sort(math.begin(), math.end(), [](Resultado* a, Resultado* b){
            if(a->m_puntaje_math < b->m_puntaje_math){
                return false;
            }
            return b->m_puntaje < a->m_puntaje;
        });

        std::sort(stem.begin(), stem.end(), [](Resultado* a, Resultado* b){
            if(a->m_puntaje_stem < b->m_puntaje_stem){
                return false;
            }
            return b->m_puntaje < a->m_puntaje;
        });

        std::sort(hum.begin(), hum.end(), [](Resultado* a, Resultado* b){
            if(a->m_puntaje_hum < b->m_puntaje_hum){
                return false;
            }
            return b->m_puntaje < a->m_puntaje;
        });

        for(int i = 0; i < 1000000; i++){
            m_maths         << math[i]->math_output()   << std::endl;
            m_stem          << stem[i]->stem_output()   << std::endl;
            m_humanities    << hum[i]->hum_output()     << std::endl;
        }
    }


} // cpyd