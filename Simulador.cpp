//
// Created by david on 24/10/2025.
//

#include <ctime>
#include <cstdlib>
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
    std::srand(std::time(0));

    std::cout << "Simulador iniciado!" << std::endl;

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

    std::string comando = cmd.getComando();
    const std::vector<std::string>& p = cmd.getParametros();

    if (comando == "jardim") {
        if (jardim == nullptr) {
            int linhas = std::stoi(p[0]);
            int colunas = std::stoi(p[1]);

            jardim = new Jardim(linhas, colunas);

            jardineiro = new Jardineiro();

            std::cout << "Jardim de " << linhas << "x" << colunas << " criado com sucesso." << std::endl;
        } else {
            std::cout << "Erro: O comando 'jardim' já foi executado." << std::endl;
        }
    }
    else if (jardim == nullptr) {
        std::cout << "Erro: O comando 'jardim <n> <n>' deve ser executado primeiro." << std::endl;
    }
    else if (comando == "fim") {
        std::cout << "A encerrar o simulador..." << std::endl;
        exit(0);
    }
    else {
        std::cout << "Comando '" << comando << "' válido, mas a funcionalidade não está implementada." << std::endl;
    }
}

