#include <stdlib.h>
#include <stdio.h>

typedef struct celula_t {
    int y;
    int x;
    int valor;
    struct celula_t *proxLinha;
    struct celula_t *proxColuna;
} celula;

typedef struct {
    int numLinhas;
    celula **linhas;
    int numColunas;
    celula **colunas;
} matrizEsparsa;

/// Cria uma matrizEsparsa de tamanho 'linhas x colunas'
matrizEsparsa *criaMatrizEsparsa (int linhas, int colunas);

/// Insere um valor na matrizEsparsa nas posições 'y x x'
/// Retorna 1 se tudo certo, 0 caso contrário
int insereValor (matrizEsparsa *mat, int y, int x, int valor);

/// Calcula a soma dos valores da linha 'linha'
int somaLinha (matrizEsparsa *mat, int linha);
/// Calcula a soma dos valores da coluna 'coluna'
int somaColuna (matrizEsparsa *mat, int coluna);

/// Escreve a matriz na tela
void printMatriz (matrizEsparsa *mat);

/// Apaga uma matrizEsparsa, todas suas células e talz
void apagaMatrizEsparsa (matrizEsparsa *mat);
