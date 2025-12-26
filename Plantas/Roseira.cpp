#include "Roseira.h"

Roseira::Roseira()
        : Planta( Settings::Roseira::inicial_agua, Settings::Roseira::inicial_nutrientes, 'r', Beleza::BONITA ),
          instantesComVizinhosEmTodasAsPosicoes(0),
          nutrientesAbsorvidosTotal(0)
{}

void Roseira::passaInstante(Posicao& solo) {
    incrementaInstantes();

    aguaInterna -= Settings::Roseira::perda_agua;
    aguaInterna = std::max(0, aguaInterna);
    nutrientesInternos -= Settings::Roseira::perda_nutrientes;
    nutrientesInternos = std::max(0, nutrientesInternos);

    int aguaSoloAntes = solo.getAgua();
    solo.retiraAgua(Settings::Roseira::absorcao_agua);
    int aguaRetiradaReal = aguaSoloAntes - solo.getAgua();
    aguaInterna += aguaRetiradaReal;

    int nutrientesSoloAntes = solo.getNutrientes();
    solo.retiraNutrientes(Settings::Roseira::absorcao_nutrientes);
    int nutrientesRetiradosReal = nutrientesSoloAntes - solo.getNutrientes();
    nutrientesInternos += nutrientesRetiradosReal;
    nutrientesAbsorvidosTotal += nutrientesRetiradosReal;
}

bool Roseira::verificaMorte(const Posicao& solo) const {
    if (aguaInterna <  Settings::Roseira::morre_agua_menor || nutrientesInternos < Settings::Roseira::morre_nutrientes_menor) {
        std::cout << "Roseira (ID: r) morreu: Esgotamento interno de recursos." << std::endl;
        return true;
    }

    if (nutrientesInternos > Settings::Roseira::morre_nutrientes_maior) {
        std::cout << "Roseira (ID: r) morreu: Excesso de nutrientes acumulados (>= 200)." << std::endl;
        return true;
    }

    if (instantesComVizinhosEmTodasAsPosicoes > 0) {
        std::cout << "Roseira (ID: r) morreu: Rodeada em todas as posicoes vizinhas." << std::endl;
        return true;
    }

    return false;
}

Planta* Roseira::tentaMultiplicar() {
    if (nutrientesInternos > Settings::Roseira::multiplica_nutrientes_maior) {

        int novaAgua = aguaInterna * Settings::Roseira::nova_agua_percentagem / 100;
        int novosNutrientes = Settings::Roseira::nova_nutrientes;

        if (aguaInterna >= novaAgua && nutrientesInternos >= novosNutrientes) {
            Roseira* novo = new Roseira();
            novo->aguaInterna = novaAgua;
            novo->nutrientesInternos = novosNutrientes;

            aguaInterna = aguaInterna * Settings::Roseira::original_agua_percentagem / 100;
            nutrientesInternos = Settings::Roseira::original_nutrientes;

            std::cout << "Roseira (ID: r) multiplicou! Recursos divididos." << std::endl;
            return novo;
        }
    }
    return nullptr;
}

void Roseira::acaoAoSerRemovida(Posicao& solo) {
    int nutrientesDevolver = nutrientesAbsorvidosTotal / 2;
    int aguaDevolver = aguaInterna / 2;

    if (nutrientesDevolver > 0) {
        solo.adicionaNutrientes(nutrientesDevolver);
    }
    if (aguaDevolver > 0) {
        solo.adicionaAgua(aguaDevolver);
    }
}

void Roseira::serPodada() { }

Planta *Roseira::clona() const {
    Roseira* novaRoseira = new Roseira(*this);
    return novaRoseira;
}

void Roseira::setRodeada(bool rodeada) {
    if (rodeada) {
        instantesComVizinhosEmTodasAsPosicoes++;
    } else {
        instantesComVizinhosEmTodasAsPosicoes = 0;
    }
}

