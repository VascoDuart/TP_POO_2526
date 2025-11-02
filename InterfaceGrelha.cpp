#include "InterfaceGrelha.h"
#include "Jardim.h"


InterfaceGrelha::InterfaceGrelha(Jardim& jardim, Jardineiro& jardineiro)
    : jardim(jardim), jd(jardineiro)
{}

void InterfaceGrelha::desenharJardim() const {

    int linhas = jardim.getNumLinhas();
    int colunas = jardim.getNumColunas();

    std::cout << " ";
    for (int col = 0; col < colunas; ++col) {
        std::cout << (char)('A' + col);
    }
    std::cout << std::endl;

    for (int i = 0; i < linhas; ++i) {

        std::cout << (char)('A' + i) << "  ";

        for (int k = 0; k < colunas; ++k) {

            const Posicao& pos = jardim.getPosicao(i, k);

            char char_a_imprimir = ' ';

            if (jd.estaPresente() &&
                jd.getLinha() == i &&
                jd.getColuna() == k)
            {
                char_a_imprimir = 'J';
            }

            else if (pos.temPlanta()) {
                char_a_imprimir = 'P';
            }
            else if (pos.temFerramenta()) {
                char_a_imprimir = 'F';
            }

            std::cout << char_a_imprimir << ' ';
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}
