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

    clock_t tempoIncial = clock();
    calculaDistanciaMinima(&dados);
    calculaQuantidadeCaminho(&dados);
    clock_t tempoFinal = clock();


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

    imprimeCaminhos(&dados);

    srand(time(NULL));
    bool a = gerarCasoTeste("randon", 10, 10, 1, 10);
    printf("--------------------------------------------------------------------------------------\n");
    printf("Tempo de execucao: %f ms\n", ((float)(tempoFinal-tempoIncial)) * 1000/(CLOCKS_PER_SEC));
    return 0;
}