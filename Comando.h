#ifndef TP_POO_2526_COMANDO_H
#define TP_POO_2526_COMANDO_H

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Comando {
private:
    string comando;
    vector<string> parametros;
    bool valido;

public:
    Comando(const string& input);
    bool isValido() const;
    string getComando() const;
    vector<string> getParametros() const;

private:
    void parseLinha(const std::string& linhaComando);
    void validarComando();

    bool isInt(const std::string& s) const;
    bool isPosicao(const std::string& s) const;
    bool isTipoPlanta(const std::string& s) const;
    bool isTipoFerramenta(const std::string& s) const;
};


#endif //TP_POO_2526_COMANDO_H
