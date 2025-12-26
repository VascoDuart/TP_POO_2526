#include <vector>
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

Posicao& Jardim::getPosicao(int linha, int coluna) const {
    return grelha[linha][coluna];
}

bool Jardim::ePosicaoValida(int linha, int coluna) const {
    return linha >= 0 && linha < numLinhas && coluna >= 0 && coluna < numColunas;
}

bool Jardim::estaRodeada(int linha, int coluna) const {
    int dl[] = {-1, 1, 0, 0};
    int dc[] = {0, 0, 1, -1};

    for (int i = 0; i < 4; ++i) {
        int nl = linha + dl[i];
        int nc = coluna + dc[i];

        if (!ePosicaoValida(nl, nc) || grelha[nl][nc].getPlanta() == nullptr) {
            return false;
        }
    }
    return true;
}

Posicao* Jardim::encontraVizinhoMultiplicacao(int l, int c, bool &temPlantaVizinha) {
    int dl[] = {-1, 1, 0, 0};
    int dc[] = {0, 0, 1, -1};

    for (int i = 0; i < 4; ++i) {
        int nl = l + dl[i];
        int nc = c + dc[i];

        if (ePosicaoValida(nl, nc)) {
            temPlantaVizinha = (grelha[nl][nc].getPlanta() != nullptr);
            return grelha[nl] + nc;
        }
    }
    temPlantaVizinha = false;
    return nullptr;
}

void Jardim::passaInstante() {
    std::cout << "\n--- Passa Instante ---" << std::endl;
    std::vector<std::pair<int, int>> posicoesParaRemover;

    for (int i = 0; i < numLinhas; ++i) {
        for (int j = 0; j < numColunas; ++j) {
            Posicao& pos = grelha[i][j];
            Planta* planta = pos.getPlanta();

            Ferramenta* ferramenta = pos.getFerramenta();
            if (ferramenta != nullptr) {
                if (ferramenta->usarFerramenta(pos, *this, i, j)) {
                    Ferramenta* fEsgotada = pos.removeFerramenta();
                    delete fEsgotada; // Liberta a memória
                    std::cout << "Ferramenta descartada (ID: " << fEsgotada->getNumSerie() << ")." << std::endl;
                }
            }

            if (planta != nullptr) {
                Roseira* roseira = dynamic_cast<Roseira*>(planta);
                if (roseira) {
                    roseira->setRodeada(estaRodeada(i, j));
                }

                planta->passaInstante(pos);

                if (planta->verificaMorte(pos)) {
                    posicoesParaRemover.push_back({i, j});
                    continue;
                }

                Planta* novoRebento = planta->tentaMultiplicar();

                if (novoRebento != nullptr) {
                    bool temVizinhoComPlanta = false;
                    Posicao* posVizinha = encontraVizinhoMultiplicacao(i, j, temVizinhoComPlanta);

                    if (posVizinha != nullptr) {
                        if (novoRebento->getTipoPlanta() == 'e') {
                            if (temVizinhoComPlanta) {
                                Planta* plantaASerMorta = posVizinha->getPlanta();
                                std::cout << "Erva Daninha em (" << i << ", " << j << ") matou a planta "
                                          << plantaASerMorta->getTipoPlanta() << " em posicao vizinha!" << std::endl;

                                Planta* pMortaPorErva = posVizinha->removePlanta();
                                delete pMortaPorErva;
                            }

                            posVizinha->setPlanta(novoRebento);
                        } else if (!temVizinhoComPlanta) {
                            posVizinha->setPlanta(novoRebento);
                        } else {
                            delete novoRebento;
                        }
                    } else {
                        delete novoRebento;
                    }
                }
            }
        }
    }

    for (const auto& coord : posicoesParaRemover) {
        int i = coord.first;
        int j = coord.second;

        Planta* plantaMorta = grelha[i][j].removePlanta();
        delete plantaMorta;
    }
}

void Jardim::adicionaObjeto(int linha, int coluna, Planta *p) {
    if (!ePosicaoValida(linha, coluna)) {
        std::cerr << "ERRO: Tentativa de adicionar planta fora dos limites do jardim." << std::endl;
        delete p;
        return;
    }

    Posicao& pos = grelha[linha][coluna];

    if (pos.temPlanta()) {
        std::cout << "Aviso: Substituindo planta existente em (" << linha << ", " << coluna << ")." << std::endl;

        Planta* pAntiga = pos.removePlanta();
        delete pAntiga;
    }

    pos.setPlanta(p);
    std::cout << "Planta do tipo '" << p->getTipoPlanta() << "' adicionada em (" << linha << ", " << coluna << ")." << std::endl;
}

void Jardim::adicionaObjeto(int linha, int coluna, Ferramenta *f) {
    if (!ePosicaoValida(linha, coluna)) {
        std::cerr << "ERRO: Tentativa de adicionar ferramenta fora dos limites do jardim." << std::endl;
        delete f;
        return;
    }

    Posicao& pos = grelha[linha][coluna];

    if (pos.temFerramenta()) {
        std::cout << "Aviso: Substituindo ferramenta existente em (" << linha << ", " << coluna << ")." << std::endl;

        Ferramenta* fAntiga = pos.removeFerramenta();
        delete fAntiga;
    }

    pos.setFerramenta(f);
    std::cout << "Ferramenta adicionada em (" << linha << ", " << coluna << ")." << std::endl;
}

Jardim *Jardim::clona() const {
    Jardim* copia = new Jardim(numLinhas, numColunas);

    for (int i = 0; i < numLinhas; ++i) {
        for (int j = 0; j < numColunas; ++j) {

            copia->grelha[i][j].adicionaAgua(grelha[i][j].getAgua());
            copia->grelha[i][j].adicionaNutrientes(grelha[i][j].getNutrientes());

            Planta* plantaOriginal = grelha[i][j].getPlanta();
            if (plantaOriginal != nullptr) {
                Planta* plantaCopia = plantaOriginal->clona();
                copia->adicionaObjeto(i, j, plantaCopia);
            }

            Ferramenta* ferramentaOriginal = grelha[i][j].getFerramenta();
            if (ferramentaOriginal != nullptr) {
                Ferramenta* ferramentaCopia = ferramentaOriginal->clona();
                copia->adicionaObjeto(i, j, ferramentaCopia);
            }
        }
    }
    return copia;
}