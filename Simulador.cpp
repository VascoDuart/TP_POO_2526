#include <ctime>
#include <cstdlib>
#include "Simulador.h"

#include <fstream>

#include "Plantas/Cacto.h"
#include "Plantas/Roseira.h"
#include "Plantas/ErvaDaninha.h"
#include "Plantas/PlantaExotica.h"
#include "Ferramentas/Regador.h"
#include "Ferramentas/Adubo.h"
#include "Ferramentas/Tesoura.h"
#include "Ferramentas/Pesticida.h"

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

    if (comando == "executa") {
        std::cout << "A executar comandos do ficheiro '" << p[0] << "'..." << std::endl;
        ifstream ficheiro(p[0]);
        ifstream ficheiroLinha1(p[0]);

        if (ficheiro.is_open()) {
            string linha;
            string linha1;
            char marcador = ' ';
            getline(ficheiroLinha1, linha1, marcador);

            if (jardim == nullptr &&  linha1 != "jardim") {
                int linhas = 4;
                int colunas = 4;

                jardim = new Jardim(linhas, colunas);
                jardineiro = new Jardineiro();
                interfaceGrelha = new InterfaceGrelha(*jardim, *jardineiro);
                estadoAlterado = true;
            }

            while (getline(ficheiro, linha)) {
                cout << "Comando do ficheiro: " << linha << std::endl;
                Comando cmd_ficheiro(linha);
                if (cmd_ficheiro.isValido()) {
                    executarComando(cmd_ficheiro);
                } else {
                    std::cout << "Erro no ficheiro '" << p[0] << "': " << cmd_ficheiro.getMsgErro() << std::endl;
                }
            }
            ficheiro.close();
            std::cout << "Execucao do ficheiro '" << p[0] << "' concluida." << std::endl;
        }
        else
            std::cout << "Erro: Nao foi possivel abrir o ficheiro '" << p[0] << "'." << std::endl;
    }
    else if (comando == "jardim") {
        if (jardim == nullptr) {
            int linhas = std::stoi(p[0]);
            int colunas = std::stoi(p[1]);

            jardim = new Jardim(linhas, colunas);
            jardineiro = new Jardineiro();
            interfaceGrelha = new InterfaceGrelha(*jardim, *jardineiro);
            estadoAlterado = true;

            for (int i = 0; i < 3; ++i) {
                jardim->gerarFerramentaAleatoria();
            }

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
        std::string nome = p[0];
        copiasJardins[nome]= jardim->clona();
        std::cout << "Jardim '" << nome << "' guardado com sucesso." << std::endl;
        estadoAlterado = true;
    }
    else if (comando == "recupera") {
        std::cout << "A recuperar o estado do jardim do ficheiro '" << p[0] << "'..." << std::endl;
        std::string nome = p[0];
        if (copiasJardins.count(nome)) {    //talvez trocar para contains
            delete jardim;
            jardim = copiasJardins[nome];
            copiasJardins.erase(nome);

            delete interfaceGrelha;
            interfaceGrelha = new InterfaceGrelha(*jardim, *jardineiro);
            std::cout << "Jardim '" << nome << "' recuperado com sucesso." << std::endl;
            estadoAlterado = true;
        }
        else
            std::cout << "Erro: Nao foi possivel encontrar o ficheiro '" << nome << "'." << std::endl;
    }
    else if (comando == "apaga") {
        std::cout << "A apagar o ficheiro '" << p[0] << "'..." << std::endl;
        string nome = p[0];
        if (copiasJardins.count(nome)) {
            delete copiasJardins[nome];
            copiasJardins.erase(nome);
            std::cout << "Ficheiro '" << nome << "' apagado com sucesso." << std::endl;
            estadoAlterado = true;      //CONFIRMAR SE É NECESSARIO AQUI!!!!
        }
        else
            std::cout << "Erro: Nao foi possivel encontrar o ficheiro '" << nome << "'." << std::endl;

    }
 /*   else if (comando == "executa") {
        std::cout << "A executar comandos do ficheiro '" << p[0] << "'..." << std::endl;
        ifstream ficheiro(p[0]);
        if (ficheiro.is_open()) {
            string linha;
            while (getline(ficheiro, linha)) {
                Comando cmd_ficheiro(linha);
                if (cmd_ficheiro.isValido()) {
                    executarComando(cmd_ficheiro);
                } else {
                    std::cout << "Erro no ficheiro '" << p[0] << "': " << cmd_ficheiro.getMsgErro() << std::endl;
                }
            }
            ficheiro.close();
            std::cout << "Execucao do ficheiro '" << p[0] << "' concluida." << std::endl;
        }
        else
            std::cout << "Erro: Nao foi possivel abrir o ficheiro '" << p[0] << "'." << std::endl;
    }*/

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

        const Posicao& pos = jardim->getPosicao(l, c);
        if (pos.temPlanta()) {
            std::cout << "Erro: Ja existe uma planta (" << pos.getPlanta()->getTipoPlanta() << ") na posicao " << p[0] << "." << std::endl;
            return;
        }

        if (pos.temFerramenta()) {
            std::cout << "Erro: Nao e possivel plantar. A posicao " << p[0] << " ja contem uma ferramenta." << std::endl;
            return;
        }

        if (jardineiro->getPlantacoesRestantes() <= 0) {
            std::cout << "Erro: Jardineiro nao tem acoes de plantacao restantes neste instante." << std::endl;
            return;
        }

        Planta* novaPlanta = nullptr;

        switch(tipo) {
            case 'c': novaPlanta = new Cacto(); break;
            case 'r': novaPlanta = new Roseira(); break;
            case 'e': novaPlanta = new ErvaDaninha(); break;
            case 'x': novaPlanta = new PlantaExotica(); break;
        }

        if (novaPlanta != nullptr) {
            jardim->adicionaObjeto(l, c, novaPlanta);
            jardineiro->planta(*jardim, tipo);
            std::cout << "Jardineiro planta " << p[1] <<" na posicao " << p[0] << std::endl;
            estadoAlterado = true;
        }
    }
    else if (comando == "larga") {
        if (jardineiro->getFerramentaNaMao() == nullptr) {
            std::cout << "Erro: O jardineiro nao tem nenhuma ferramenta na mao para largar." << std::endl;
        } else {
            jardineiro->largaFerramenta();
            estadoAlterado = true;
        }
    }
    else if (comando == "pega") {
        int idAlvo;

        try {
            idAlvo = std::stoi(p[0]);
        } catch (...) {
            std::cout << "Erro: Numero de serie '" << p[0] << "' invalido (deve ser um numero)." << std::endl;
            return;
        }

        if (jardineiro->selecionarFerramenta(idAlvo)) {
            std::cout << "Jardineiro colocou a ferramenta (ID: " << idAlvo << ") na mao." << std::endl;
            estadoAlterado = true;
        } else {
            std::cout << "Erro: O jardineiro nao possui a ferramenta com ID " << idAlvo << " no inventario." << std::endl;
        }
    }
    else if (comando == "compra") {
        char tipo = tolower(p[0][0]);
        Ferramenta* novaFerramenta = nullptr;

        switch (tipo) {
            case 'g': novaFerramenta = new Regador(); break;
            case 'a': novaFerramenta = new Adubo(); break;
            case 't': novaFerramenta = new Tesoura(); break;
            case 'z': novaFerramenta = new Pesticida(); break;
                return;
        }

        if (novaFerramenta != nullptr) {
            jardineiro->adicionaFerrInv(novaFerramenta);
            std::cout << "Jardineiro compra uma ferramenta do tipo " << p[0] << " (ID: " << novaFerramenta->getNumSerie() << ")." << std::endl;
            estadoAlterado = true;
        }
    }

    //Comandos para lista informacao

    else if (comando == "lplantas") {
        int linhas = jardim->getNumLinhas();
        int colunas = jardim->getNumColunas();
        bool encontrouPlantas = false;

        std::cout << "--- Listagem Detalhada de Todas as Plantas no Jardim ---" << std::endl;

        for (int i = 0; i < linhas; ++i) {
            for (int k = 0; k < colunas; ++k) {
                const Posicao& pos = jardim->getPosicao(i, k);

                if (pos.temPlanta()) {
                    encontrouPlantas = true;
                    Planta* p = pos.getPlanta();

                    char coord_l = (char)('A' + i);
                    char coord_c = (char)('A' + k);

                    std::cout << "Posicao [" << coord_l << coord_c << "]:" << std::endl;

                    std::cout << "  > Planta: " << p->getTipoPlanta() << std::endl;
                    std::cout << "    Propriedades Internas: "
                              << "Agua: " << p->getAguaInterna()
                              << " | Nutrientes: " << p->getNutrientesInternos()
                              << " | Beleza: " << (int)p->getBeleza()
                              << " | Vida: " << p->getTempoVida() << "i" << std::endl;

                    std::cout << "    Propriedades do Solo:     "
                              << "Agua: " << pos.getAgua()
                              << " | Nutrientes: " << pos.getNutrientes() << std::endl;

                    std::cout << "  -------------------------------------------------" << std::endl;
                }
            }
        }

        if (!encontrouPlantas) {
            std::cout << "Nao foram encontradas plantas no jardim." << std::endl;
        }

        return;
    }
    else if (comando == "lplanta") {
        std::pair<int, int> coords = comandoParaCoordenadas(p[0]);
        int l = coords.first;
        int c = coords.second;

        if (!jardim->ePosicaoValida(l, c)) {
            std::cout << "Erro: Posicao '" << p[0] << "' fora dos limites do jardim." << std::endl;
            return;
        }

        const Posicao& pos = jardim->getPosicao(l, c);

        if (!pos.temPlanta()) {
            std::cout << "Erro: Nao existe planta na posicao '" << p[0] << "'." << std::endl;
            return;
        }

        Planta* planta = pos.getPlanta();

        std::cout << "--- Informacao da Planta em '" << p[0] << "' ---" << std::endl;
        std::cout << "Tipo: " << planta->getTipoPlanta() << std::endl;
        std::cout << "Tempo de Vida: " << planta->getTempoVida() << " instantes" << std::endl;
        std::cout << "Beleza: " << (int)planta->getBeleza() << std::endl;
        std::cout << "Agua Interna: " << planta->getAguaInterna() << std::endl;
        std::cout << "Nutrientes Internos: " << planta->getNutrientesInternos() << std::endl;

        return;
    }
    else if (comando == "larea") {
        int linhas = jardim->getNumLinhas();
        int colunas = jardim->getNumColunas();
        bool encontrouAlgo = false;

        std::cout << "--- Listagem de Posicoes Ocupadas no Jardim ---" << std::endl;

        for (int i = 0; i < linhas; ++i) {
            for (int k = 0; k < colunas; ++k) {
                const Posicao& pos = jardim->getPosicao(i, k);

                bool temJardineiro = (jardineiro->estaPresente() &&
                                      jardineiro->getLinha() == i &&
                                      jardineiro->getColuna() == k);

                if (pos.temPlanta() || pos.temFerramenta() || temJardineiro) {
                    encontrouAlgo = true;

                    char coord_l = (char)('A' + i);
                    char coord_c = (char)('A' + k);

                    std::cout << "[" << coord_l << coord_c << "]: ";

                    if (temJardineiro) {
                        std::cout << "Jardineiro presente! ";
                    }

                    if (pos.temPlanta()) {
                        Planta* p = pos.getPlanta();
                        std::cout << "Planta: " << p->getTipoPlanta()
                                  << " (Vida: " << p->getTempoVida()
                                  << "i, B: " << (int)p->getBeleza() << ") ";
                    }

                    if (pos.temFerramenta()) {
                        Ferramenta* f = pos.getFerramenta();
                        std::cout << "Ferramenta: " << f->getTipoFerramenta()
                                  << " (ID: " << f->getNumSerie() << ") ";
                    }

                    std::cout << "| Solo -> Agua: " << pos.getAgua()
                              << ", Nutrientes: " << pos.getNutrientes() << std::endl;
                }
            }
        }

        if (!encontrouAlgo) {
            std::cout << "O jardim esta totalmente vazio de objetos." << std::endl;
        }

        return;
    }
    else if (comando == "lsolo") {
        std::pair<int, int> coords = comandoParaCoordenadas(p[0]);
        int l_centro = coords.first;
        int c_centro = coords.second;

        if (!jardim->ePosicaoValida(l_centro, c_centro)) {
            std::cout << "Erro: Posicao central '" << p[0] << "' fora dos limites do jardim." << std::endl;
            return;
        }

        int raio = 0;
        bool area_mode = false;

        if (p.size() > 1) {
            try {
                raio = std::stoi(p[1]);
                if (raio < 0) {
                    std::cout << "Aviso: O raio nao pode ser negativo. Usando 0." << std::endl;
                    raio = 0;
                }
                if (raio > 0) {
                    area_mode = true;
                }
            } catch (const std::exception& e) {
                std::cout << "Aviso: Parametro de area invalido. Ignorando area." << std::endl;
            }
        }

        int l_min = l_centro - raio;
        int l_max = l_centro + raio;
        int c_min = c_centro - raio;
        int c_max = c_centro + raio;

        if (area_mode) {
            std::cout << "--- Informacao do Solo na Area (" << p[0] << ", Raio: " << raio << ") ---" << std::endl;
        }

        for (int l = l_min; l <= l_max; ++l) {
            for (int c = c_min; c <= c_max; ++c) {

                if (jardim->ePosicaoValida(l, c)) {
                    const Posicao& pos = jardim->getPosicao(l, c);

                    char coord_l = (char)('A' + l);
                    char coord_c = (char)('A' + c);

                    std::cout << "\n[Posicao " << coord_l << coord_c << "]:" << std::endl;
                    std::cout << "Agua: " << pos.getAgua();
                    std::cout << " | Nutrientes: " << pos.getNutrientes();

                    if (pos.temPlanta()) {
                        std::cout << " | Planta: " << pos.getPlanta()->getTipoPlanta()
                                  << " (Beleza: " << (int)pos.getPlanta()->getBeleza() << ")";
                    }
                    if (pos.temFerramenta()) {
                        std::cout << " | Ferramenta: " << pos.getFerramenta()->getTipoFerramenta();
                    }
                    std::cout << std::endl;

                } else if (area_mode) {
                }
            }
        }
        return;
    }
    else if (comando == "lferr") {
        const std::vector<Ferramenta*>& inv = jardineiro->getInventario();
        Ferramenta* naMao = jardineiro->getFerramentaNaMao();

        std::cout << "--- Inventario de Ferramentas ---" << std::endl;

        if (inv.empty()) {
            std::cout << "O jardineiro nao transporta ferramentas." << std::endl;
        } else {
            for (Ferramenta* f : inv) {
                if (f == naMao) {
                    std::cout << "[ EM MAO ] ";
                } else {
                    std::cout << "[Mochila ] ";
                }

                std::cout << "Tipo: " << f->getTipoFerramenta()
                          << " | ID: " << f->getNumSerie();
                std::cout << " | Detalhes: ";
                f->listarDetalhes();

                std::cout << std::endl;
            }
        }
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
        jardineiro->usaFerramenta(*jardim);

        jardim->passaInstante();

        instanteAtual++;

        jardineiro->resetContadoresAcoes();
    }
}

