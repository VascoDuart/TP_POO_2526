#include "Jardineiro.h"
#include <algorithm>

Jardineiro::Jardineiro()
        : presenteNoJardim(false), linha(-1), coluna(-1), ferramentaNaMao(nullptr),
          entrouNesteInstante(false), saiuNesteInstante(false)
{
    resetContadoresAcoes();
}

Jardineiro::~Jardineiro() {
    for (Ferramenta* f : inventario) {
        delete f;
    }
    inventario.clear();
}

void Jardineiro::resetContadoresAcoes() {
    movimentosRestantes = Settings::Jardineiro::max_movimentos;
    plantasRestantes = Settings::Jardineiro::max_plantacoes;
    colheitasRestantes = Settings::Jardineiro::max_colheitas;

    entrouNesteInstante = false;
    saiuNesteInstante = false;
}

bool Jardineiro::entraNoJardim(int l, int c, Jardim &j) {
    if (!j.ePosicaoValida(l, c)) {
        std::cout << "Erro: Coordenadas fora dos limites do jardim." << std::endl;
        return false;
    }

    if (presenteNoJardim) {
        linha = l;
        coluna = c;
    } else {
        if (entrouNesteInstante) {
            std::cout << "Aviso: O jardineiro ja entrou neste instante (limite: 1)." << std::endl;
            return false;
        }
        presenteNoJardim = true;
        linha = l;
        coluna = c;
        entrouNesteInstante = true;
    }

    Posicao& pos = j.getPosicao(linha, coluna);

    if (pos.temFerramenta()) {
        Ferramenta* f = pos.getFerramenta();

        if (this->adicionaFerrInv(f)) {
            pos.removeFerramenta();

            j.gerarFerramentaAleatoria();

            std::cout << "Jardineiro entrou e recolheu automaticamente: " << f->getTipoFerramenta() << std::endl;
        }
    }

    return true;
}

bool Jardineiro::saiDoJardim() {
    if (!presenteNoJardim) {
        std::cout << "Aviso: O jardineiro ja esta fora do jardim." << std::endl;
        return false;
    }

    if (saiuNesteInstante) {
        std::cout << "Aviso: O jardineiro ja saiu neste instante (limite: 1)." << std::endl;
        return false;
    }

    presenteNoJardim = false;
    linha = -1;
    coluna = -1;
    saiuNesteInstante = true;

    return true;
}

bool Jardineiro::move(char direcao, Jardim &j) {
    if (!presenteNoJardim) {
        std::cout << "Erro: O jardineiro nao esta no jardim para se mover." << std::endl;
        return false;
    }

    if (movimentosRestantes <= 0) {
        std::cout << "Erro: Movimentos esgotados neste instante." << std::endl;
        return false;
    }

    int novaLinha = linha;
    int novaColuna = coluna;

    switch (tolower(direcao)) {
        case 'e': novaColuna--; break;
        case 'd': novaColuna++; break;
        case 'c': novaLinha--; break;
        case 'b': novaLinha++; break;
        default: return false;
    }

    if (j.ePosicaoValida(novaLinha, novaColuna)) {
        linha = novaLinha;
        coluna = novaColuna;
        movimentosRestantes--;

        Posicao& pos = j.getPosicao(linha, coluna);

        if (pos.temFerramenta()) {
            Ferramenta* f = pos.getFerramenta();

            if (this->adicionaFerrInv(f)) {
                pos.removeFerramenta();

                j.gerarFerramentaAleatoria();

                std::cout << "Recolheu automaticamente: " << f->getTipoFerramenta() << std::endl;
            }
        }
        return true;
    }

    std::cout << "Erro: Movimento invalido (fora dos limites)." << std::endl;
    return false;
}

void Jardineiro::planta(Jardim &j, char tipoPlanta) {
    if (plantasRestantes <= 0) {
        return;
    }

    plantasRestantes--;
}

void Jardineiro::colhe(int l, int c, Jardim &j) {
    if (colheitasRestantes <= 0) {
        std::cout << "Erro: Numero de colheitas esgotadas (limite: " << Settings::Jardineiro::max_colheitas << ")." << std::endl;
        return;
    }

    if (!j.ePosicaoValida(l, c)) {
        std::cout << "Erro: Posicao invalida." << std::endl;
        return;
    }

    Posicao& pos = j.getPosicao(l, c);

    if (!pos.temPlanta()) {
        std::cout << "Erro: Nao ha planta para colher na posicao " << (char)('A' + l) << (char)('A' + c) << "." << std::endl;
        return;
    }

    Planta* plantaColhida = pos.removePlanta();

    if (plantaColhida != nullptr) {
        plantaColhida->acaoAoSerRemovida(pos);
        delete plantaColhida;
        colheitasRestantes--;
        std::cout << "Colheita bem sucedida na posicao " << (char)('A' + l) << (char)('A' + c) << std::endl;
    }
}

bool Jardineiro::adicionaFerrInv(Ferramenta *f) {
    if (f == nullptr) {
        std::cout << "Erro: Nao e possivel pegar numa ferramenta nula." << std::endl;
        return false;
    }

    inventario.push_back(f);
    std::cout << "Ferramenta ID " << f->getNumSerie() << " adicionada ao inventario." << std::endl;
    return true;
}

bool Jardineiro::selecionarFerramenta(int id) {
    for (Ferramenta* f : inventario) {
        if (f->getNumSerie() == id) {
            this->ferramentaNaMao = f;
            return true;
        }
    }
    return false;
}

void Jardineiro::largaFerramenta() {
    if (this->ferramentaNaMao == nullptr) {
        std::cout << "Aviso: O jardineiro ja nao tinha nada na mao." << std::endl;
        return;
    }

    std::cout << "Jardineiro guardou a ferramenta (ID: "
              << ferramentaNaMao->getNumSerie() << ") na mochila." << std::endl;

    this->ferramentaNaMao = nullptr;
}

void Jardineiro::usaFerramenta(Jardim &j) {
    if (!presenteNoJardim) {
        std::cout << "Erro: O jardineiro nao esta no jardim." << std::endl;
        return;
    }

    if (ferramentaNaMao == nullptr) {
        std::cout << "O jardineiro nao tem nenhuma ferramenta na mao." << std::endl;
        return;
    }

    Posicao& pos = j.getPosicao(linha, coluna);
    bool esgotou = ferramentaNaMao->usarFerramenta(pos, j, linha, coluna);

    if (esgotou) {
        std::cout << "A ferramenta ID " << ferramentaNaMao->getNumSerie() << " esgotou-se e foi descartada." << std::endl;

        auto it = std::find(inventario.begin(), inventario.end(), ferramentaNaMao);
        if (it != inventario.end()) {
            inventario.erase(it);
        }

        delete ferramentaNaMao;
        ferramentaNaMao = nullptr;
    } else {
        std::cout << "Ferramenta ID " << ferramentaNaMao->getNumSerie() << " utilizada com sucesso." << std::endl;
    }
}

Jardineiro* Jardineiro::clona() const {
    Jardineiro* novoJardineiro = new Jardineiro();
    novoJardineiro->presenteNoJardim = this->presenteNoJardim;
    novoJardineiro->linha = this->linha;
    novoJardineiro->coluna = this->coluna;
    novoJardineiro->movimentosRestantes = this->movimentosRestantes;
    novoJardineiro->colheitasRestantes = this->colheitasRestantes;
    novoJardineiro->plantasRestantes = this->plantasRestantes;
    novoJardineiro->entrouNesteInstante = this->entrouNesteInstante;
    novoJardineiro->saiuNesteInstante = this->saiuNesteInstante;
    for (Ferramenta* f : this->inventario) {
        novoJardineiro->inventario.push_back(f->clona());
    }
    if (this->ferramentaNaMao != nullptr) {
        novoJardineiro->ferramentaNaMao = this->ferramentaNaMao->clona();
    } else {
        novoJardineiro->ferramentaNaMao = nullptr;
    }
    return novoJardineiro;
}

