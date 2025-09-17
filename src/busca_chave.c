#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 100

int dentro_limite(int n, int m, int linha, int coluna) {
    return linha >= 0 && linha < n && coluna >= 0 && coluna < m;
}

int busca_chave(char edificio[MAX_SIZE][MAX_SIZE], int visitado[MAX_SIZE][MAX_SIZE],
                int n, int m, int linha, int coluna) {

    if (!dentro_limite(n, m, linha, coluna) || visitado[linha][coluna])
        return 0;

    if (edificio[linha][coluna] == '*')
        return 1;

    visitado[linha][coluna] = 1;

    int achou = 0;
    if (edificio[linha][coluna] == 'H') {
        achou = busca_chave(edificio, visitado, n, m, linha, coluna - 1) ||
                busca_chave(edificio, visitado, n, m, linha, coluna + 1);
    } else if (edificio[linha][coluna] == 'V') {
        achou = busca_chave(edificio, visitado, n, m, linha - 1, coluna) ||
                busca_chave(edificio, visitado, n, m, linha + 1, coluna);
    }

    visitado[linha][coluna] = 0;

    return achou;
}

int main(int argc, char *argv[]) {
    
    // Verificando se o nome do arquivo foi informado como parâmetro
    if (argc != 2) {
        printf("Modo de uso: ./busca_chave entrada.txt\n");
        return 1;
    }

    //Abrindo o arquivo de entrada em modo de leitura
    FILE *arquivo = fopen(argv[1], "r");

    //Verificando se foi possível abrir o arquivo informado
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo de entrada\n");
        return 1;
    }

    int n;

     //Lendo tamanho do edifício
    if (fscanf(arquivo, "%d", &n) != 1 || n <= 0 || n > MAX_SIZE) {
        printf("Erro na leitura do tamanho do edifício.\n");
        return 1;
    }

    char edificio[MAX_SIZE][MAX_SIZE];
    int m = -1; // número de colunas

    //Lendo matriz informada no arquivo
    for (int i = 0; i < n; i++) {
        int col = 0, ch;
        while (col < MAX_SIZE && (ch = getc(arquivo)) != '\n' && ch != EOF) {
            if (ch == ' ' || ch == '\r') continue; // ignora espaços e '\r'
            edificio[i][col++] = (char)ch;
        }
        if (col == 0) {
            i--;
            continue;
        }
        if (m == -1) m = col;
        else if (col != m) {
            printf("Erro: número de colunas inconsistente.\n");
            return 1;
        }
    }

    int linha_ini, coluna_ini;
    if (fscanf(arquivo, "%d %d", &linha_ini, &coluna_ini) != 2 ||
        !dentro_limite(n, m, linha_ini, coluna_ini)) {
        printf("Erro na leitura da posição inicial.\n");
        return 1;
    }

    int visitado[MAX_SIZE][MAX_SIZE] = {0};

    int resultado = busca_chave(edificio, visitado, n, m, linha_ini, coluna_ini);

    if (resultado)
        printf("Chave encontrada no Edifício João Calvino!\n");
    else
        printf("Não conseguimos encontrar a chave no Edifício João Calvino.\n");


    fclose(arquivo);
    return 0;
}