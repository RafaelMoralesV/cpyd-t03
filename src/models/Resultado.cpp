//
// Created by rafael on 7/17/22.
//

#include "../headers/Resultado.h"


namespace cpyd {
    /**************** CONSTRUCTORES ****************/
    Resultado::Resultado():
    m_puntaje(0),
    m_puntaje_math(0),
    m_puntaje_stem(0),
    m_puntaje_hum(0) { }

    Resultado::Resultado(std::string &output_string) {
        std::stringstream stream(output_string);

        std::getline(stream, m_uuid, ';');

        std::string word;
        std::getline(stream, word, ';');
        m_puntaje_math = std::stod(word);

        std::getline(stream, word, ';');
        m_puntaje_stem = std::stod(word);

        std::getline(stream, word, ';');
        m_puntaje_hum = std::stod(word);

        std::getline(stream, word, ';');
        m_puntaje = std::stod(word);
    }

    /**************** GETTERS ****************/
    inline double Resultado::getPuntajeMath() const {
        return m_puntaje_math;
    }

    inline double Resultado::getPuntajeStem() const {
        return m_puntaje_stem;
    }

    inline double Resultado::getPuntajeHum() const {
        return m_puntaje_hum;
    }

    inline double Resultado::getPuntaje() const {
        return m_puntaje;
    }

    /**************** COMPARADORES ****************/
    inline bool Resultado::did_better_in_math(Resultado &other) const {
        if(this->getPuntajeMath() < other.getPuntajeMath()){
            return false;
        }

        return other.getPuntaje() < this->getPuntaje();
    }

    inline bool Resultado::did_better_in_stem(Resultado &other) const {
        if(this->getPuntajeStem() < other.getPuntajeStem()){
            return false;
        }
        return other.getPuntaje() < this->getPuntaje();
    }

    inline bool Resultado::did_better_in_hum(Resultado &other) const {
        if(this->getPuntajeHum() < other.getPuntajeHum()){
            return false;
        }
        return other.getPuntaje() < this->getPuntaje();
    }

    /**************** OUTPUT STRINGS ****************/
    std::string Resultado::math_output() const {
        std::stringstream output;

        output  << this->m_uuid         << ';'
                << this->m_puntaje_math << ';'
                << this->m_puntaje;

        return output.str();
    }

    std::string Resultado::stem_output() const {
        std::stringstream output;

        output << this->m_uuid          << ';'
               << this->m_puntaje_stem  << ';'
               << this->m_puntaje;

        return output.str();
    }

    std::string Resultado::hum_output() const {
        std::stringstream output;

        output << this->m_uuid          << ';'
               << this->m_puntaje_hum   << ';'
               << this->m_puntaje;

        return output.str();
    }
} // cpyd