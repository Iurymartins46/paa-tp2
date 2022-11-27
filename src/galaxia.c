#include "galaxia.h"


void calculaDistanciaMinimaInterno(int ***distanciaMinima, int linhaInicio, int colunaInicio, int linhaFinal, int colunaFinal);
void calculaQuantidadeCaminhoInterno(Dados *dados, int ***quantidadeCaminho, int ***distanciaMinima, int linhaInicio, int colunaInicio, int linhaFinal, int colunaFinal);
void imprimerCaminhoInterno(Dados *dados, char *caminho, int ***distanciaMinima, int *caminhosMostrados, int linha, int coluna, int linhaParada, int colunaParada);

bool leituraDados(Dados *dados, char nomeArquivo[]){
    int N, M, distancia, i, j;
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
    for(int i = 0; i < N; i++){
        dados->grid[i] = (int*)malloc(M * sizeof(int));
    }
}

void inserirDistancia(Dados *dados, int distancia, int i, int j){
    dados->grid[i][j] = distancia;
}

int calculaDistanciaMinima(Dados *dados){
    int i, j;
    int **distanciaMinima;
    distanciaMinima = (int**)malloc(dados->N * sizeof(int*));
    for(i = 0; i < dados->N; i++){
        distanciaMinima[i] = (int*)malloc(dados->M * sizeof(int));
    }
    for(i = 0; i < dados->N; i++){
        for(j = 0; j < dados->M; j++){
            distanciaMinima[i][j] = dados->grid[i][j];
        }
    }
    calculaDistanciaMinimaInterno(&distanciaMinima, 0, 0, dados->N - 1, dados->N - 1);
    return distanciaMinima[0][0];
}

int calculaDistanciaMinimaParada(Dados *dados, int linha, int coluna){
    if((linha > dados->N) || (coluna > dados->N)){
        printf("Possicao fora da matriz\n");
        return 0;
    }
    int i, j;
    int **distanciaMinima;
    distanciaMinima = (int**)malloc(dados->N * sizeof(int*));
    for(i = 0; i < dados->N; i++){
        distanciaMinima[i] = (int*)malloc(dados->M * sizeof(int));
    }
    for(i = 0; i < dados->N; i++){
        for(j = 0; j < dados->M; j++){
            distanciaMinima[i][j] = dados->grid[i][j];
        }
    }
    calculaDistanciaMinimaInterno(&distanciaMinima, linha -1, coluna -1, dados->N - 1, dados->N - 1);
    calculaDistanciaMinimaInterno(&distanciaMinima, 0, 0, linha -1, coluna -1);
    return distanciaMinima[0][0];
}

void calculaDistanciaMinimaInterno(int ***distanciaMinima, int linhaInicio, int colunaInicio, int linhaFinal, int colunaFinal){
    int i, j;
    for(i = linhaFinal; i >= linhaInicio; i--){
        for(j = colunaFinal; j >= colunaInicio; j--){
            if(i == linhaFinal && j == colunaFinal){
                (*distanciaMinima)[i][j] = (*distanciaMinima)[i][j];
            }
            else if(i == linhaFinal){
                (*distanciaMinima)[i][j] = (*distanciaMinima)[i][j] + (*distanciaMinima)[i][j + 1];
            }
            else if(j == colunaFinal){
                (*distanciaMinima)[i][j] = (*distanciaMinima)[i][j] + (*distanciaMinima)[i + 1][j];
            }
            else{
                if((*distanciaMinima)[i][j + 1] <= (*distanciaMinima)[i + 1][j]){
                    (*distanciaMinima)[i][j] = (*distanciaMinima)[i][j] + (*distanciaMinima)[i][j + 1];
                }
                else{
                    (*distanciaMinima)[i][j] = (*distanciaMinima)[i][j] + (*distanciaMinima)[i + 1][j];
                }
            }
        }
    }
}

int calculaQuantidadeCaminho(Dados *dados){
    int i, j;
    int **quantidadeCaminho;
    int **distanciaMinima;
    quantidadeCaminho = (int**)malloc( dados->N * sizeof(int*));
    distanciaMinima = (int**)malloc(dados->N * sizeof(int*));
    for(i = 0; i < dados->N; i++){
        quantidadeCaminho[i] = (int*)calloc(dados->M, sizeof(int));
        distanciaMinima[i] = (int*)malloc(dados->M * sizeof(int));
    }
    for(i = 0; i < dados->N; i++){
        for(j = 0; j < dados->M; j++){
            distanciaMinima[i][j] = dados->grid[i][j];
        }
    }
    calculaDistanciaMinimaInterno(&distanciaMinima, 0, 0, dados->N - 1, dados->N - 1);
    calculaQuantidadeCaminhoInterno(dados, &quantidadeCaminho, &distanciaMinima,  0, 0, dados->N - 1, dados->N - 1);
    return quantidadeCaminho[0][0];
}

int calculaQuantidadeCaminhoParada(Dados *dados, int linha, int coluna){
    if((linha > dados->N) || (coluna > dados->N)){
        printf("Possicao fora da matriz\n");
        return 0;
    }
    int i, j;
    int **quantidadeCaminho;
    int **distanciaMinima;
    quantidadeCaminho = (int**)malloc( dados->N * sizeof(int*));
    distanciaMinima = (int**)malloc(dados->N * sizeof(int*));
    for(i = 0; i < dados->N; i++){
        quantidadeCaminho[i] = (int*)calloc(dados->M, sizeof(int));
        distanciaMinima[i] = (int*)malloc(dados->M * sizeof(int));
    }
    for(i = 0; i < dados->N; i++){
        for(j = 0; j < dados->M; j++){
            distanciaMinima[i][j] = dados->grid[i][j];
        }
    }
    calculaDistanciaMinimaInterno(&distanciaMinima, linha -1, coluna -1, dados->N - 1, dados->N - 1);
    calculaDistanciaMinimaInterno(&distanciaMinima, 0, 0, linha -1, coluna -1);
    calculaQuantidadeCaminhoInterno(dados, &quantidadeCaminho, &distanciaMinima, linha -1, coluna -1, dados->N - 1, dados->N - 1);
    calculaQuantidadeCaminhoInterno(dados, &quantidadeCaminho, &distanciaMinima,  0, 0, linha -1, coluna -1);
    return quantidadeCaminho[0][0];
}

void calculaQuantidadeCaminhoInterno(Dados *dados, int ***quantidadeCaminho, int ***distanciaMinima, int linhaInicio, int colunaInicio, int linhaFinal, int colunaFinal){
    int i, j;
    for(i = linhaFinal; i >= linhaInicio; i--){
        for(j = colunaFinal; j >= colunaInicio; j--){
            if((i == linhaFinal) || (j == colunaFinal)){
                if(((linhaFinal != dados->N - 1) && (colunaFinal != dados->M - 1)) && ((i == linhaFinal) && (j == colunaFinal))){
                    (*quantidadeCaminho)[i][j] = (*quantidadeCaminho)[i][j];
                }
                else if((linhaFinal != dados->N - 1) && (j != colunaFinal)){
                    (*quantidadeCaminho)[i][j] = (*quantidadeCaminho)[i][j + 1];
                }
                else if((colunaFinal != dados->M - 1) && (i != linhaFinal)){
                    (*quantidadeCaminho)[i][j] = (*quantidadeCaminho)[i + 1][j];
                }
                else{
                    (*quantidadeCaminho)[i][j] = 1;
                }
            }
            else{
                if((*distanciaMinima)[i][j + 1] < (*distanciaMinima)[i + 1][j]){
                    (*quantidadeCaminho)[i][j] = (*quantidadeCaminho)[i][j + 1];
                }
                else if((*distanciaMinima)[i + 1][j] < (*distanciaMinima)[i][j + 1]){
                    (*quantidadeCaminho)[i][j] = (*quantidadeCaminho)[i + 1][j];
                }
                else{
                    (*quantidadeCaminho)[i][j] = (*quantidadeCaminho)[i + 1][j] + (*quantidadeCaminho)[i][j + 1];
                }
            } 
        }
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

void imprimerCaminho(Dados *dados){
    int caminhosMostrados = 0;
    int i, j;
    int **distanciaMinima;
    distanciaMinima = (int**)malloc(dados->N * sizeof(int*));
    for(i = 0; i < dados->N; i++){
        distanciaMinima[i] = (int*)malloc(dados->M * sizeof(int));
    }
    for(i = 0; i < dados->N; i++){
        for(j = 0; j < dados->M; j++){
            distanciaMinima[i][j] = dados->grid[i][j];
        }
    }
    calculaDistanciaMinimaInterno(&distanciaMinima, 0, 0, dados->N - 1, dados->N - 1);
    imprimerCaminhoInterno(dados, "", &distanciaMinima, &caminhosMostrados, 0, 0, -1, -1);
}

void imprimerCaminhoParada(Dados *dados, int linha, int coluna){
    if((linha > dados->N) || (coluna > dados->N)){
        printf("Possicao fora da matriz\n");
        return;
    }
    int caminhosMostrados = 0;
    int i, j;
    int **distanciaMinima;
    distanciaMinima = (int**)malloc(dados->N * sizeof(int*));
    for(i = 0; i < dados->N; i++){
        distanciaMinima[i] = (int*)malloc(dados->M * sizeof(int));
    }
    for(i = 0; i < dados->N; i++){
        for(j = 0; j < dados->M; j++){
            distanciaMinima[i][j] = dados->grid[i][j];
        }
    }
    calculaDistanciaMinimaInterno(&distanciaMinima, linha -1, coluna -1, dados->N - 1, dados->N - 1);
    calculaDistanciaMinimaInterno(&distanciaMinima, 0, 0, linha -1, coluna -1);

    imprimerCaminhoInterno(dados, "", &distanciaMinima, &caminhosMostrados, 0, 0, linha -1, coluna -1);
}

void imprimerCaminhoInterno(Dados *dados, char *caminho, int ***distanciaMinima, int *caminhosMostrados, int linha, int coluna, int linhaParada, int colunaParada){
    if((*caminhosMostrados) >= 20){
        return;
    }
    if(linha == dados->N - 1 && coluna == dados->M - 1){
        printf("%s(%d,%d)\n", caminho, linha, coluna);
        (*caminhosMostrados)++;
        if((*caminhosMostrados) == 20){
            printf("Foram impressos apenas 20 caminhos para uma melhor visualizacao\n");
        }
    }
    else{
        char aux1[20000] = "";
        char aux2[100] = "";
        char l[10];
        char c[10];
        sprintf(l, "%d", linha);
        sprintf(c, "%d", coluna);
        strcpy(aux1, "");
        strcpy(aux2, "");
        strcpy(aux1, caminho);
        strcat(aux2, "(");
        strcat(aux2, l);
        strcat(aux2, ",");
        strcat(aux2, c);
        strcat(aux2, ")->");
        strcat(aux1, aux2);
        if((linha == dados->N - 1) || (linha == linhaParada && coluna < colunaParada)){
            imprimerCaminhoInterno(dados, aux1, distanciaMinima, caminhosMostrados, linha, coluna + 1, linhaParada, colunaParada);
        }
        else if((coluna == dados->M - 1) || (coluna == colunaParada && linha < linhaParada)){
            imprimerCaminhoInterno(dados, aux1, distanciaMinima, caminhosMostrados, linha + 1, coluna, linhaParada, colunaParada);
        }
        else{
            if((*distanciaMinima)[linha][coluna + 1] < (*distanciaMinima)[linha + 1][coluna]){
                imprimerCaminhoInterno(dados, aux1, distanciaMinima, caminhosMostrados, linha, coluna + 1, linhaParada, colunaParada);
            }
            else if((*distanciaMinima)[linha + 1][coluna] < (*distanciaMinima)[linha][coluna + 1]){
                imprimerCaminhoInterno(dados, aux1, distanciaMinima, caminhosMostrados, linha + 1, coluna, linhaParada, colunaParada);;
            }
            else{
                imprimerCaminhoInterno(dados, aux1, distanciaMinima, caminhosMostrados, linha + 1, coluna, linhaParada, colunaParada);
                imprimerCaminhoInterno(dados, aux1, distanciaMinima, caminhosMostrados, linha, coluna + 1, linhaParada, colunaParada);
            }
        }
    }
}

