#include "Planta.h"

Planta::Planta(int agua, int nutrientes, char tipo, Beleza belezaTipo)
    : aguaInterna(agua), nutrientesInternos(nutrientes), tipoPlanta(tipo), beleza(belezaTipo), tempoVida(0) {}

Planta::~Planta() {

}

int Planta::getAguaInterna() const { return aguaInterna; }

char Planta::getTipoPlanta() const { return tipoPlanta; }

Beleza Planta::getBeleza() const { return beleza; }

int Planta::getTempoVida() const { return tempoVida; }


void Planta::incrementaInstantes() { tempoVida++; }


