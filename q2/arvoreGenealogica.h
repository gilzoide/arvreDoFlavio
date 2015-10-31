#include "arvore.h"

// Adiciona um parentesco, sendo pai e mae pais de filho
int adicionaParentesco (arvore *A, char filho[], char pai[], char mae[]);

// Imprime os membros da árvore genealógica, por geração
void imprimeMembros (arvore *A);

// Imprime os antepassados de 'nome'
void imprimeAntepassados (arvore *A, char nome[]);

// Imprime a árvore genealógica em "labelled bracketing"
void labelledBracketing (arvore *A);
