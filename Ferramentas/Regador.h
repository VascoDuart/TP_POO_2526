//
// Created by david on 24/10/2025.
//

#ifndef TP_POO_2526_REGADOR_H
#define TP_POO_2526_REGADOR_H


#include "Ferramenta.h"
#include "../Settings.h"
#include "../Posicao.h"

class Regador : public Ferramenta {
public:

    Regador();

    void verificaCapacidade() const;
    void aplica(Posicao& pos) override;


private:
    int capacidade;
    static const int dose = Settings::Regador::dose;
};


#endif //TP_POO_2526_REGADOR_H
