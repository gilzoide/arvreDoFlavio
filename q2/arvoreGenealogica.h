#include "arvore.h"

// Adiciona um parentesco, sendo pai e mae pais de filho
int adicionaParentesco (arvore *A, char filho[], char pai[], char mae[]);

// Imprime os membros da árvore genealógica, por geração
void imprimeMembros (arvore *A, int n);

// Imprime a árvore genealógica em "labelled bracketing"
void labelledBracketing (arvore *A);
