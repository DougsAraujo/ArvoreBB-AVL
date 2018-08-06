#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "TabSimb.h"

void Tratar_Palavra(char *palavra) {
    int i;

    for (i = 0; i < strlen(palavra); i++) {
        if (palavra[i] == '�' || palavra[i] == '�' || palavra[i] == '�' || palavra[i] == '�' ||
            palavra[i] == '�' || palavra[i] == '�' || palavra[i] == '�' || palavra[i] == '�' ||
            palavra[i] == '�' || palavra[i] == '�') {
            palavra[i] = 'a';
        }
        else if (palavra[i] == '�' || palavra[i] == '�') {
            palavra[i] = 'c';
        }
        else if (palavra[i] == '�' || palavra[i] == '�' || palavra[i] == '�' || palavra[i] == '�' ||
            palavra[i] == '�' || palavra[i] == '�' || palavra[i] == '�' || palavra[i] == '�') {
            palavra[i] = 'e';
        }
        else if (palavra[i] == '�' || palavra[i] == '�' || palavra[i] == '�' || palavra[i] == '�' ||
            palavra[i] == '�' || palavra[i] == '�' || palavra[i] == '�' || palavra[i] == '�') {
            palavra[i] = 'i';
        }
        else if (palavra[i] == '�' || palavra[i] == '�') {
            palavra[i] = 'n';
        }
        else if (palavra[i] == '�' || palavra[i] == '�' || palavra[i] == '�' || palavra[i] == '�' ||
            palavra[i] == '�' || palavra[i] == '�' || palavra[i] == '�' || palavra[i] == '�' ||
            palavra[i] == '�' || palavra[i] == '�') {
            palavra[i] = 'o';
        }
        else if (palavra[i] == '�' || palavra[i] == '�' || palavra[i] == '�' || palavra[i] == '�' ||
            palavra[i] == '�' || palavra[i] == '�' || palavra[i] == '�' || palavra[i] == '�') {
            palavra[i] = 'u';
        }
        else if (palavra[i] == '�' || palavra[i] == '�' || palavra[i] == '�') {
            palavra[i] = 'y';
        }
        if (isupper(palavra[i])) {
            palavra[i] = tolower(palavra[i]);
        }
    }
}

int Inserir_Texto(TabelaSimbolos T, char *nome_texto) {
    FILE *texto = fopen(nome_texto, "r");

    if (texto == NULL) {
        return 0;
    }

    char *p_palavra = NULL;
    char palavra[40];

    while (!feof(texto)) {
        fscanf(texto, "%s", palavra);
        p_palavra = strtok(palavra, "!?.,:;+-*/^~<>=()[]{}\\|_'\"@#$%&");
        while (p_palavra) {
            Tratar_Palavra(p_palavra);
            printf("%s\n", p_palavra);
            TS_Inserir(T, p_palavra);
            p_palavra = strtok(NULL, "!?.,:;+-*/^~<>=()[]{}\\|_'\"@#$%&");
        }
    }

    fclose(texto);

    return 1;
}

void Executar_Buscas(TabelaSimbolos T) {
    char *p_palavra = NULL;
    char palavra[40];
    int posicao = -1;

    while (strcmp(palavra, ".") != 0) {
        fgets(palavra, sizeof(palavra), stdin);
        palavra[strlen(palavra)-1] = '\0';
        if (strlen(palavra) == 0) {
            continue;
        }

        p_palavra = strtok(palavra, " ");
        strcpy(palavra, p_palavra);
        Tratar_Palavra(palavra);

        posicao = -1;
        p_palavra = strtok(NULL, " ");
        if (p_palavra) {
            posicao = atoi(p_palavra);
        }

        if (strcmp(palavra, ";") == 0) {
            TS_Imprimir(T);
            continue;
        }

        TS_Buscar(T, palavra, posicao);
    }
}

int main(int c, char *argv[]) {
    TabelaSimbolos T = Nova_Tabela();

    if (Inserir_Texto(T, argv[1]) == 0) {
        printf("Arquivo inexistente.\n");
        return -1;
    }
    Executar_Buscas(T);

	return 0;
}

