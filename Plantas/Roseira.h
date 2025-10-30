#ifndef TP_POO_2526_ROSEIRA_H
#define TP_POO_2526_ROSEIRA_H


#include "Planta.h"
#include "../Settings.h"

class Roseira : public Planta{

public:
    Roseira();

    void passaInstante(Posicao& solo) ;
    bool verificaMorte(const Posicao& solo) const ;
    Planta* tentaMultiplicar() ;
    void acaoAoSerRemovida(Posicao& solo) ;
    void serPodada() ;
};


#endif //TP_POO_2526_ROSEIRA_H
