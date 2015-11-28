#include "arvore.h"
#include <stdlib.h>
#include <string.h>

void iniciaArvore (arvore *A) {
	A->raiz = NULL;
	A->n = 0;
}


no *novoNo (char valor[]) {
	no *novo = malloc (sizeof (no));
	if (novo == NULL) {
		return NULL;
	}

	// inicializa valores: não tem filhos
	strncpy (novo->valor, valor, MAX);
	novo->esquerdo = NULL;
	novo->direito = NULL;

	return novo;
}


// Função auxiliar a destroiArvore. Destrói cada nó, liberando sua memória e
// de seus filhos recursivamente.
void destroiNo (no *N) {
	if (N != NULL) {
		destroiNo (N->esquerdo);
		destroiNo (N->direito);
		free (N);
	}
}
void destroiArvore (arvore *A) {
	destroiNo (A->raiz);
	// volta A pro estado inicial: não há nós
	iniciaArvore (A);
}
