#include "Adubo.h"

Adubo::Adubo() : Ferramenta() {
    capacidade = Settings::Adubo::capacidade;
    std::cout << "Adubo criado!" << std::endl;
}

Adubo::~Adubo() {
    std::cout << "Adubo destruido!" << std::endl;
}

bool Adubo::usarFerramenta(Posicao &pos, Jardim &j, int l, int c) {
    if (capacidade > 0) {
        int quantidadeAplicar = (capacidade < dose) ? capacidade : dose;

        pos.adicionaNutrientes(quantidadeAplicar);
        capacidade -= quantidadeAplicar;

        std::cout << "Adubo aplicado! Adicionadas " << quantidadeAplicar
                  << " unidades de nutrientes. Capacidade restante: " << capacidade << std::endl;
    }

    if (capacidade <= 0) {
        std::cout << "O pacote de adubo (ID: " << getNumSerie() << ") esgotou e sera descartado." << std::endl;
        return true;
    }

    return false;
}

char Adubo::getTipoFerramenta() const {
    return 'a';
}

void Adubo::listarDetalhes() const {
    std::cout << "Capacidade: " << capacidade << "/" << Settings::Adubo::capacidade
              << " (Dose: " << dose << ")";
}

Ferramenta *Adubo::clona() const {
    Adubo* novo = new Adubo();
    novo->capacidade = this->capacidade;
    return novo;
}
