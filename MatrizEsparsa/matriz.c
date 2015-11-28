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

    celula **aux;
    for (*aux = mat->linhas[y]; *aux != NULL; *aux = (*aux)->proxLinha) {
        if ((*aux)->x == x) {
            (*aux)->valor = valor;
            return 1;
        }
        else if ((*aux)->x > x) {
            celula *cel = malloc (sizeof (celula));
            if (cel == NULL) {
                return 0;
            }

            cel->y = y;
            cel->x = x;
            cel->proxLinha = *aux;
            *aux = cel;

            for (*aux = mat->colunas[x]; *aux != NULL; *aux = (*aux)->proxColuna) {
                if ((*aux)->y > y) {
                    cel->proxColuna = *aux;
                    *aux = cel;
                    return 1;
                }
            }
        }
    }
}


void apagaMatrizEsparsa (matrizEsparsa *mat) {
    free (mat->linhas);
    free (mat->colunas);
    free (mat);
}
