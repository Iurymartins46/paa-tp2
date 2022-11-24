#include "galaxia.h"

int main(){
    /*int i, j;
    printf("--------------------------------------------------------------------------------------\n");
    Dados dados;
    bool continuar;
    clock_t tempoIncial = clock();
    
    continuar = leituraDados(&dados);

    if(continuar == false){
        return 0;
    }

    printf("Soma Minima: %d\n", calculaDistanciaMinima(&dados));
    printf("Quantidade de caminhos: %d\n", calculaQuantidadeCaminho(&dados));

    clock_t tempoFinal = clock();

    srand(time(NULL));
    bool a = gerarCasoTeste("randon", 10, 10, 1, 10);
    imprimerCaminho(&dados);
    printf("--------------------------------------------------------------------------------------\n");
    printf("Tempo de execucao: %f ms\n", ((float)(tempoFinal-tempoIncial)) * 1000/(CLOCKS_PER_SEC));
    return 0;*/

    int i, j;
    printf("--------------------------------------------------------------------------------------\n");
    Dados dados;
    bool continuar;
    clock_t tempoIncial = clock();
    
    continuar = leituraDados(&dados);

    if(continuar == false){
        return 0;
    }

    printf("Soma Minima: %d\n", calculaDistanciaMinima(&dados));
    printf("Quantidade de caminhos: %d\n", calculaQuantidadeCaminho(&dados));

    clock_t tempoFinal = clock();
    imprimerCaminho(&dados);
    printf("\n");
    printf("Soma Minima: %d\n", calculaDistanciaMinimaParada(&dados, 1, 1));
    printf("Quantidade de caminhos: %d\n", calculaQuantidadeCaminhoParada(&dados, 1, 1));
    imprimerCaminhoParada(&dados, 1, 1);

    srand(time(NULL));
    bool a = gerarCasoTeste("randon", 10, 10, 1, 10);
    printf("--------------------------------------------------------------------------------------\n");
    printf("Tempo de execucao: %f ms\n", ((float)(tempoFinal-tempoIncial)) * 1000/(CLOCKS_PER_SEC));
    return 0;
}