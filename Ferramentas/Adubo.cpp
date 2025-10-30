//
// Created by david on 24/10/2025.
//

#include "Adubo.h"


Adubo::Adubo() : Ferramenta() {
 capacidade = Settings::Adubo::capacidade;
}

void Adubo::verificaCapacidade() const {
    if(capacidade<=0){
        std::cout << "Adubo sem capacidade!" << std::endl;
        Adubo::~Adubo();
    } else {
        std::cout << "Adubo com "<< capacidade <<" capacidade!" << std::endl;
    }
}

void Adubo::aplicaNutrientes(Posicao pos) {
    verificaCapacidade();
    if(capacidade>=dose){
        pos.adicionaNutrientes(dose);
        capacidade -= dose;
        std::cout << "Adubo aplicado com sucesso! Capacidade restante: " << capacidade << std::endl;
    } else {
        std::cout << "Adubo sem capacidade suficiente para aplicar dose!" << std::endl;
    }
    verificaCapacidade();
}

Adubo::~Adubo() {
    std::cout << "Adubo destruido" << std::endl;
}