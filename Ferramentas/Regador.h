#ifndef TP_POO_2526_REGADOR_H
#define TP_POO_2526_REGADOR_H

#include "Ferramenta.h"
#include "../Settings.h"
#include "../Posicao.h"

class Regador : public Ferramenta {
private:
    static const int dose = Settings::Regador::dose;
    int capacidade;

public:
    Regador();

    ~Regador();
    
    bool usarFerramenta(Posicao& pos, Jardim& j, int l, int c) override;
    char getTipoFerramenta() const override;
    Ferramenta* clona() const override;
    void listarDetalhes() const override;
};


#endif //TP_POO_2526_REGADOR_H
