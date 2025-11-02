#include "PlantaExotica.h"

PlantaExotica::PlantaExotica()
        : Planta( 50,50,'E',Beleza::BONITA )
{}

void PlantaExotica::passaInstante(Posicao& solo) {
}
bool PlantaExotica::verificaMorte(const Posicao& solo) const {
    return false;
}
Planta* PlantaExotica::tentaMultiplicar() {
    return nullptr;
}
void PlantaExotica::acaoAoSerRemovida(Posicao& solo) {
}
void PlantaExotica::serPodada() { }