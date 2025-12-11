#include "ErvaDaninha.h"

ErvaDaninha::ErvaDaninha()
        : Planta( Settings::ErvaDaninha::inicial_agua, Settings::ErvaDaninha::inicial_nutrientes,'e',Beleza::FEIA ),
            instantesDesdeMultiplicacao(0)
{}

void ErvaDaninha::passaInstante(Posicao& solo) {
    incrementaInstantes();
    instantesDesdeMultiplicacao++;

    int aguaSoloAntes = solo.getAgua();
    solo.retiraAgua(Settings::ErvaDaninha::absorcao_agua);
    aguaInterna += (aguaSoloAntes - solo.getAgua());

    int nutrientesSoloAntes = solo.getNutrientes();
    solo.retiraNutrientes(Settings::ErvaDaninha::absorcao_nutrientes);
    nutrientesInternos += (nutrientesSoloAntes - solo.getNutrientes());
}

bool ErvaDaninha::verificaMorte(const Posicao& solo) const {
    if (getTempoVida() >= Settings::ErvaDaninha::morre_instantes) {
        std::cout << "Erva Daninha (ID: E) morreu: Atingiu o limite de vida (" << getTempoVida() << " instantes)." << std::endl;
        return true;
    }
    return false;
}

Planta* ErvaDaninha::tentaMultiplicar() {
    if (nutrientesInternos > Settings::ErvaDaninha::multiplica_nutrientes_maior &&
        instantesDesdeMultiplicacao >= Settings::ErvaDaninha::multiplica_instantes) {
        ErvaDaninha* novo = new ErvaDaninha();
        novo->aguaInterna = 5;
        novo->nutrientesInternos = Settings::ErvaDaninha::nova_nutrientes;

        instantesDesdeMultiplicacao = 0;

        std::cout << "Erva Daninha (ID: E) multiplicou! A mae nao perdeu recursos." << std::endl;

        return novo;
    }
    return nullptr;
}

void ErvaDaninha::acaoAoSerRemovida(Posicao& solo) {

}

void ErvaDaninha::serPodada() {

}

Planta *ErvaDaninha::clona() const {
    ErvaDaninha* novaErva = new ErvaDaninha(*this);
    return novaErva;
}
