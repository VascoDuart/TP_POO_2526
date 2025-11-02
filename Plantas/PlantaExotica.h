#ifndef TP_POO_2526_PLANTAEXOTICA_H
#define TP_POO_2526_PLANTAEXOTICA_H


#include "Planta.h"

class PlantaExotica : public Planta {
public:
    PlantaExotica();

    void passaInstante(Posicao& solo) override;
    bool verificaMorte(const Posicao& solo) const override;
    Planta* tentaMultiplicar() override;
    void acaoAoSerRemovida(Posicao& solo) override;
    void serPodada() override;
};


#endif //TP_POO_2526_PLANTAEXOTICA_H
