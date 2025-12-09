#include "Adubo.h"

Adubo::Adubo() : Ferramenta() {
    capacidade = Settings::Adubo::capacidade;
}

bool Adubo::usarFerramenta(Posicao &pos, Jardim &j, int l, int c) {
    if (capacidade >= dose) {
        pos.adicionaNutrientes(dose);
        capacidade -= dose;
        std::cout << "Adubo aplicado! Adicionadas " << dose << " unidades de nutrientes. Capacidade restante: " << capacidade << std::endl;
    } else {
        std::cout << "Adubo vazio (ID: " << getNumSerie() << "). Nao foi possivel aplicar a dose de nutrientes." << std::endl;
    }

    if (capacidade <= 0) {
        std::cout << "O pacote de adubo esgotou e foi levado pelo vento! Sera descartado." << std::endl;
        return true;
    }

    return false;
}

char Adubo::getTipoFerramenta() const {
    return 'a';
}

Ferramenta *Adubo::clona() const {
    Adubo* novo = new Adubo();
    novo->capacidade = this->capacidade;
    return novo;
}
