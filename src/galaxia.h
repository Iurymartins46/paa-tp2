#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>

typedef struct{
    int **grid;
    int **distanciaMinima;
    int **quantidadeCaminho;
    int N;
    int M;
}Dados;

typedef struct{
    int i;
    int j;
    int i2;
    int j2;
}Celula;

bool leituraDados(Dados *dados);

void inicializaMatriz(Dados *dados, int N, int M);

void inserirDistancia(Dados *dados, int distancia, int i, int j);

void calculaDistanciaMinima(Dados *dados);

void calculaQuantidadeCaminho(Dados *dados);

bool gerarCasoTeste(char nomeArquivoTeste[], int N, int M, int numeroMinimo, int numeroMaximo);

void imprimeCaminhos(Dados *dados);

void imprimeCaminhosAux(Dados *dados, char* caminhos, Celula** caminho, int linha, int coluna);