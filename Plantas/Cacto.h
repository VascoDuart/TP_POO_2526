#ifndef TP_POO_2526_CACTO_H
#define TP_POO_2526_CACTO_H

#include "Planta.h"
#include "../Settings.h"
#include "../Posicao.h"

class Cacto : public Planta {
private:
    int instantesMtAgua;
    int instantesSemNutrientes;
    int nutrientesAbsorvidosTotal;

public:
    Cacto();

    void passaInstante(Posicao& solo) override;
    bool verificaMorte(const Posicao& solo) const override;
    Planta* tentaMultiplicar() override;
    void acaoAoSerRemovida(Posicao& solo) override;
    void serPodada() override;
    Planta* clona() const override;
};


#endif //TP_POO_2526_CACTO_H
