#ifndef SIMULADOR_H
#define SIMULADOR_H

#include "Jardim.h"
#include "Jardineiro.h"
#include "InterfaceGrelha.h"
#include "Comando.h"

class Simulador {
private:
    Jardim* jardim;
    Jardineiro* jardineiro;
    InterfaceGrelha* interfaceGrelha;

    int instanteAtual;

public:
    Simulador();
    ~Simulador();

    void iniciar();

private:
    Comando lerComando() const;

    void executarComando(const Comando& cmd);

    void avancarInstante(int numInstantes);
};

#endif // SIMULADOR_H