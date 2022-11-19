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

int calculaDistanciaMinima(Dados *dados);

int calculaQuantidadeCaminho(Dados *dados);

bool gerarCasoTeste(char nomeArquivoTeste[], int N, int M, int numeroMinimo, int numeroMaximo);

void imprimerCaminho(Dados *dados);

