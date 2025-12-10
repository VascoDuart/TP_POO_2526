#include "Regador.h"

Regador::Regador() : Ferramenta() {
    capacidade = Settings::Regador::capacidade;
}

Regador::~Regador() {
    std::cout << "Regador destruido!" << std::endl;
}

bool Regador::usarFerramenta(Posicao &pos, Jardim &j, int l, int c) {
    if (capacidade >= dose) {
        pos.adicionaAgua(dose);
        capacidade -= dose;
        std::cout << "Regador aplicado! Adicionadas " << dose << " unidades de agua. Capacidade restante: " << capacidade << std::endl;
    } else {
        std::cout << "Regador vazio (ID: " << getNumSerie() << "). Nao foi possivel aplicar a dose de agua." << std::endl;
    }

    if (capacidade <= 0) {
        std::cout << "O regador esgotou! Sera descartado." << std::endl;
        return true;
    }

    return false;
}

char Regador::getTipoFerramenta() const {
    return 'g';
}

Ferramenta *Regador::clona() const {
    Regador* novo = new Regador();
    novo->capacidade = this->capacidade;
    return novo;
}

