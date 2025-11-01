//
// Created by david on 24/10/2025.
//

#include "Ferramenta.h"

int Ferramenta::numSerie = 0;

Ferramenta::Ferramenta() {
    numSerie +=1;
    std::cout << "Ferramenta criada com numero de serie: " << numSerie << std::endl;
}

Ferramenta::~Ferramenta() {
    std::cout << "Ferramenta com numero de serie " << numSerie << " destruida." << std::endl;
}