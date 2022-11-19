#include "galaxia.h"

bool leituraDados(Dados *dados){
    int N, M, distancia, i, j;
    char nomeArquivo[50] = "testPaint";
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
    dados->quantidadeCaminho = (int**)malloc(N * sizeof(int*));
    for(int i = 0; i < N; i++){
        dados->grid[i] = (int*)malloc(M * sizeof(int));
        dados->distanciaMinima[i] = (int*)malloc(M * sizeof(int));
        dados->quantidadeCaminho[i] = (int*)calloc(M, sizeof(int));
    }
}

void inserirDistancia(Dados *dados, int distancia, int i, int j){
    dados->grid[i][j] = distancia;
    dados->distanciaMinima[i][j] = distancia;
}

void calculaDistanciaMinima(Dados *dados){
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

void calculaQuantidadeCaminho(Dados *dados){
    int i, j;
    for(i = dados->N - 1; i >= 0; i--){
        for(j = dados->M - 1; j >= 0; j--){
            if(i == dados->N - 1 && j == dados->M - 1){
                dados->quantidadeCaminho[i][j] = 1;
            }
            else if(i == dados->N - 1 || j == dados->M - 1){
                dados->quantidadeCaminho[i][j] = 1;
            }
            else{
                if(dados->distanciaMinima[i][j + 1] < dados->distanciaMinima[i + 1][j]){
                    dados->quantidadeCaminho[i][j] = dados->quantidadeCaminho[i][j + 1];
                }
                else if(dados->distanciaMinima[i + 1][j] < dados->distanciaMinima[i][j + 1]){
                    dados->quantidadeCaminho[i][j] = dados->quantidadeCaminho[i + 1][j];
                }
                else{
                    dados->quantidadeCaminho[i][j] = dados->quantidadeCaminho[i + 1][j] + dados->quantidadeCaminho[i][j + 1];
                }
            }
        }
    }
}

void imprimeCaminhos(Dados *dados){
    Celula **caminho;
    caminho = (Celula**)malloc(dados->N * sizeof(Celula*));
    for (int i = 0; i < dados->N; i++){
        caminho[i] = (Celula*)calloc(dados->M, sizeof(Celula));
        for (int j = 0; j < dados->M; j++){
            caminho[i][j].i = -1;
            caminho[i][j].i2 = -1;
            caminho[i][j].j = -1;
            caminho[i][j].j2 = -1;
        }
    }
    for(int i = 0; i < dados->N ; i++){
        for(int j = 0; j < dados->M; j++){
            if (i == dados->N - 1 && j == dados->M - 1){
                caminho[i][j].i = -2;
                caminho[i][j].j = -2;
            }else if (i == dados->M - 1 && j < dados->M - 1){
                caminho[i][j].i = i;
                caminho[i][j].j = j + 1;
            }else if (i < dados->M - 1 && j == dados->M - 1){
                caminho[i][j].i = i + 1;
                caminho[i][j].j = j;
            }else{
                if (i != dados->N - 1 && j != dados->M - 1){
                    if(dados->distanciaMinima[i][j + 1] < dados->distanciaMinima[i + 1][j]){
                        caminho[i][j].i = i;
                        caminho[i][j].j = j + 1;
                    }else if(dados->distanciaMinima[i + 1][j] < dados->distanciaMinima[i][j + 1]){
                        caminho[i][j].i = i + 1;
                        caminho[i][j].j = j;
                    }else{
                        caminho[i][j].i = i;
                        caminho[i][j].j = j + 1;
                        caminho[i][j].i2 = i + 1;
                        caminho[i][j].j2 = j;
                    }
                }
            }
        }
    }

    char *stringCamninhos = (char*)malloc(sizeof(char));

    imprimeCaminhosAux(dados, stringCamninhos, caminho, 0, 0);
    puts("\n");
}

void imprimeCaminhosAux(Dados *dados, char* caminhos, Celula** caminho, int linha, int coluna){
    printf("(%d, %d) ", linha, coluna);
    if (caminho[linha][coluna].i == -2){
        return;
    }
    imprimeCaminhosAux(dados, caminhos, caminho, caminho[linha][coluna].i, caminho[linha][coluna].j);
    if (caminho[linha][coluna].i2 != -1){
        imprimeCaminhosAux(dados, caminhos, caminho, caminho[linha][coluna].i2, caminho[linha][coluna].j2);
    }
}

bool gerarCasoTeste(char nomeArquivoTeste[], int N, int M, int numeroMinimo, int numeroMaximo){
    int i, j, numero;
    char diretorio[100];
    strcpy(diretorio, "tests/");
    strcat(strcat(diretorio, nomeArquivoTeste), ".txt");
    FILE *file;
    file = fopen(diretorio,"w");
    if(file == NULL){
        printf("\nErro na criacao do arquivo de teste !!!!!!!!\n\n");
        return false;
    }
    fprintf(file, "%d %d\n", N, M);
    for(i = 0; i < N; i++){
        for(j = 0; j < M; j++){
            numero = numeroMinimo + (rand() % (numeroMaximo - numeroMinimo + 1));
            fprintf(file, "%d ", numero);
        }
        fprintf(file, "\n");
    }

    fclose(file);
    return true;
}
