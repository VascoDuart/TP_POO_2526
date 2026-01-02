#ifndef TP_POO_2526_JARDIM_H
#define TP_POO_2526_JARDIM_H

#include "Posicao.h"
#include "Plantas/Roseira.h"
#include "Ferramentas/Ferramenta.h"

class Jardineiro;

class Jardim {
    Posicao** grelha;
    int numLinhas;
    int numColunas;

public:
    Jardim(int linhas, int colunas);

    ~Jardim();

    int getNumLinhas() const { return numLinhas; }
    int getNumColunas() const { return numColunas; }
    Posicao& getPosicao(int linha, int coluna) const;
    bool ePosicaoValida(int linha, int coluna) const;
    bool estaRodeada(int linha, int coluna) const;
    bool encontraVizinhoMultiplicacao(int l, int c, int &nl, int &nc, bool &temPlanta);

    void adicionaObjeto(int linha, int coluna, Planta* p);
    void adicionaObjeto(int linha, int coluna, Ferramenta* f);

    void gerarFerramentaAleatoria();

    void passaInstante(Jardineiro& jd);

    Jardim* clona() const;
};


#endif //TP_POO_2526_JARDIM_H
