//
// Created by david on 24/10/2025.
//

#include "Simulador.h"

Simulador::Simulador()
    : jardim(nullptr), jardineiro(nullptr), interfaceGrelha(nullptr), instanteAtual(0)
{
}

Simulador::~Simulador() {
    delete jardim;
    delete jardineiro;
    delete interfaceGrelha;
}

void Simulador::iniciar() {
    cout << "Simulador iniciado!" << endl;

    while (true) {
        Comando cmd = lerComando();
        if (!cmd.isValido()) {
            cout << "Comando invalido. Tente novamente." << endl;
            continue;
        }

        executarComando(cmd);
    }
}

Comando Simulador::lerComando() const {
    cout << "Escreva o comando desejado: ";
    string linha;
    getline(cin, linha);
    return Comando(linha);
}

static std::string toLower(const std::string& s) {
    std::string out = s;
    std::transform(out.begin(), out.end(), out.begin(), ::tolower);
    return out;
}

void Simulador::executarComando(const Comando& cmd) {

    cmd.getComando();

    if (cmd.isValido()) {
        std::cout << "Comando válido." << std::endl;
    } else {
        std::cout << "Comando inválido." << std::endl;
    }

}

