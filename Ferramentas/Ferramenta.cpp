#include "Ferramenta.h"

int Ferramenta::contador = 0;

Ferramenta::Ferramenta() : numSerie(++contador) {
    std::cout << "Ferramenta criada com numero de serie: " << numSerie << std::endl;
}

Ferramenta::~Ferramenta() {
    std::cout << "Ferramenta com numero de serie " << numSerie << " destruida." << std::endl;
}

int Ferramenta::getNumSerie() const {
    return numSerie;
}

