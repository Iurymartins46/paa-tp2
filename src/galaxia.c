#include "galaxia.h"


void calculaDistanciaMinimaInterno(int ***distanciaMinima, int linhaInicio, int colunaInicio, int linhaFinal, int colunaFinal);
void calculaQuantidadeCaminhoInterno(Dados *dados, int ***quantidadeCaminho, int ***distanciaMinima, int linhaInicio, int colunaInicio, int linhaFinal, int colunaFinal);
void imprimerCaminhoInterno(Dados *dados, char *caminho, int ***distanciaMinima, int *caminhosMostrados, int linha, int coluna, int linhaParada, int colunaParada);

bool leituraDados(Dados *dados){
    int N, M, distancia, i, j;
    char nomeArquivo[50] = "test04";
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

/*
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

int calculaDistanciaMinima(Dados *dados){
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
    return dados->distanciaMinima[0][0];
}

int calculaQuantidadeCaminho(Dados *dados){
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
    return dados->quantidadeCaminho[0][0];
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
    imprimerCaminhoInterno(dados, "", &caminhosMostrados, 0, 0);
}

void imprimerCaminhoInterno(Dados *dados, char *caminho, int *caminhosMostrados, int linha, int coluna){
    if((*caminhosMostrados) >= 20){
        return;
    }
    if(linha == dados->N - 1 && coluna == dados->M - 1){
        printf("%s(%d,%d)\n", caminho, linha, coluna);
        (*caminhosMostrados)++;
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
        if(linha == dados->N - 1){
            imprimerCaminhoInterno(dados, aux1, caminhosMostrados, linha, coluna + 1);
        }
        else if(coluna == dados->M - 1){
            imprimerCaminhoInterno(dados, aux1, caminhosMostrados, linha + 1, coluna);
        }
        else{
            if(dados->distanciaMinima[linha][coluna + 1] < dados->distanciaMinima[linha + 1][coluna]){
                imprimerCaminhoInterno(dados, aux1, caminhosMostrados, linha, coluna + 1);
            }
            else if(dados->distanciaMinima[linha + 1][coluna] < dados->distanciaMinima[linha][coluna + 1]){
                imprimerCaminhoInterno(dados, aux1, caminhosMostrados, linha + 1, coluna);;
            }
            else{
                imprimerCaminhoInterno(dados, aux1, caminhosMostrados, linha + 1, coluna);
                imprimerCaminhoInterno(dados, aux1, caminhosMostrados, linha, coluna + 1);
            }
        }
    }
}
*/

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
    calculaDistanciaMinimaInterno(&distanciaMinima, linha, coluna, dados->N - 1, dados->N - 1);
    calculaDistanciaMinimaInterno(&distanciaMinima, 0, 0, linha, coluna);
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
    calculaDistanciaMinimaInterno(&distanciaMinima, linha, coluna, dados->N - 1, dados->N - 1);
    calculaDistanciaMinimaInterno(&distanciaMinima, 0, 0, linha, coluna);
    calculaQuantidadeCaminhoInterno(dados, &quantidadeCaminho, &distanciaMinima, linha, coluna, dados->N - 1, dados->N - 1);
    calculaQuantidadeCaminhoInterno(dados, &quantidadeCaminho, &distanciaMinima,  0, 0, linha, coluna);
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
    calculaDistanciaMinimaInterno(&distanciaMinima, linha, coluna, dados->N - 1, dados->N - 1);
    calculaDistanciaMinimaInterno(&distanciaMinima, 0, 0, linha, coluna);

    imprimerCaminhoInterno(dados, "", &distanciaMinima, &caminhosMostrados, 0, 0, linha, coluna);
}

void imprimerCaminhoInterno(Dados *dados, char *caminho, int ***distanciaMinima, int *caminhosMostrados, int linha, int coluna, int linhaParada, int colunaParada){
    //printf("%s\n", caminho);
    if((*caminhosMostrados) >= 20){
        return;
    }
    if(linha == dados->N - 1 && coluna == dados->M - 1){
        printf("%s(%d,%d)\n", caminho, linha, coluna);
        (*caminhosMostrados)++;
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
            //printf("-->1\n");
            imprimerCaminhoInterno(dados, aux1, distanciaMinima, caminhosMostrados, linha, coluna + 1, linhaParada, colunaParada);
        }
        else if((coluna == dados->M - 1) || (coluna == colunaParada && linha < linhaParada)){
            //printf("-->2\n");
            imprimerCaminhoInterno(dados, aux1, distanciaMinima, caminhosMostrados, linha + 1, coluna, linhaParada, colunaParada);
        }
        else{
            if((*distanciaMinima)[linha][coluna + 1] < (*distanciaMinima)[linha + 1][coluna]){
                //printf("-->3\n");
                imprimerCaminhoInterno(dados, aux1, distanciaMinima, caminhosMostrados, linha, coluna + 1, linhaParada, colunaParada);
            }
            else if((*distanciaMinima)[linha + 1][coluna] < (*distanciaMinima)[linha][coluna + 1]){
                //printf("-->4\n");
                imprimerCaminhoInterno(dados, aux1, distanciaMinima, caminhosMostrados, linha + 1, coluna, linhaParada, colunaParada);;
            }
            else{
                //printf("-->5\n");
                //printf("-->5.1\n");
                imprimerCaminhoInterno(dados, aux1, distanciaMinima, caminhosMostrados, linha + 1, coluna, linhaParada, colunaParada);
                //printf("-->5.2\n");
                imprimerCaminhoInterno(dados, aux1, distanciaMinima, caminhosMostrados, linha, coluna + 1, linhaParada, colunaParada);
            }
        }
    }
}

