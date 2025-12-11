#ifndef TP_POO_2526_ROSEIRA_H
#define TP_POO_2526_ROSEIRA_H


#include "Planta.h"
#include "../Settings.h"
#include "../Posicao.h"

class Roseira : public Planta{
private:
    int instantesComVizinhosEmTodasAsPosicoes;
    int nutrientesAbsorvidosTotal;

public:
    Roseira();

    void setRodeada(bool rodeada);

    void passaInstante(Posicao& solo) override;
    bool verificaMorte(const Posicao& solo) const override;
    Planta* tentaMultiplicar() override;
    void acaoAoSerRemovida(Posicao& solo) override;
    void serPodada() override;
    Planta* clona() const override;
};


#endif //TP_POO_2526_ROSEIRA_H
