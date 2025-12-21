#ifndef TP_POO_2526_FERRAMENTA_H
#define TP_POO_2526_FERRAMENTA_H

#include "string"
#include <iostream>
#include "../Posicao.h"
class Jardim;

class Ferramenta {
private:
    static int contador;
    int numSerie;

public:
    Ferramenta();

    virtual ~Ferramenta();

    int getNumSerie() const;

    virtual bool usarFerramenta(Posicao& pos, Jardim& j, int l, int c) = 0;
    virtual char getTipoFerramenta() const = 0;
    virtual Ferramenta* clona() const = 0;
    virtual void listarDetalhes() const = 0;
};


#endif //TP_POO_2526_FERRAMENTA_H
