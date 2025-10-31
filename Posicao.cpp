//
// Created by david on 24/10/2025.
//

#include "Posicao.h"
#include "Settings.h"

Posicao::Posicao()
        : planta(nullptr), ferramenta(nullptr)
{
    agua = (std::rand() % (Settings::Jardim::agua_max - Settings::Jardim::agua_min + 1)) + Settings::Jardim::agua_min;
    nutrientes = (std::rand() % (Settings::Jardim::nutrientes_max - Settings::Jardim::nutrientes_min + 1)) + Settings::Jardim::nutrientes_min;
}

int Posicao::getAgua() const {
    return agua;
}

void Posicao::adicionaAgua(int valor) {
    agua += valor;
}

void Posicao::retiraAgua(int valor) {
    agua -= valor;
    if (agua < 0) {
        agua = 0;
    }
}

int Posicao::getNutrientes() const {
    return nutrientes;
}

void Posicao::adicionaNutrientes(int valor) {
    nutrientes += valor;
}

void Posicao::retiraNutrientes(int valor) {
    nutrientes -= valor;
    if (nutrientes < 0) {
        nutrientes = 0;
    }
}

bool Posicao::temPlanta() const {
    return planta != nullptr;
}

Planta* Posicao::getPlanta() const {
    return planta;
}

void Posicao::setPlanta(Planta* p) {
    planta = p;
}

Planta* Posicao::removePlanta() {
    Planta* temp = planta;
    planta = nullptr;
    return temp;
}

bool Posicao::temFerramenta() const {
    return ferramenta != nullptr;
}

Ferramenta* Posicao::getFerramenta() const {
    return ferramenta;
}

void Posicao::setFerramenta(Ferramenta* f) {
    ferramenta = f;
}

Ferramenta* Posicao::removeFerramenta() {
    Ferramenta* temp = ferramenta;
    ferramenta = nullptr;
    return temp;
}

