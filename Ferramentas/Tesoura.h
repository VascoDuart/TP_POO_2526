#ifndef TP_POO_2526_TESOURA_H
#define TP_POO_2526_TESOURA_H

#include "Ferramenta.h"
#include "../Posicao.h"
#include  "../Plantas/Planta.h"

class Tesoura : public Ferramenta {
public:
    Tesoura();

    ~Tesoura();

    bool usarFerramenta(Posicao& pos, Jardim& j, int l, int c) override;
    char getTipoFerramenta() const override;
    Ferramenta* clona() const override;
    void listarDetalhes() const override;
};


#endif //TP_POO_2526_TESOURA_H
