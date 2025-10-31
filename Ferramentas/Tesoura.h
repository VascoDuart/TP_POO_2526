//
// Created by david on 24/10/2025.
//

#ifndef TP_POO_2526_TESOURA_H
#define TP_POO_2526_TESOURA_H


#include "Ferramenta.h"
#include "../Posicao.h"
#include  "../Plantas/Planta.h"

class Tesoura : public Ferramenta {
public:
    Tesoura();

    void cortaPlanta(Posicao& pos);

    ~Tesoura();

};


#endif //TP_POO_2526_TESOURA_H
