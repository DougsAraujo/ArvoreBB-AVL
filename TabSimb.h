#ifndef TABELA_SIMBOLOS
#define TABELA_SIMBOLOS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Posicao {
    int posicao;
    char *p_chave;
    struct Posicao *proximo;
    struct Posicao *pos_antes;
    struct Posicao *pos_depois;
} Posicao;

typedef struct Nodo {
    int fb;
    char chave[40];
    Posicao *P;
    struct Nodo *esquerda;
    struct Nodo *direita;
} Nodo;

typedef struct TS {
    Nodo *raiz;
} TS;

typedef TS* TabelaSimbolos;

TabelaSimbolos Nova_Tabela();
void TS_Inserir(TabelaSimbolos T, char *palavra);
void TS_Buscar(TabelaSimbolos T, char *palavra, int pos);
void TS_Imprimir(TabelaSimbolos T);

#endif

