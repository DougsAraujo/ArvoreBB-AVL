#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "TabSimb.h"

void Tratar_Palavra(char *palavra) {
    int i;

    for (i = 0; i < strlen(palavra); i++) {
        if (palavra[i] == 'á' || palavra[i] == 'Á' || palavra[i] == 'à' || palavra[i] == 'À' ||
            palavra[i] == 'â' || palavra[i] == 'Â' || palavra[i] == 'ä' || palavra[i] == 'Ä' ||
            palavra[i] == 'ã' || palavra[i] == 'Ã') {
            palavra[i] = 'a';
        }
        else if (palavra[i] == 'ç' || palavra[i] == 'Ç') {
            palavra[i] = 'c';
        }
        else if (palavra[i] == 'é' || palavra[i] == 'É' || palavra[i] == 'è' || palavra[i] == 'È' ||
            palavra[i] == 'ê' || palavra[i] == 'Ê' || palavra[i] == 'ë' || palavra[i] == 'Ë') {
            palavra[i] = 'e';
        }
        else if (palavra[i] == 'í' || palavra[i] == 'Í' || palavra[i] == 'ì' || palavra[i] == 'Ì' ||
            palavra[i] == 'î' || palavra[i] == 'Î' || palavra[i] == 'ï' || palavra[i] == 'Ï') {
            palavra[i] = 'i';
        }
        else if (palavra[i] == 'ñ' || palavra[i] == 'Ñ') {
            palavra[i] = 'n';
        }
        else if (palavra[i] == 'ó' || palavra[i] == 'Ó' || palavra[i] == 'ò' || palavra[i] == 'Ò' ||
            palavra[i] == 'õ' || palavra[i] == 'Õ' || palavra[i] == 'ö' || palavra[i] == 'Ö' ||
            palavra[i] == 'ô' || palavra[i] == 'Ô') {
            palavra[i] = 'o';
        }
        else if (palavra[i] == 'ú' || palavra[i] == 'Ú' || palavra[i] == 'ù' || palavra[i] == 'Ù' ||
            palavra[i] == 'û' || palavra[i] == 'Û' || palavra[i] == 'ü' || palavra[i] == 'Ü') {
            palavra[i] = 'u';
        }
        else if (palavra[i] == 'ý' || palavra[i] == 'Ý' || palavra[i] == 'ÿ') {
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

