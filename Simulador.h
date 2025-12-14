#ifndef SIMULADOR_H
#define SIMULADOR_H

#include "Jardim.h"
#include "Jardineiro.h"
#include "InterfaceGrelha.h"
#include "Comando.h"
#include "iostream"
#include "string"
#include "algorithm"

class Simulador {
private:
    Jardim* jardim;
    Jardineiro* jardineiro;
    InterfaceGrelha* interfaceGrelha;

    int instanteAtual;

    Comando lerComando() const;
    void executarComando(const Comando& cmd);
    void avancarInstante(int numInstantes);

public:
    Simulador();
    ~Simulador();

    void iniciar();
};

#endif // SIMULADOR_H