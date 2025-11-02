#include "ErvaDaninha.h"

ErvaDaninha::ErvaDaninha()
        : Planta( 5,5,'E',Beleza::FEIA ),
            instantesDesdeMultiplicacao(0)
{}

void ErvaDaninha::passaInstante(Posicao& solo) {
}

bool ErvaDaninha::verificaMorte(const Posicao& solo) const {
    return false;
}
Planta* ErvaDaninha::tentaMultiplicar() {
    return nullptr;
}
void ErvaDaninha::acaoAoSerRemovida(Posicao& solo) {
}
void ErvaDaninha::serPodada() { }