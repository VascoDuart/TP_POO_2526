//
// Created by david on 24/10/2025.
//

#include "Jardim.h"

Jardim::Jardim(int linhas, int colunas)
    : numLinhas(linhas), numColunas(colunas)
{
    grelha = new Posicao*[numLinhas];
    for (int i = 0; i < numLinhas; ++i) {
        grelha[i] = new Posicao[numColunas];
    }
}

Jardim::~Jardim() {
    for (int i = 0; i < numLinhas; ++i) {
        delete[] grelha[i];
    }
    delete[] grelha;
}