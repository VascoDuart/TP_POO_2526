#include <vector>
#include "Jardim.h"

#include "Plantas/PlantaExotica.h"
#include "Ferramentas/Regador.h"
#include "Ferramentas/Adubo.h"
#include "Ferramentas/Tesoura.h"
#include "Ferramentas/Pesticida.h"
#include "Jardineiro.h"

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
        for (int j=0; j < numColunas; ++j) {
            delete grelha[i][j].removePlanta();
            delete grelha[i][j].removeFerramenta();
        }
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

bool Jardim::encontraVizinhoMultiplicacao(int l, int c, int &nl, int &nc, bool &temPlanta) {
    int dl[] = {-1, 1, 0, 0};
    int dc[] = {0, 0, 1, -1};

    for (int i = 0; i < 4; ++i) {
        int tempL = l + dl[i];
        int tempC = c + dc[i];

        if (ePosicaoValida(tempL, tempC)) {
            nl = tempL;
            nc = tempC;
            temPlanta = grelha[nl][nc].temPlanta();
            return true;
        }
    }
    return false;
}

void Jardim::passaInstante(Jardineiro& jd) {
    std::cout << "\n--- Passa Instante ---" << std::endl;
    std::vector<std::pair<int, int>> posicoesParaRemover;

    struct NovoRebento {
        int l, c;
        Planta* planta;
    };
    std::vector<NovoRebento> novosRebentos;

    if (jd.estaPresente()) {
        jd.usaFerramenta(*this);
    }

    for (int i = 0; i < numLinhas; ++i) {
        for (int j = 0; j < numColunas; ++j) {
            Posicao& pos = grelha[i][j];
            Planta* planta = pos.getPlanta();

            if (planta != nullptr) {
                PlantaExotica* exotica = dynamic_cast<PlantaExotica*>(planta);
                if (exotica) {
                    exotica->passaInstanteComJardim(pos, *this, i, j);
                } else {
                    planta->passaInstante(pos);
                }

                Roseira* roseira = dynamic_cast<Roseira*>(planta);
                if (roseira) {
                    roseira->setRodeada(estaRodeada(i, j));
                }

                if (planta->verificaMorte(pos)) {
                    posicoesParaRemover.push_back({i, j});
                    continue;
                }

                Planta* novo = planta->tentaMultiplicar();
                if (novo != nullptr) {
                    int nl, nc;
                    bool temPlantaVizinha = false;

                    if (encontraVizinhoMultiplicacao(i, j, nl, nc, temPlantaVizinha)) {
                        if (planta->getTipoPlanta() == 'e') {
                            novosRebentos.push_back({nl, nc, novo});
                        }
                        else if (!temPlantaVizinha) {
                            novosRebentos.push_back({nl, nc, novo});
                        }
                        else {
                            delete novo;
                        }
                    } else {
                        delete novo;
                    }
                }
            }
        }
    }

    for (const auto& coord : posicoesParaRemover) {
        delete grelha[coord.first][coord.second].removePlanta();
    }

    for (auto& rebento : novosRebentos) {
        Posicao& destino = grelha[rebento.l][rebento.c];

        if (rebento.planta->getTipoPlanta() == 'e' && destino.temPlanta()) {
            Planta* pMorta = destino.removePlanta();
            delete pMorta;
            std::cout << "Erva Daninha matou planta em " << (char)('A' + rebento.l) << (char)('A' + rebento.c) << "!" << std::endl;
        }

        if (!destino.temPlanta()) {
            destino.setPlanta(rebento.planta);
        } else {
            delete rebento.planta;
        }
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

void Jardim::gerarFerramentaAleatoria() {
    int l, c;
    int tentativas = 0;
    int maxTentativas = numLinhas * numColunas;

    do {
        l = rand() % numLinhas;
        c = rand() % numColunas;
        tentativas++;
    } while ((grelha[l][c].temFerramenta() || grelha[l][c].temPlanta()) && tentativas < maxTentativas);

    if (tentativas >= maxTentativas) return;

    int tipo = rand() % 4;
    Ferramenta* nova = nullptr;

    if (tipo == 0) nova = new Regador();
    else if (tipo == 1) nova = new Adubo();
    else if (tipo == 2) nova = new Tesoura();
    else nova = new Pesticida();

    grelha[l][c].setFerramenta(nova);
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