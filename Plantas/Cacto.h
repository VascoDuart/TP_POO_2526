#ifndef TP_POO_2526_CACTO_H
#define TP_POO_2526_CACTO_H


#include "Planta.h"
#include "../Settings.h"

class Cacto : public Planta {
    int instantesMtAgua;
    int instantesSemNutrientes;

public:
    Cacto();

    void passaInstante(Posicao& solo) ;
    bool verificaMorte(const Posicao& solo) const ;
    Planta* tentaMultiplicar() ;
    void acaoAoSerRemovida(Posicao& solo) ;
    void serPodada() ;
};


#endif //TP_POO_2526_CACTO_H
