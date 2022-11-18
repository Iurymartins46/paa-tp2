#include "galaxia.h"

int main(){
    int i, j;
    printf("--------------------------------------------------------------------------------------\n");
    Dados dados;
    bool continuar;

    continuar = leituraDados(&dados);

    if(continuar == false){
        return 0;
    }

    calculaDistanciaMinima(&dados);
    calculaQuantidadeCaminho(&dados);
    for(i = 0; i < dados.N; i++){
        for(j = 0; j < dados.M; j++){
            printf("%-6d ", dados.grid[i][j]);
        }
        printf("\n");
    }
    printf("\n");
    for(i = 0; i < dados.N; i++){
        for(j = 0; j < dados.M; j++){
            printf("%-6d ", dados.distanciaMinima[i][j]);
        }
        printf("\n");
    }
    printf("\n");
    for(i = 0; i < dados.N; i++){
        for(j = 0; j < dados.M; j++){
            printf("%-6d ", dados.quantidadeCaminho[i][j]);
        }
        printf("\n");
    }
    printf("\n");
    printf("--------------------------------------------------------------------------------------\n");
    return 0;
}