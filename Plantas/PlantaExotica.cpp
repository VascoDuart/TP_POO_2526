#include "PlantaExotica.h"

PlantaExotica::PlantaExotica()
        : Planta( 50,50,'x',Beleza::NEUTRA )
{}

void PlantaExotica::passaInstante(Posicao& solo) {
    incrementaInstantes();

    int aguaSolo = solo.getAgua();
    int aAbsorver = std::min(aguaSolo, 2);
    solo.retiraAgua(aAbsorver);
    aguaInterna += aAbsorver;
}

void PlantaExotica::passaInstanteComJardim(Posicao& solo, Jardim& jardim, int l, int c) {

    this->passaInstante(solo);

    // Habilidade Especial: Raízes Longas (Nutrientes da própria posição)
    int nProprio = std::min(solo.getNutrientes(), 2);
    solo.retiraNutrientes(nProprio);
    nutrientesInternos += nProprio;

    // Habilidade Especial: Nutrientes da posição à direita
    if (jardim.ePosicaoValida(l, c + 1)) {
        Posicao& soloDireita = jardim.getPosicao(l, c + 1);
        int nDireita = std::min(soloDireita.getNutrientes(), 2);
        soloDireita.retiraNutrientes(nDireita);
        nutrientesInternos += nDireita;
        std::cout << "Planta Exotica em (" << (char)('A'+l) << (char)('A'+c)
                  << ") obteve nutrientes da direita." << std::endl;
    }
}

bool PlantaExotica::verificaMorte(const Posicao& solo) const {
    if (aguaInterna <= 0) {
        std::cout << "Planta Exotica morreu por desidratacao." << std::endl;
        return true;
    }

    // Condição específica: Se o solo estiver muito saturado de nutrientes (> 150)
    if (solo.getNutrientes() > 150) {
        std::cout << "Planta Exotica morreu por toxicidade de nutrientes no solo." << std::endl;
        return true;
    }

    return false;
}
Planta* PlantaExotica::tentaMultiplicar() {
    // Requisito: Ter nutrientes > 80 e água > 40
    if (nutrientesInternos > 80 && aguaInterna > 40) {

        // Cria o novo rebento com metade dos recursos
        int novaAgua = aguaInterna / 2;
        int novosNutrientes = nutrientesInternos / 2;

        aguaInterna -= novaAgua;
        nutrientesInternos -= novosNutrientes;

        PlantaExotica* novo = new PlantaExotica();
        novo->aguaInterna = novaAgua;
        novo->nutrientesInternos = novosNutrientes;

        std::cout << "Planta Exotica multiplicou-se!" << std::endl;
        return novo;
    }
    return nullptr;
}
void PlantaExotica::acaoAoSerRemovida(Posicao& solo) {
}
void PlantaExotica::serPodada() { }

Planta *PlantaExotica::clona() const {
    PlantaExotica* novaPExotica = new PlantaExotica(*this);
    return novaPExotica;
}
