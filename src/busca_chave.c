/*
    Projeto e análise de algoritmos II
    Projeto 1: A Missão no Edifício João Calvino

    Carlos Eduardo Diniz de Almeida RA 10444407
    Guilherme Silveira Giacomini    RA 10435311
    Matheus Mendonça Lopes          RA 10443495
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 100

// função que verifica se a posição (linha x coluna) está dentro dos limites da matriz (m x n).
int dentro_limite(int n, int m, int linha, int coluna) {
    return linha >= 0 && linha < n && coluna >= 0 && coluna < m;
}

// Abaixo é a busca com algoritmo de backtracking para encontrar a chave (*)
int busca_chave(char edificio[MAX_SIZE][MAX_SIZE], int visitado[MAX_SIZE][MAX_SIZE],
                int n, int m, int linha, int coluna) {

    // Caso base que termina a função caso esteja fora dos limites ou se a posição já foi visitada
    if (!dentro_limite(n, m, linha, coluna) || visitado[linha][coluna])
        return 0;

    // Caso a chave tenha sido encontrada, retorna 1 (que representa sucesso)
    if (edificio[linha][coluna] == '*')
        return 1;

    // Marca a posição como visitada
    visitado[linha][coluna] = 1;


    int achou = 0;
    
    // Abaixo, é verificada a letra atual, e então se chama a função novamente para horizontal ou vertical.
    // Se for corredor horizontal, tenta ir para esquerda e direita
    if (edificio[linha][coluna] == 'H') {
        achou = busca_chave(edificio, visitado, n, m, linha, coluna - 1) ||
                busca_chave(edificio, visitado, n, m, linha, coluna + 1);
    } 
    // Se for corredor vertical, tenta ir para cima e para baixo
    else if (edificio[linha][coluna] == 'V') {
        achou = busca_chave(edificio, visitado, n, m, linha - 1, coluna) ||
                busca_chave(edificio, visitado, n, m, linha + 1, coluna);
    }

    // Parte crucial do Backtracking, desfaz a marcação de que a posição foi visitada para testar outros caminhos
    visitado[linha][coluna] = 0;

    return achou;
}

int main(int argc, char *argv[]) {
    
    // Verificando se o nome do arquivo foi informado como parâmetro
    if (argc != 2) {
        printf("Modo de uso: ./busca_chave nome_do_arquivo.txt\n");
        return 1;
    }

    // Abrindo o arquivo de entrada em modo de leitura
    FILE *arquivo = fopen(argv[1], "r");

    // Verificando se foi possível abrir o arquivo informado
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo de entrada\n");
        return 1;
    }

    int n;

    // Aqui se lê o "tamanho" do edifício; no caso, o número de linhas
    if (fscanf(arquivo, "%d", &n) != 1 || n <= 0 || n > MAX_SIZE) {
        printf("Erro na leitura do tamanho do edifício.\n");
        return 1;
    }

    char edificio[MAX_SIZE][MAX_SIZE];
    int m = -1; // número de colunas não é informado como parte da entrada, portanto apenas é importanto que todos andares possuam a mesma qtd de linhas

    // Lendo matriz informada no arquivo, e define as informações do edifício
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

    // Lê a posição inicial informada na entrada
    int linha_ini, coluna_ini;
    if (fscanf(arquivo, "%d %d", &linha_ini, &coluna_ini) != 2 ||
        !dentro_limite(n, m, linha_ini, coluna_ini)) {
        printf("Erro na leitura da posição inicial.\n");
        return 1;
    }

    // Matriz para verificar se uma posição foi visitada
    int visitado[MAX_SIZE][MAX_SIZE] = {0};

    // Chamada inicial para realizar a busca da chave
    int resultado = busca_chave(edificio, visitado, n, m, linha_ini, coluna_ini);

    if (resultado)
        printf("Chave encontrada no Edifício João Calvino!\n");
    else
        printf("Não conseguimos encontrar a chave no Edifício João Calvino.\n");


    fclose(arquivo);
    return 0;
}