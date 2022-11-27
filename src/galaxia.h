#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>

typedef struct{
    int **grid;
    int N;
    int M;
}Dados;

bool leituraDados(Dados *dados, char nomeArquivo[]);

void inicializaMatriz(Dados *dados, int N, int M);

void inserirDistancia(Dados *dados, int distancia, int i, int j);

int calculaDistanciaMinima(Dados *dados);

int calculaDistanciaMinimaParada(Dados *dados, int linha, int coluna);

int calculaQuantidadeCaminho(Dados *dados);

int calculaQuantidadeCaminhoParada(Dados *dados, int linha, int coluna);

bool gerarCasoTeste(char nomeArquivoTeste[], int N, int M, int numeroMinimo, int numeroMaximo);

void imprimerCaminho(Dados *dados);

void imprimerCaminhoParada(Dados *dados, int linha, int coluna);
