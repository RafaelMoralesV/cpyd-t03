//
// Created by rafael on 7/17/22.
//

#ifndef CPYD_01_RESULTADO_H
#define CPYD_01_RESULTADO_H

#include <iostream>
#include <sstream>

namespace cpyd {

    class Resultado {
    private:
        std::string m_uuid;
        double m_puntaje;
        double m_puntaje_math;
        double m_puntaje_stem;
        double m_puntaje_hum;

    protected:
        Resultado();

    public:
        explicit Resultado(std::string &output_string);

        inline bool did_better_in_math(Resultado &other) const;
        inline bool did_better_in_stem(Resultado &other) const;
        inline bool did_better_in_hum(Resultado &other) const;

        [[nodiscard]] std::string math_output() const;
        [[nodiscard]] std::string stem_output() const;
        [[nodiscard]] std::string hum_output() const;

        [[nodiscard]] inline double getPuntajeMath() const;
        [[nodiscard]] inline double getPuntajeStem() const;
        [[nodiscard]] inline double getPuntajeHum() const;
        [[nodiscard]] inline double getPuntaje() const;
    };

} // cpyd

#endif //CPYD_01_RESULTADO_H
