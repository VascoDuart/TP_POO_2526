#include <ctime>
#include <cstdlib>
#include "Simulador.h"
#include "Plantas/Cacto.h"
#include "Plantas/Roseira.h"
#include "Plantas/ErvaDaninha.h"
#include "Plantas/PlantaExotica.h"
#include "Ferramentas/Regador.h"
#include "Ferramentas/Adubo.h"
#include "Ferramentas/Tesoura.h"

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

std::pair<int, int> comandoParaCoordenadas(const std::string& pos) {
    if (pos.length() != 2) return {-1, -1};
    int linha = tolower(pos[0]) - 'a';
    int coluna = tolower(pos[1]) - 'a';
    return {linha, coluna};
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
        if (jardineiro->move('e', *jardim)) {
            std::cout << "Jardineiro moveu-se para a esquerda." << std::endl;
            estadoAlterado = true;
        } else {
            std::cout << "Erro: Nao foi possivel mover para a esquerda." << std::endl;
        }
    }
    else if (comando == "d"){
        if (jardineiro->move('d', *jardim)) {
            std::cout << "Jardineiro moveu-se para a direita." << std::endl;
            estadoAlterado = true;
        } else {
            std::cout << "Erro: Nao foi possivel mover para a direita." << std::endl;
        }
    }
    else if (comando == "c"){
        if (jardineiro->move('c', *jardim)) {
            std::cout << "Jardineiro moveu-se para cima." << std::endl;
            estadoAlterado = true;
        } else {
            std::cout << "Erro: Nao foi possivel mover para cima." << std::endl;
        }
    }
    else if (comando == "b"){
        if (jardineiro->move('b', *jardim)) {
            std::cout << "Jardineiro moveu-se para baixo." << std::endl;
            estadoAlterado = true;
        } else {
            std::cout << "Erro: Nao foi possivel mover para baixo." << std::endl;
        }
    }
    else if (comando == "entra") {
        std::pair<int, int> coords = comandoParaCoordenadas(p[0]);
        int l = coords.first;
        int c = coords.second;

        if (jardineiro->entraNoJardim(l, c, *jardim)) {
            std::cout << "Jardineiro entrou no jardim nas coordenadas " << p[0] << std::endl;
            estadoAlterado = true;

        } else {
            std::cout << "Erro: Nao foi possivel entrar no jardim na posicao " << p[0] << ". (Verifique os limites, se ja esta dentro, ou se tem acoes de entrada)." << std::endl;
        }
    }
    else if (comando == "sai") {
        if (jardineiro->saiDoJardim()) {
            std::cout << "Jardineiro saiu do jardim" << std::endl;
            estadoAlterado = true;
        } else {
            std::cout << "Erro: Nao foi possivel sair do jardim. (Verifique se ja esta fora ou se atingiu o limite de acoes)." << std::endl;
        }
    }

    //Comandos para acoes

    else if (comando == "colhe") {
        jardineiro->colhe(*jardim);
        std::cout << "Jardineiro colhe na posicao " << p[0] << std::endl;
        estadoAlterado = true;
    }
    else if (comando == "planta") {

        std::pair<int, int> coords = comandoParaCoordenadas(p[0]);
        int l = coords.first;
        int c = coords.second;
        char tipo = tolower(p[1][0]);

        if (!jardim->ePosicaoValida(l, c)) {
            std::cout << "Erro: Posicao '" << p[0] << "' fora dos limites do jardim." << std::endl;
            return;
        }

        Planta* novaPlanta = nullptr;

        switch(tipo) {
            case 'c': novaPlanta = new Cacto(); break;
            case 'r': novaPlanta = new Roseira(); break;
            case 'e': novaPlanta = new ErvaDaninha(); break;
            //case 'x': novaPlanta = new PlantaExotica(); break;
        }

        if (novaPlanta != nullptr) {
            jardim->adicionaObjeto(l, c, novaPlanta);
            jardineiro->planta(*jardim, tipo);
            std::cout << "Jardineiro planta " << p[1] <<" na posicao " << p[0] << std::endl;
            estadoAlterado = true;
        }
    }
    else if (comando == "larga") {
        std::cout << "Jardineiro larga a ferramenta que esta' na sua mao" << std::endl;
        estadoAlterado = true;
    }
    else if (comando == "pega") {
        std::cout << "Jardineiro pega na ferramenta" << std::endl;
        estadoAlterado = true;
    }
    else if (comando == "compra") {
        char tipo = tolower(p[0][0]);
        Ferramenta* novaFerramenta = nullptr;

        switch (tipo) {
            case 'g': novaFerramenta = new Regador(); break;
            case 'a': novaFerramenta = new Adubo(); break;
            case 't': novaFerramenta = new Tesoura(); break;
            case 'z':
                std::cout << "Ferramenta 'Z' nao implementada." << std::endl;
                return;
        }

        if (novaFerramenta != nullptr) {
            jardineiro->pegaFerramenta(novaFerramenta);
            std::cout << "Jardineiro compra uma ferramenta do tipo " << p[0] << " (ID: " << novaFerramenta->getNumSerie() << ")." << std::endl;
            estadoAlterado = true;
        }
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

        std::pair<int, int> coords = comandoParaCoordenadas(p[0]);
        int l = coords.first;
        int c = coords.second;

        if (!jardim->ePosicaoValida(l, c)) {
            std::cout << "Erro: Posicao '" << p[0] << "' fora dos limites do jardim." << std::endl;
            return;
        }

        const Posicao& pos = jardim->getPosicao(l, c);

        std::cout << "--- Informacao do Solo (" << p[0] << ") ---" << std::endl;
        std::cout << "Agua: " << pos.getAgua() << std::endl;
        std::cout << "Nutrientes: " << pos.getNutrientes() << std::endl;

        if (pos.temPlanta()) {
            Planta* planta = pos.getPlanta();
            std::cout << "Planta presente (Tipo: " << planta->getTipoPlanta()
                      << ", Beleza: " << (int)planta->getBeleza()
                      << ", Tempo de Vida: " << planta->getTempoVida() << " instantes)" << std::endl;
        }
        if (pos.temFerramenta()) {
            Ferramenta* ferramenta = pos.getFerramenta();
            std::cout << "Ferramenta presente (Tipo: " << ferramenta->getTipoFerramenta()
                      << ", ID: " << ferramenta->getNumSerie() << ")" << std::endl;
        }

        // Lógica de lsolo com área (p[1]) não implementada.
        return;
    }
    else if (comando == "lferr") {
        std::cout << "Lista de todas as ferramentas do jardineiro" << std::endl;
    }

    //Comandos para o tempo simulado
    else if (comando == "avanca") {

        int numInstantes = 1;

        if (p.empty()) {
            std::cout << "A avancar o tempo em 1 instante (default)..." << std::endl;
        } else {
            try {
                numInstantes = std::stoi(p[0]);
                std::cout << "A avancar o tempo em " << numInstantes << " instantes..." << std::endl;
            } catch (const std::exception& e) {
                std::cout << "Erro interno na conversão de instantes." << std::endl;
                return;
            }
        }

        avancarInstante(numInstantes);

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

void Simulador::avancarInstante(int numInstantes) {
    for (int i = 0; i < numInstantes; ++i) {
        jardim->passaInstante();

        instanteAtual++;

        jardineiro->resetContadoresAcoes();
    }
}

