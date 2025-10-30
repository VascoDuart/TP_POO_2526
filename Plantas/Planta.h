#ifndef TP_POO_2526_PLANTA_H
#define TP_POO_2526_PLANTA_H

#include <iostream>
#include <string>
#include "../Settings.h"
#include "../Posicao.h"

enum class Beleza {
    NEUTRA,
    FEIA,
    BONITA
};

class Planta {
    int aguaInterna, nutrientesInternos;
    char tipoPlanta;
    Beleza beleza;
    int tempoVida;

public:
    Planta(int agua, int nutrientes, char tipo, Beleza belezaTipo);
        : aguaInterna(agua), nutrientesInternos(nutrientes), tipoPlanta(tipo), beleza(belezaTipo), tempoVida(0) {};

    virtual ~Planta() = default;

    int getAguaInterna() const { return aguaInterna; }
    char getTipoPlanta() const { return tipoPlanta; }
    Beleza getBeleza() const { return beleza; }
    int getTempoVida() const { return tempoVida; }

    void incrementaInstantes() { tempoVida++; }
    virtual void passaInstante(Posicao& solo) = 0;

    virtual bool verificaMorte(const Posicao& solo) const = 0;
    virtual Planta* tentaMultiplicar() = 0;
    virtual void acaoAoSerRemovida(Posicao& solo) = 0;
    virtual void serPodada() = 0;
};


#endif //TP_POO_2526_PLANTA_H
