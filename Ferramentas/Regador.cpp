#include "Regador.h"

Regador::Regador() : Ferramenta() {
    capacidade = Settings::Regador::capacidade;
    std::cout << "Regador criado!" << std::endl;
}

Regador::~Regador() {
    std::cout << "Regador destruido!" << std::endl;
}

bool Regador::usarFerramenta(Posicao &pos, Jardim &j, int l, int c) {
    if (capacidade > 0) {
        int quantidadeAplicar = (capacidade < dose) ? capacidade : dose;

        pos.adicionaAgua(quantidadeAplicar);
        capacidade -= quantidadeAplicar;

        std::cout << "Regador utilizado! Adicionadas " << quantidadeAplicar
                  << " unidades de agua. Capacidade restante: " << capacidade << std::endl;
    }

    if (capacidade <= 0) {
        std::cout << "O regador (ID: " << getNumSerie() << ") esgotou e sera descartado." << std::endl;
        return true;
    }

    return false;
}

char Regador::getTipoFerramenta() const {
    return 'g';
}

void Regador::listarDetalhes() const {
    std::cout << "Capacidade: " << capacidade << "/" << Settings::Regador::capacidade
              << " (Dose: " << dose << ")";
}

Ferramenta *Regador::clona() const {
    Regador* novo = new Regador();
    novo->capacidade = this->capacidade;
    return novo;
}

