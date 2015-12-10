#include <stdlib.h>
#include <stdio.h>

#define ERRO -99999999

typedef struct celula_t {
    int y;
    int x;
    double valor;
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

/// Insere um valor na matrizEsparsa na posição 'y x x'
/// Retorna 0 se tudo certo, ERRO caso contrário
int insereValor (matrizEsparsa *mat, int y, int x, double valor);

/// Calcula a soma dos valores da linha 'linha'
double somaLinha (matrizEsparsa *mat, int linha);
/// Calcula a soma dos valores da coluna 'coluna'
double somaColuna (matrizEsparsa *mat, int coluna);

/// Consulta o valor na matriz na posição 'y x x'
double consultaValor (matrizEsparsa *mat, int y, int x);

/// Escreve a matriz na tela
void printMatriz (matrizEsparsa *mat);

/// Calcula o determinante da matriz
double determinante (matrizEsparsa *mat);

/// Calcula o resultado do sistema linear
/// Saída é a variável de entrada 'vetor'
int gaussSeidel (matrizEsparsa *mat);

/// Apaga uma matrizEsparsa, todas suas células e talz
void apagaMatrizEsparsa (matrizEsparsa *mat);
