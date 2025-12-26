#ifndef TP_POO_2526_PLANTAEXOTICA_H
#define TP_POO_2526_PLANTAEXOTICA_H


#include "Planta.h"
#include "../Jardim.h"

class PlantaExotica : public Planta {
public:
    PlantaExotica();

    void passaInstante(Posicao& solo) override;
    void passaInstanteComJardim(Posicao& solo, Jardim& jardim, int l, int c);
    bool verificaMorte(const Posicao& solo) const override;
    Planta* tentaMultiplicar() override;
    void acaoAoSerRemovida(Posicao& solo) override;
    void serPodada() override;
    Planta* clona() const override;
};


#endif //TP_POO_2526_PLANTAEXOTICA_H
