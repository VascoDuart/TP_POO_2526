//
// Created by vasco on 26/12/2025.
//

#ifndef TP_POO_2526_PESTICIDA_H
#define TP_POO_2526_PESTICIDA_H

#include "Ferramenta.h"

class Pesticida : public Ferramenta {
private:
    int doses;
public:
    Pesticida();
    ~Pesticida();
    bool usarFerramenta(Posicao& pos, Jardim& j, int l, int c) override;
    char getTipoFerramenta() const override;
    Ferramenta* clona() const override;
    void listarDetalhes() const override;
};


#endif //TP_POO_2526_PESTICIDA_H