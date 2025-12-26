#include "Cacto.h"
#include <iostream>

Cacto::Cacto()
        : Planta( 0,0,'c',Beleza::NEUTRA ),
          instantesMtAgua(0),
          instantesSemNutrientes(0),
          nutrientesAbsorvidosTotal(0)
{}

void Cacto::passaInstante(Posicao& solo) {
    incrementaInstantes();

    int aguaSoloAntes = solo.getAgua();
    int aguaAbsorver = aguaSoloAntes * Settings::Cacto::absorcao_agua_percentagem / 100;
    solo.retiraAgua(aguaAbsorver);
    int aguaSoloDepois = solo.getAgua();
    int aguaRetiradaReal = aguaSoloAntes - aguaSoloDepois;
    aguaInterna += aguaRetiradaReal;

    int nutrientesSoloAntes = solo.getNutrientes();
    int nutrientesAbsorver = Settings::Cacto::absorcao_nutrientes;
    solo.retiraNutrientes(nutrientesAbsorver);
    int nutrientesSoloDepois = solo.getNutrientes();
    int nutrientesRetiradosReal = nutrientesSoloAntes - nutrientesSoloDepois;
    nutrientesInternos += nutrientesRetiradosReal;
    nutrientesAbsorvidosTotal += nutrientesRetiradosReal;

    if (solo.getAgua() > Settings::Cacto::morre_agua_solo_maior) {
        instantesMtAgua++;
    } else {
        instantesMtAgua = 0;
    }

    if (solo.getNutrientes() <= Settings::Cacto::morre_nutrientes_solo_menor) {
        instantesSemNutrientes++;
    } else {
        instantesSemNutrientes = 0;
    }
}

bool Cacto::verificaMorte(const Posicao& solo) const {
    if (instantesMtAgua >= Settings::Cacto::morre_agua_solo_instantes) {
        std::cout << "Cacto morreu: Excesso de agua no solo (" << instantesMtAgua << " instantes)." << std::endl;
        return true;
    }

    if (instantesSemNutrientes > Settings::Cacto::morre_nutrientes_solo_instantes) {
        std::cout << "Cacto morreu: Falta de nutrientes no solo (" << instantesSemNutrientes << " instantes)." << std::endl;
        return true;
    }

    return false;
}

Planta* Cacto::tentaMultiplicar() {
    if(nutrientesInternos > Settings::Cacto::multiplica_nutrientes_maior && aguaInterna > Settings::Cacto::multiplica_agua_maior){
        int novosNutrientes = nutrientesInternos / 2;
        int novaAgua = aguaInterna / 2;
        nutrientesInternos -= novosNutrientes;
        aguaInterna -= novaAgua;

        Cacto* novo = new Cacto();
        novo->aguaInterna = novaAgua;
        novo->nutrientesInternos = novosNutrientes;

        std::cout << "Cacto (ID: " << getTipoPlanta() << ") multiplicou! Recursos divididos: (" << novaAgua << "/" << novosNutrientes << ")" << std::endl;
        return novo;
    }
    return nullptr;
}

void Cacto::acaoAoSerRemovida(Posicao& solo) {
    if (nutrientesAbsorvidosTotal > 0) {
        solo.adicionaNutrientes(nutrientesAbsorvidosTotal);
        std::cout << "Cacto devolveu " << nutrientesAbsorvidosTotal << " unidades de nutrientes ao solo." << std::endl;
        nutrientesAbsorvidosTotal = 0;
    }
}

void Cacto::serPodada() {

}

Planta* Cacto::clona() const {
    Cacto* novoCacto = new Cacto(*this);
    return novoCacto;
}