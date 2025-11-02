#include "Roseira.h"

Roseira::Roseira()
        : Planta( 25,25,'R',Beleza::BONITA )
{}

void Roseira::passaInstante(Posicao& solo) {

}

bool Roseira::verificaMorte(const Posicao& solo) const {
    return false;
}
Planta* Roseira::tentaMultiplicar() {
    return nullptr;
}
void Roseira::acaoAoSerRemovida(Posicao& solo) {

}
void Roseira::serPodada() { }