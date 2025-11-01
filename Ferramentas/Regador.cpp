//
// Created by david on 24/10/2025.
//

#include "Regador.h"


Regador::Regador() : Ferramenta() {
 capacidade = Settings::Regador::capacidade;
}


void Regador::verificaCapacidade() const {
    if(capacidade<=0){
        std::cout << "Regador sem capacidade!" << std::endl;
        Regador::~Regador();
    } else {
        std::cout << "Regador com "<< capacidade <<" capacidade!" << std::endl;
    }
}

void Regador::aplica(Posicao& pos) {
    verificaCapacidade();
    if(capacidade>=dose){
        pos.adicionaAgua(dose);
        capacidade -= dose;
        std::cout << "Regador aplicado com sucesso! Capacidade restante: " << capacidade << std::endl;
    } else {
        std::cout << "Regador sem capacidade suficiente para aplicar dose!" << std::endl;
    }
    verificaCapacidade();
}
