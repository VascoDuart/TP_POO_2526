//
// Created by david on 24/10/2025.
//

#ifndef TP_POO_2526_ADUBO_H
#define TP_POO_2526_ADUBO_H


#include "Ferramenta.h"
#include "../Settings.h"
#include "../Posicao.h"

class Adubo : public Ferramenta {
public:
    Adubo();
    void verificaCapacidade() const;
    void aplica(Posicao& pos) override;




private:
    int capacidade;
    static const int dose = Settings::Adubo::dose;
};


#endif //TP_POO_2526_ADUBO_H
