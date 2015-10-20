#include "arvore.h"

// Insere um valor na ABB, de modo que continue sendo uma ABB
void insereABB (arvore *A, int valor);

// Remove um valor da ABB, de modo que continue sendo uma ABB
// Retorna 1 se removeu com sucesso, ou 0 se valor não encontrado
int removeABB (arvore *A, int valor);

// Imprime a ABB em ordem
void imprimeEmOrdem (arvore *A);

// Imprime a ABB em Pré ordem
void imprimePreOrdem (arvore *A);

// Imprime a ABB em Pós ordem
void imprimePosOrdem (arvore *A);

// Imprime a ABB em "labelled bracketing"
void labelledBracketing (arvore *A);

// Busca um valor na ABB. Retorna 1 se achou, 0 caso contrário
int buscaValor (arvore *A, int valor);
