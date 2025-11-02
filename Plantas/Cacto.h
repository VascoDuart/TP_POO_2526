#ifndef TP_POO_2526_CACTO_H
#define TP_POO_2526_CACTO_H


#include "Planta.h"
#include "../Settings.h"

class Cacto : public Planta {
    int instantesMtAgua;
    int instantesSemNutrientes;

public:
    Cacto();

    void passaInstante(Posicao& solo) override;
    bool verificaMorte(const Posicao& solo) const override;
    Planta* tentaMultiplicar() override;
    void acaoAoSerRemovida(Posicao& solo) override;
    void serPodada() override;
};


#endif //TP_POO_2526_CACTO_H
