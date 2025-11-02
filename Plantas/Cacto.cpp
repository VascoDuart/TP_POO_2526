#include "Cacto.h"

Cacto::Cacto()
        : Planta( 0,0,'C',Beleza::NEUTRA ),
          instantesMtAgua(0),
          instantesSemNutrientes(0)
{}

void Cacto::passaInstante(Posicao& solo) {
}

bool Cacto::verificaMorte(const Posicao& solo) const {
    return false;
}
Planta* Cacto::tentaMultiplicar() {
    return nullptr;
}
void Cacto::acaoAoSerRemovida(Posicao& solo) {
}
void Cacto::serPodada() { }