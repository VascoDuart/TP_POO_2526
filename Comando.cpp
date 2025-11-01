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

const std::string& Comando::getMsgErro() const {
    return msgErro;
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

void Comando::definirErro(const std::string& msg) {
    valido = false;
    msgErro = "Comando invalido. " + msg;
}

void Comando::validarComando() {
    const std::vector<std::string>& p = parametros;

    if (comando == "jardim") {
        if (p.size() != 2) {
            definirErro("O comando 'jardim' requer 2 argumentos: jardim <linhas> <colunas>.");
        }
        else if (!isInt(p[0]) || !isInt(p[1])) {
            definirErro("As dimensoes devem ser numeros inteiros positivos (1-26).");
        }
        else {
            try {
                int linhas = std::stoi(p[0]);
                int colunas = std::stoi(p[1]);
                if (linhas < 1 || linhas > 26 || colunas < 1 || colunas > 26) {
                    definirErro("As dimensoes do jardim devem estar entre 1 e 26 (para usar letras A-Z).");
                }
            } catch (const std::exception& e) {
                definirErro("Erro na conversao das dimensoes. Use numeros inteiros validos.");
            }
        }
    }
    else if (comando == "grava" || comando == "recupera" || comando == "apaga" || comando == "executa") {
        if (p.size() != 1) {
            definirErro("O comando '" + comando + "' requer um nome de ficheiro como argumento. Ex: " + comando + " teste1.");
        }
    }
    else if (comando == "fim" || comando == "lplantas" || comando == "larea" || comando == "lferr" || comando == "sai" || comando == "larga" ||
             comando == "e" || comando == "d" || comando == "c" || comando == "b") {
        if (!p.empty()) {
            definirErro("O comando '" + comando + "' nao aceita parametros.");
        }
    }
    else if (comando == "avanca") {
        if (p.size() > 1) {
            definirErro("O comando 'avanca' aceita no maximo 1 parametro.");
        }
        else if (p.size() == 1 && !isInt(p[0])) {
            definirErro("O numero de instantes do comando 'avanca' deve ser um numero inteiro positivo.");
        }
    }
    else if (comando == "colhe" || comando == "lplanta" || comando == "entra") {
        if (p.size() != 1 || !isPosicao(p[0])) {
            definirErro("O comando '" + comando + "' requer 1 argumento de posicao. Ex: " + comando + " ab.");
        }
    }
    else if (comando == "planta") {
        if (p.size() != 2) {
            definirErro("O comando 'planta' requer 2 argumentos: planta <posicao> <tipo>. Ex: planta ab c.");
        }
        else if (!isPosicao(p[0]) || !isTipoPlanta(p[1])) {
            definirErro("A sintaxe de 'planta' é incorreta. A posicao deve ser 2 letras (ex: ab) e o tipo deve ser C, R, E ou X.");
        }
    }
    else if (comando == "pega") {
        if (p.size() != 1 || !isInt(p[0])) {
            definirErro("O comando 'pega' requer 1 argumento inteiro (o ID da ferramenta).");
        }
    }
    else if (comando == "compra") {
        if (p.size() != 1 || !isTipoFerramenta(p[0])) {
            definirErro("O comando 'compra' requer 1 argumento de tipo de ferramenta (G, A, T ou Z).");
        }
    }
    else if (comando == "lsolo") {
        if (p.size() < 1 || p.size() > 2) {
            definirErro("O comando 'lsolo' requer 1 ou 2 argumentos: lsolo <posicao> [area].");
        } else if (!isPosicao(p[0])) {
            definirErro("O primeiro argumento de 'lsolo' deve ser uma posicao (2 letras, ex: ab).");
        } else if (p.size() == 2 && !isInt(p[1])) {
            definirErro("O segundo argumento de 'lsolo' (area) deve ser um numero inteiro positivo.");
        }
    }
    else {
        definirErro("O comando '" + comando + "' nao e reconhecido.");
    }
}


bool Comando::isValido() const{
    return valido;
}