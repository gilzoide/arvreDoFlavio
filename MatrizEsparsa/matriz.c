#include "matriz.h"

matrizEsparsa *criaMatrizEsparsa (int linhas, int colunas) {
    if (linhas <= 0 || colunas <= 0) {
        fprintf (stderr, "Erro: número de linhas e colunas deve ser positivo não nulo!\n");
        return NULL;
    }

    matrizEsparsa *mat = malloc (sizeof (matrizEsparsa));
    if (mat == NULL) {
        return NULL;
    }

    mat->numLinhas = linhas;
    mat->linhas = calloc (linhas, sizeof (celula *));
    if (mat->linhas == NULL) {
        free (mat);
        return NULL;
    }
    mat->numColunas = colunas;
    mat->colunas = calloc (colunas, sizeof (celula *));
    if (mat->colunas == NULL) {
        free (mat->linhas);
        free (mat);
        return NULL;
    }

    return mat;
}


int insereValor (matrizEsparsa *mat, int y, int x, int valor) {
    if (y < 0 || x < 0 || y >= mat->numLinhas || x >= mat->numColunas) {
        fprintf (stderr, "Erro na inserção: posição inválida\n");
        return 0;
    }

	// procura a célula na linha, até que não exista, ou até a célula exatamente depois
    celula **aux;
    for (aux = &mat->linhas[y]; *aux != NULL; *aux = (*aux)->proxLinha) {
        if ((*aux)->x == x) {
            (*aux)->valor = valor;
            return 1;
        }
        else if ((*aux)->x > x) {
			break;
        }
    }

	// já cria a célula nova
	celula *cel = malloc (sizeof (celula));
	if (cel == NULL) {
		return 0;
	}

	cel->y = y;
	cel->x = x;
	cel->valor = valor;


	// atualiza os ponteiros (linha)
	cel->proxLinha = *aux;
	*aux = cel;

	// procura a célula na coluna, até que não exista, ou até a célula exatamente depois
	for (aux = &mat->colunas[x]; *aux != NULL; *aux = (*aux)->proxColuna) {
		if ((*aux)->y > y) {
			break;
		}
	}

	// atualiza os ponteiros (coluna)
	cel->proxColuna = *aux;
	*aux = cel;
	return 1;
}


int somaLinha (matrizEsparsa *mat, int linha) {
	if (linha < 0 || linha >= mat->numLinhas) {
		fprintf (stderr, "Linha inválida\n");
		return ERRO;
	}

	// acumula valores das células na variável 'soma'
	int soma = 0;
	celula *aux;
	for (aux = mat->linhas[linha]; aux != NULL; aux = aux->proxLinha) {
		soma += aux->valor;
	}

	return soma;
}


int somaColuna (matrizEsparsa *mat, int coluna) {
	if (coluna < 0 || coluna >= mat->numColunas) {
		fprintf (stderr, "Coluna inválida\n");
		return ERRO;
	}

	// acumula valores das células na variável 'soma'
	int soma = 0;
	celula *aux;
	for (aux = mat->colunas[coluna]; aux != NULL; aux = aux->proxColuna) {
		soma += aux->valor;
	}

	return soma;
}


int consultaValor (matrizEsparsa *mat, int y, int x) {
	if (y < 0 || x < 0 || y >= mat->numLinhas || x >= mat->numColunas) {
		fprintf (stderr, "Posição inválida\n");
		return ERRO;
	}

	celula *aux;
	for (aux = mat->linhas[y]; aux != NULL; aux = aux->proxLinha) {
		// achou o número
		if (aux->x == x) {
			return aux->valor;
		}
	}

	// se por acaso não achou uma célula, é porque é zero
	return 0;
}


void printMatriz (matrizEsparsa *mat) {
	int i, j;
	for (i = 0; i < mat->numLinhas; i++) {
		j = 0;
		celula *aux = mat->linhas[i];
		// pra cada célula existente, escreve os zeros antes, e seu valor
		for (aux = mat->linhas[i]; aux != NULL; aux = aux->proxLinha) {
			// escreve os zeros anteriores ao X atual
			while (j < aux->x) {
				printf ("0 ");
				j++;
			}
			printf ("%d ", aux->valor);
			j++;
		}
		// escreve o resto dos zeros
		while (j < mat->numColunas) {
			printf ("0 ");
			j++;
		}

		// pula linha, e partiu próxima
		puts ("");
	}
}


void apagaMatrizEsparsa (matrizEsparsa *mat) {
	// apaga as células todas
	int i;
	for (i = 0; i < mat->numLinhas; i++) {
		celula *aux, *proximo;
		for (aux = mat->linhas[i]; aux != NULL; aux = proximo) {
			proximo = aux->proxLinha;
			free (aux);
		}
	}
    free (mat->linhas);
    free (mat->colunas);
    free (mat);
}
