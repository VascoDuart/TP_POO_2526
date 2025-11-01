#ifndef TP_POO_2526_ROSEIRA_H
#define TP_POO_2526_ROSEIRA_H


#include "Planta.h"
#include "../Settings.h"

class Roseira : public Planta{

public:
    Roseira();

    void passaInstante(Posicao& solo) override;
    bool verificaMorte(const Posicao& solo) const override;
    Planta* tentaMultiplicar() override;
    void acaoAoSerRemovida(Posicao& solo) override;
    void serPodada() override;
};


#endif //TP_POO_2526_ROSEIRA_H
