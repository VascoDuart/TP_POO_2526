//
// Created by david on 24/10/2025.
//

#ifndef TP_POO_2526_FERRAMENTA_H
#define TP_POO_2526_FERRAMENTA_H
#include "string"
#include <iostream>
#include "../Posicao.h"

class Ferramenta {
public:

    Ferramenta();

    virtual void aplica(Posicao& pos);

    virtual ~Ferramenta();

private:
    static int numSerie;

};


#endif //TP_POO_2526_FERRAMENTA_H
