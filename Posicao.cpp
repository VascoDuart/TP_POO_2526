//
// Created by david on 24/10/2025.
//

#include "Posicao.h"

Posicao::Posicao()
    : agua(0), nutrientes(0), planta(nullptr), ferramenta(nullptr)
{
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

void Posicao::removePlanta() {
    delete planta;
    planta = nullptr;
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

void Posicao::removeFerramenta() {
    delete ferramenta;
    ferramenta = nullptr;
}

