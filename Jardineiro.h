#ifndef TP_POO_2526_JARDINEIRO_H
#define TP_POO_2526_JARDINEIRO_H

#include <iostream>
#include <vector>
#include "Ferramentas/Ferramenta.h"
#include "Plantas/Planta.h"
#include "Posicao.h"
#include "Jardim.h"

using namespace std;

class Jardineiro {
private:
    bool presenteNoJardim;
    int linha;
    int coluna;
    vector<Ferramenta*> inventario;
    Ferramenta* ferramentaNaMao;

    int movimentosRestantes;
    int colheitasRestantes;
    int plantasRestantes;
    bool entrouNesteInstante;
    bool saiuNesteInstante;

public:
    Jardineiro();
    ~Jardineiro();

    bool move(char direcao, const Jardim& j);
    bool entraNoJardim(int l, int c, const Jardim& j);
    bool saiDoJardim();

    void usaFerramenta(Jardim& j);
    void planta(Jardim& j, char tipoPlanta);
    void colhe(Jardim& j);
    void adicionaFerrInv(Ferramenta* f);
    bool selecionarFerramenta(int id);
    void largaFerramenta();

    void resetContadoresAcoes();

    bool estaPresente() const { return presenteNoJardim; }
    int getLinha() const { return linha; }
    int getColuna() const { return coluna; }
    int getPlantacoesRestantes() const { return plantasRestantes; }
    Ferramenta* getFerramentaNaMao() const { return ferramentaNaMao; }
    const vector<Ferramenta*>& getInventario() { return inventario; }
    Jardineiro* clona() const;
};


#endif //TP_POO_2526_JARDINEIRO_H
