#include "Comando.h"
#include <sstream>
#include <algorithm>

using namespace std;

void Comando::parseLinha(const string& linhaComando) {
    istringstream iss(linhaComando);
    string tempComando;

    if (iss >> tempComando) {
        std::transform(tempComando.begin(), tempComando.end(), tempComando.begin(),::tolower);

        comando = tempComando;
    }
    string parametro;
    while (iss >> parametro) {
        parametros.push_back(parametro);
    }
}

Comando::Comando(const std::string &input) : valido(true) {
    parseLinha(input);

    if (comando.empty()) {
        valido = false;
    } else {
        validarComando();
    }
}

std::string Comando::getComando() const {
    return comando;
}

std::vector<std::string> Comando::getParametros() const {
    return parametros;
}

bool Comando::isInt(const std::string& s) const {
    if (s.empty() || s == "0") return false;

    for (char c : s) {
        if (!isdigit(c)) {
            return false;
        }
    }
    return true;
}

bool Comando::isPosicao(const std::string& s) const {
    if (s.length() != 2) return false;

    char l = tolower(s[0]);
    char c = tolower(s[1]);

    return (l >= 'a' && l <= 'z' && c >= 'a' && c <= 'z');
}

bool Comando::isTipoPlanta(const std::string& s) const {
    if (s.length() != 1) return false;
    char tipo = tolower(s[0]);
    return (tipo == 'c' || tipo == 'r' || tipo == 'e' || tipo == 'x');
}

bool Comando::isTipoFerramenta(const std::string& s) const {
    if (s.length() != 1) return false;
    char tipo = tolower(s[0]);
    return (tipo == 'g' || tipo == 'a' || tipo == 't' || tipo == 'z');
}

void Comando::validarComando() {
    const std::vector<std::string>& p = parametros;

    if (comando == "jardim") {
        if (p.size() != 2 || !isInt(p[0]) || !isInt(p[1])) {
            valido = false;
        }
    } else if (comando == "grava" || comando == "recupera" || comando == "apaga" || comando == "executa") {
        if (p.size() != 1) {
            valido = false;
        }
    } else if (comando == "fim" || comando == "lplantas" || comando == "larea" || comando == "lferr" || comando == "sai" || comando == "larga") {
        if (!p.empty()) {
            valido = false;
        }

    } else if (comando == "avanca") {
        if (p.size() > 1 || (p.size() == 1 && !isInt(p[0]))) {
            valido = false;
        }

    } else if (comando == "colhe" || comando == "lplanta" || comando == "entra") {
        if (p.size() != 1 || !isPosicao(p[0])) {
            valido = false;
        }
    } else if (comando == "lsolo") {
        if (p.size() < 1 || p.size() > 2) {
            valido = false;
        } else if (p.size() == 1) {
            if (!isPosicao(p[0])) valido = false;
        } else {
            if (!isPosicao(p[0]) || !isInt(p[1])) valido = false;
        }
    } else if (comando == "planta") {
        if (p.size() != 2 || !isPosicao(p[0]) || !isTipoPlanta(p[1])) {
            valido = false;
        }
    } else if (comando == "pega") {
        if (p.size() != 1 || !isInt(p[0])) {
            valido = false;
        }
    } else if (comando == "compra") {
        if (p.size() != 1 || !isTipoFerramenta(p[0])) {
            valido = false;
        }
    } else if (comando == "e" || comando == "d" || comando == "c" || comando == "b") {
        if (!p.empty()) {
            valido = false;
        }
    }
    else {
        valido = false;
    }
}


bool Comando::isValido() const{
    return valido;
}