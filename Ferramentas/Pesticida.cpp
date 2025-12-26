//
// Created by vasco on 26/12/2025.
//

#include "Pesticida.h"

Pesticida::Pesticida() : Ferramenta(), doses(3) {
    std::cout << "Pesticida (ID: " << getNumSerie() << ") comprado com 3 doses." << std::endl;
}

Pesticida::~Pesticida() {
    if (doses==0)
        std::cout << "Pesticida (ID: " << getNumSerie() << ") esgotado e descartado!" << std::endl;
    else
    std::cout << "Pesticida (ID: " << getNumSerie() << ") destruido!" << std::endl;
}

bool Pesticida::usarFerramenta(Posicao &pos, Jardim &j, int l, int c) {
    if (doses <= 0) {
        std::cout << "Pesticida vazio!" << std::endl;
        return true;
    }

    if (pos.temPlanta()) {
        Planta* p = pos.getPlanta();
        std::cout << "Pesticida a ser aplicado" << std::endl;

        p->acaoAoSerRemovida(pos);
        delete pos.removePlanta();
        doses--;
        std::cout << "Doses restantes: " << doses << std::endl;
    } else {
        std::cout << "Nao ha plantas nesta posicao para aplicar o pesticida." << std::endl;
    }

    if (doses <= 0) {
        std::cout << "O pesticida (ID: " << getNumSerie() << ") esgotou e sera descartado." << std::endl;
        return true;
    }

    return false;
}

char Pesticida::getTipoFerramenta() const { return 'z'; }

Ferramenta* Pesticida::clona() const {
    Pesticida* novo = new Pesticida();
    novo->doses = this->doses;
    return novo;
}

void Pesticida::listarDetalhes() const {
    std::cout << "Doses: " << doses << "/3";
}