#include "TabSimb.h"

int posicao = 0;
Posicao *ultimo = NULL;

TabelaSimbolos Nova_Tabela() {
    TabelaSimbolos T = malloc(sizeof(TS));

    T->raiz = NULL;

    return T;
}

void Rotacao_Direita(Nodo **nodo) {
    Nodo *nodo_2 = (*nodo)->esquerda;

    (*nodo)->esquerda = nodo_2->direita;
    nodo_2->direita = *nodo;
    *nodo = nodo_2;

    (*nodo)->fb = 0;
    (*nodo)->direita->fb = 0;
}

void Rotacao_Esquerda_Direita(Nodo **nodo) {
    Nodo *nodo_2 = (*nodo)->esquerda;
    Nodo *nodo_3 = nodo_2->direita;

    (*nodo)->esquerda = nodo_3->direita;
    nodo_3->direita = *nodo;
    nodo_2->direita = nodo_3->esquerda;
    nodo_3->esquerda = nodo_2;
    *nodo = nodo_3;

    if ((*nodo)->fb == 1) {
        (*nodo)->esquerda->fb = -1;
    }
    else {
        (*nodo)->esquerda->fb = 0;
    }
    if ((*nodo)->fb == -1) {
        (*nodo)->direita->fb = 1;
    }
    else {
        (*nodo)->direita->fb = 0;
    }
    (*nodo)->fb = 0;
}

void Rotacao_Esquerda(Nodo **nodo) {
    Nodo *nodo_2 = (*nodo)->direita;

    (*nodo)->direita = nodo_2->esquerda;
    nodo_2->esquerda = *nodo;
    *nodo = nodo_2;

    (*nodo)->fb = 0;
    (*nodo)->esquerda->fb = 0;
}

void Rotacao_Direita_Esquerda(Nodo **nodo) {
    Nodo *nodo_2 = (*nodo)->direita;
    Nodo *nodo_3 = nodo_2->esquerda;

    (*nodo)->direita = nodo_3->esquerda;
    nodo_3->esquerda = *nodo;
    nodo_2->esquerda = nodo_3->direita;
    nodo_3->direita = nodo_2;
    *nodo = nodo_3;

    if ((*nodo)->fb == 1) {
        (*nodo)->esquerda->fb = -1;
    }
    else {
        (*nodo)->esquerda->fb = 0;
    }
    if ((*nodo)->fb == -1) {
        (*nodo)->direita->fb = 1;
    }
    else {
        (*nodo)->direita->fb = 0;
    }
    (*nodo)->fb = 0;
}

void TS_Inserir_Interno(Nodo **nodo, char *palavra, int *checar) {
    if (*nodo == NULL) {
        *nodo = malloc(sizeof(Nodo));
        (*nodo)->esquerda = NULL;
        (*nodo)->direita = NULL;
        (*nodo)->fb = 0;
        strcpy((*nodo)->chave, palavra);

        (*nodo)->P = malloc(sizeof(Posicao));
        (*nodo)->P->posicao = posicao;
        (*nodo)->P->p_chave = (*nodo)->chave;
        (*nodo)->P->proximo = NULL;
        (*nodo)->P->pos_antes = ultimo;
        (*nodo)->P->pos_depois = NULL;

        posicao++;
        if (ultimo != NULL) {
            ultimo->pos_depois = (*nodo)->P;
        }
        ultimo = (*nodo)->P;

        *checar = 1;
    }
    else if (strcasecmp(palavra, (*nodo)->chave) < 0) {
        TS_Inserir_Interno(&((*nodo)->esquerda), palavra, checar);

        if (*checar == 1) {
            if ((*nodo)->fb == -1) {
                if ((*nodo)->esquerda->fb == -1) {
                    Rotacao_Direita(nodo);
                }
                else {
                    Rotacao_Esquerda_Direita(nodo);
                }
                *checar = 0;
            }
            else if ((*nodo)->fb == 0) {
                (*nodo)->fb = -1;
            }
            else {
                (*nodo)->fb = 0;
                *checar = 0;
            }
        }
    }
    else if (strcasecmp(palavra, (*nodo)->chave) > 0) {
        TS_Inserir_Interno(&((*nodo)->direita), palavra, checar);

        if (*checar == 1) {
            if ((*nodo)->fb == 1) {
                if ((*nodo)->direita->fb == 1) {
                    Rotacao_Esquerda(nodo);
                }
                else {
                    Rotacao_Direita_Esquerda(nodo);
                }
                *checar = 0;
            }
            else if ((*nodo)->fb == 0) {
                (*nodo)->fb = 1;
            }
            else {
                (*nodo)->fb = 0;
                *checar = 0;
            }
        }
    }
    else {
        Posicao *aux = (*nodo)->P;
        while (aux->proximo != NULL) {
            aux = aux->proximo;
        }

        aux->proximo = malloc(sizeof(Posicao));
        aux->proximo->posicao = posicao;
        aux->proximo->p_chave = (*nodo)->chave;
        aux->proximo->proximo = NULL;
        aux->proximo->pos_antes = ultimo;
        aux->proximo->pos_depois = NULL;

        posicao++;
        if (ultimo != NULL) {
            ultimo->pos_depois = aux->proximo;
        }
        ultimo = aux->proximo;

        *checar = 0;
    }
}

void TS_Inserir(TabelaSimbolos T, char *palavra) {
    int checar = 0;

    TS_Inserir_Interno(&(T->raiz), palavra, &checar);
}

void TS_Buscar_Interno(Nodo *nodo, char *palavra, int pos) {
    if (nodo == NULL) {
        return;
    }
    else if (strcasecmp(palavra, nodo->chave) < 0) {
        TS_Buscar_Interno(nodo->esquerda, palavra, pos);
    }
    else if (strcasecmp(palavra, nodo->chave) > 0) {
        TS_Buscar_Interno(nodo->direita, palavra, pos);
    }
    else {
        Posicao *aux = nodo->P;

        if (pos >= 0) {
            while (aux != NULL && aux->posicao != pos) {
                aux = aux->proximo;
            }
            if (aux != NULL && aux->posicao == pos) {
                if (aux->pos_antes != NULL) {
                    if (aux->pos_antes->pos_antes != NULL) {
                        if (aux->pos_antes->pos_antes->pos_antes != NULL) {
                            printf("%s ", aux->pos_antes->pos_antes->pos_antes->p_chave);
                        }
                        printf("%s ", aux->pos_antes->pos_antes->p_chave);
                    }
                    printf("%s ", aux->pos_antes->p_chave);
                }
                printf("%s ", aux->p_chave);
                if (aux->pos_depois != NULL) {
                    printf("%s ", aux->pos_depois->p_chave);
                    if (aux->pos_depois->pos_depois != NULL) {
                        printf("%s ", aux->pos_depois->pos_depois->p_chave);
                        if (aux->pos_depois->pos_depois->pos_depois != NULL) {
                            printf("%s ", aux->pos_depois->pos_depois->pos_depois->p_chave);
                        }
                    }
                }
                printf("\n");
            }
        }
        else {
            while (aux != NULL) {
                printf("%d ", aux->posicao);
                aux = aux->proximo;
            }
            printf("\n");
        }
    }
}

void TS_Buscar(TabelaSimbolos T, char *palavra, int pos) {
    TS_Buscar_Interno(T->raiz, palavra, pos);
}

void TS_Imprimir_Interno(Nodo *nodo) {
    if (nodo != NULL) {
        TS_Imprimir_Interno(nodo->esquerda);

        printf("%s >> ", nodo->chave);
        TS_Buscar_Interno(nodo, nodo->chave, -1);

        TS_Imprimir_Interno(nodo->direita);
    }
}

void TS_Imprimir(TabelaSimbolos T) {
    TS_Imprimir_Interno(T->raiz);
}

