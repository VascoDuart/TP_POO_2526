#ifndef TP_POO_2526_POSICAO_H
#define TP_POO_2526_POSICAO_H


#include "Plantas/Planta.h"
#include "Ferramentas/Ferramenta.h"

class Posicao {
    int agua, nutrientes;
    Planta* planta;
    Ferramenta* ferramenta;

public:
    Posicao();

    int getAgua() const;
    void adicionaAgua(int valor);
    void retiraAgua(int valor);

    int getNutrientes() const;
    void adicionaNutrientes(int valor);
    void retiraNutrientes(int valor);

    bool temPlanta() const;
    Planta* getPlanta() const;
    void setPlanta(Planta* p);
    void removePlanta();

    bool temFerramenta() const;
    Ferramenta* getFerramenta() const;
    void setFerramenta(Ferramenta* f);
    void removeFerramenta();

};


#endif //TP_POO_2526_POSICAO_H
