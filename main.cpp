#include <iostream>
#include "Simulador.h"

using namespace std;

int main() {
        srand(static_cast<unsigned int>(time(nullptr)));
        Simulador simulador;
        simulador.iniciar();
        return 0;
}