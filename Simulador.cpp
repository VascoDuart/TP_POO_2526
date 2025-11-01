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

    jardineiro = new Jardineiro();

    while (true) {
        Comando cmd = lerComando();
        if (!cmd.isValido()) {
            std::cout << cmd.getMsgErro() << std::endl;
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
    bool estadoAlterado = false;

    if (comando == "jardim") {
        if (jardim == nullptr) {
            int linhas = std::stoi(p[0]);
            int colunas = std::stoi(p[1]);

            jardim = new Jardim(linhas, colunas);
            jardineiro = new Jardineiro();
            interfaceGrelha = new InterfaceGrelha(*jardim, *jardineiro);
            estadoAlterado = true;

            std::cout << "Jardim de " << linhas << "x" << colunas << " criado com sucesso." << std::endl;
        } else {
            std::cout << "Erro: O comando 'jardim' ja foi executado." << std::endl;
        }
    }
    else if (jardim == nullptr) {
        std::cout << "Erro: O comando 'jardim <n> <n>' deve ser executado primeiro." << std::endl;
    }

    //Comandos adicionais de caracter geral
    else if (comando == "grava") {
        std::cout << "A gravar o estado do jardim no ficheiro '" << p[0] << "'..." << std::endl;
        estadoAlterado = true;
    }
    else if (comando == "recupera") {
        std::cout << "A recuperar o estado do jardim do ficheiro '" << p[0] << "'..." << std::endl;
        estadoAlterado = true;
    }
    else if (comando == "apaga") {
        std::cout << "A apagar o ficheiro '" << p[0] << "'..." << std::endl;
    }
    else if (comando == "executa") {
        std::cout << "A executar comandos do ficheiro '" << p[0] << "'..." << std::endl;
    }

    //Comandos para o movimento do jardineiro
    else if (comando == "e") {
        std::cout << "Jardineiro move-se uma posicao para a esquerda" << std::endl;
        estadoAlterado = true;
    }
    else if (comando == "d"){
        std::cout << "Jardineiro move-se uma posicao para a direita" << std::endl;
        estadoAlterado = true;
    }
    else if (comando == "c"){
        std::cout << "Jardineiro move-se uma posicao para cima" << std::endl;
        estadoAlterado = true;
    }
    else if (comando == "b"){
        std::cout << "Jardineiro move-se uma posicao para baixo" << std::endl;
        estadoAlterado = true;
    }
    else if (comando == "entra") {
        std::cout << "Jardineiro entra no jardim nas coordenadas " << p[0] << std::endl;
        estadoAlterado = true;
    }
    else if (comando == "sai") {
        std::cout << "Jardineiro sai do jardim" << std::endl;
        estadoAlterado = true;
    }

    //Comandos para acoes

    else if (comando == "colhe") {
        std::cout << "Jardineiro colhe na posicao " << p[0] << std::endl;
        estadoAlterado = true;
    }
    else if (comando == "planta") {
        std::cout << "Jardineiro planta " << p[1] <<" na posicao " << p[0] << std::endl;
        estadoAlterado = true;
    }
    else if (comando == "larga") {
        std:cout << "Jardineiro larga a ferramenta que esta' na sua mao" << std::endl;
        estadoAlterado = true;
    }
    else if (comando == "pega") {
        std::cout << "Jardineiro pega na ferramenta" << std::endl;
        estadoAlterado = true;
    }
    else if (comando == "compra") {
        std::cout << "Jardineiro compra uma ferramenta do tipo " << p[0] << std::endl;
        estadoAlterado = true;
    }

    //Comandos para lista informacao

    else if (comando == "lplantas") {
        std::cout << "Lista de todas as plantas do jardim" << std::endl;
    }
    else if (comando == "lplanta") {
        std::cout << "Lista de informacao da planta na posicao " << p[0] << std::endl;
    }
    else if (comando == "larea") {
        std::cout << "Informacao da area do jardim" << std::endl;
    }
    else if (comando == "lsolo") {

        std::cout << "--- Informacao do Solo ---" << std::endl;
        std::cout << "Posicao (l.c): " << p[0];

        if (p.size() == 2) {
            std::cout << " (com area: " << p[1] << ")";
        }

        std::cout << std::endl;

        return;
    }
    else if (comando == "lferr") {
        std::cout << "Lista de todas as ferramentas do jardineiro" << std::endl;
    }

    //Comandos para o tempo simulado
    else if (comando == "avanca") {

        int numPassos = 1;

        if (p.empty()) {
            std::cout << "A avancar o tempo em 1 passo (default)..." << std::endl;
        } else {
            try {
                numPassos = std::stoi(p[0]);
                std::cout << "A avancar o tempo em " << numPassos << " passos..." << std::endl;
            } catch (const std::exception& e) {
                std::cout << "Erro interno na conversão de passos." << std::endl;
                return;
            }
        }
        estadoAlterado = true;
    }

    else if (comando == "fim") {
        std::cout << "A encerrar o simulador..." << std::endl;
        exit(0);
    }
    else {
        std::cout << "Comando '" << comando << "' valido, mas a funcionalidade nao esta implementada." << std::endl;
    }

    if (jardim != nullptr && interfaceGrelha != nullptr && estadoAlterado) {
        interfaceGrelha->desenharJardim();
    }
}

