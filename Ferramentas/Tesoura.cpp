#include "Tesoura.h"

Tesoura::Tesoura() : Ferramenta() {
    std::cout << "Tesoura criada!" << std::endl;
}

Tesoura::~Tesoura() {
    std::cout << "Tesoura destruida!" << std::endl;
}

bool Tesoura::usarFerramenta(Posicao &pos, Jardim &j, int l, int c) {
    if (pos.temPlanta()) {
        Planta* p = pos.getPlanta();

        if(p->getBeleza() == Beleza::FEIA){
            std::cout << "A tesoura removeu a planta feia na posicao " << (char)('a'+l) << (char)('a'+c) << " (ID: " << getNumSerie() << ")" << std::endl;
            p->acaoAoSerRemovida(pos);
            Planta* plantaRemovida = pos.removePlanta();
            delete plantaRemovida;
        } else {
            std::cout << "A planta na posicao " << (char)('a'+l) << (char)('a'+c) << " nao e feia. A tesoura nao pode remover." << std::endl;
        }
    } else {
        std::cout << "Nao ha planta para cortar nesta posicao!" << std::endl;
    }
    return false;
}

char Tesoura::getTipoFerramenta() const {
    return 't';
}

Ferramenta *Tesoura::clona() const {
    return new Tesoura(*this);
}
