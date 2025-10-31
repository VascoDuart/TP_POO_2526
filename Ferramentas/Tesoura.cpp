//
// Created by david on 24/10/2025.
//

#include "Tesoura.h"

Tesoura::Tesoura() : Ferramenta() {
    std::cout << "Tesoura criada!" << std::endl;
}

void Tesoura::cortaPlanta(Posicao& pos) {

    if (!pos.temPlanta()) {
        std::cout << "Nao ha planta para cortar nesta posicao!" << std::endl;
        return;
    }

    Planta* p = pos.getPlanta();

    if(p->getBeleza() == Beleza::FEIA){
        p->acaoAoSerRemovida(pos);
        pos.removePlanta();
        std::cout << "Planta feia cortada e removida do jardim!" << std::endl;
    }

}

Tesoura::~Tesoura() {
    std::cout << "Tesoura destruida!" << std::endl;
}