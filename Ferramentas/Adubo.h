#ifndef TP_POO_2526_ADUBO_H
#define TP_POO_2526_ADUBO_H

#include "Ferramenta.h"
#include "../Settings.h"
#include "../Posicao.h"

class Adubo : public Ferramenta {
private:
    static const int dose = Settings::Adubo::dose;
    int capacidade;

public:
    Adubo();

    ~Adubo();

    bool usarFerramenta(Posicao& pos, Jardim& j, int l, int c) override;
    char getTipoFerramenta() const override;
    Ferramenta* clona() const override;
};


#endif //TP_POO_2526_ADUBO_H
