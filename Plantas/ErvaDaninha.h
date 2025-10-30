#ifndef TP_POO_2526_ERVADANINHA_H
#define TP_POO_2526_ERVADANINHA_H


#include "Planta.h"
#include "../Settings.h"

class ErvaDaninha : public Planta{
    int instantesDesdeMultiplicacao;

public:
    ErvaDaninha();

    void passaInstante(Posicao& solo) override;
    bool verificaMorte(const Posicao& solo) const override; // Depende do instantesVida
    Planta* tentaMultiplicar() override;
    void acaoAoSerRemovida(Posicao& solo) override;
    void serPodada() override;
};


#endif //TP_POO_2526_ERVADANINHA_H
