#include "eqPolonesa.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


// Função auxiliar, que retorna 1 se 'op' for operador, ou 0 se for operando
int ehOperador (char op[]) {
	return strchr ("+-*/%", op[0]) ? 1 : 0;
}


// Função recursiva auxiliar a leEntrada
void recLeEntrada (no **N) {
	char entrada[MAX];
	scanf ("%s", entrada);
	*N = novoNo (entrada);
	// é operador, então lê seus operandos
	if (ehOperador (entrada)) {
		recLeEntrada (&(*N)->esquerdo);
		recLeEntrada (&(*N)->direito);
	}
}
void leEntrada (arvore *A) {
	recLeEntrada (&A->raiz);
}


// Função recursiva auxiliar a imprimeRPN
void recImprimeRPN (no *N) {
	if (N != NULL) {
		recImprimeRPN (N->esquerdo);
		recImprimeRPN (N->direito);
		printf ("%s ", N->valor);
	}
}
void imprimeRPN (arvore *A) {
	printf ("RPN:               ");
	recImprimeRPN (A->raiz);
	puts ("");
}


// Função recursiva auxiliar a imprimeInfixa
void recImprimeInfixa (no *N) {
	if (N != NULL) {
		// se é operador, escreve os parênteses e espaços certos
		if (ehOperador (N->valor)) {
			printf ("(");
			recImprimeInfixa (N->esquerdo);
			printf (" %s ", N->valor);
			recImprimeInfixa (N->direito);
			printf (")");
		}
		else {
			printf ("%s", N->valor);
		}
	}
}
void imprimeInfixa (arvore *A) {
	printf ("Notação Infixa:    ");
	recImprimeInfixa (A->raiz);
	puts ("");
}
