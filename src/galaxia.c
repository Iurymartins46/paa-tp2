#include "galaxia.h"

bool leituraDados(Dados *dados){
    int N, M, distancia, i, j;
    char nomeArquivo[50] = "test02";
    char diretorio[100];
    strcpy(diretorio, "tests/");
    strcat(strcat(diretorio, nomeArquivo), ".txt");
    FILE *file;
    file = fopen(diretorio, "r");
    if(file == NULL){
        printf("\nErro na abertura do arquivo de entrada !!!!!!!!\n\n");
        return false;
    }
    fscanf(file, "%d %d", &N, &M);
    inicializaMatriz(dados, N, M);
    for(i = 0; i < N; i++){
        for(j = 0; j < M; j++){
            fscanf(file, "%d ", &distancia);
            inserirDistancia(dados, distancia, i, j);
        }
    }
    fclose(file);
    return true;
}

void inicializaMatriz(Dados *dados, int N, int M){
    dados->N = N;
    dados->M = M;
    dados->grid = (int**)malloc(N * sizeof(int*));
    dados->distanciaMinima = (int**)malloc(N * sizeof(int*));
    for(int i = 0; i < N; i++){
        dados->grid[i] = (int*)malloc(M * sizeof(int));
        dados->distanciaMinima[i] = (int*)malloc(M * sizeof(int));
    }
}

void inserirDistancia(Dados *dados, int distancia, int i, int j){
    dados->grid[i][j] = distancia;
    dados->distanciaMinima[i][j] = distancia;
}

void determinarDistanciaMinima(Dados *dados){
    int i, j;
    for(i = dados->N - 1; i >= 0; i--){
        for(j = dados->M - 1; j >= 0; j--){
            if(i == dados->N - 1 && j == dados->M - 1){
                dados->distanciaMinima[i][j] = dados->distanciaMinima[i][j];
            }
            else if(i == dados->N - 1){
                dados->distanciaMinima[i][j] = dados->distanciaMinima[i][j] + dados->distanciaMinima[i][j + 1];
            }
            else if(j == dados->M - 1){
                dados->distanciaMinima[i][j] = dados->distanciaMinima[i][j] + dados->distanciaMinima[i + 1][j];
            }
            else{
                if(dados->distanciaMinima[i][j + 1] <= dados->distanciaMinima[i + 1][j]){
                    dados->distanciaMinima[i][j] = dados->distanciaMinima[i][j] + dados->distanciaMinima[i][j + 1];
                }
                else{
                    dados->distanciaMinima[i][j] = dados->distanciaMinima[i][j] + dados->distanciaMinima[i + 1][j];
                }
            }
        }
    }
}


