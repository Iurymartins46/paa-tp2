#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>

typedef struct{
    int **grid;
    int **distanciaMinima;
    int N;
    int M;
}Dados;

bool leituraDados(Dados *dados);

void inicializaMatriz(Dados *dados, int N, int M);

void inserirDistancia(Dados *dados, int distancia, int i, int j);

void determinarDistanciaMinima(Dados *dados);

