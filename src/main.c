#include "galaxia.h"

int main(){
    int i, j;
    Dados dados;
    bool status;
    int escolha, linha, coluna, numeroMinimo, numeroMaximo;
    char nomeArquivo[50];
    char nomeArquivoGerarTeste[50];
    clock_t tempoIncial = clock();

    printf("Digite o nome do arquivo que deve ser lido: ");
    scanf("%s", &nomeArquivo);
    
    status = leituraDados(&dados, nomeArquivo);

    if(status == false){
        return 0;
    }
    printf("\n");
    printf("Soma Minima: %d\n", calculaDistanciaMinima(&dados));
    printf("Quantidade de caminhos: %d\n", calculaQuantidadeCaminho(&dados));
    imprimerCaminho(&dados);
    printf("--------------------------------------------------------------------------------------\n");

    do{
        printf("Deseja adicionar parada no caminho[0-NAO/1-SIM]: ");
        scanf("%d", &escolha);
    } while (escolha < 0 || escolha > 1);
    if(escolha == 1){
        printf("         POSSICOES       \n");
        //printf("%d %d\n", dados.N, dados.M);
        for(i = 0; i < dados.N; i++){
            for(j = 0; j < dados.M; j++){
                printf("%-3d ", dados.grid[i][j]);
            }
            printf("\n");
        }
        printf("\n");
        printf("Digite o numero da linha de parada: ");
        scanf("%d", &linha);
        printf("Digite o numero da coluna de parada: ");
        scanf("%d", &coluna);
        printf("Soma Minima: %d\n", calculaDistanciaMinimaParada(&dados, linha, coluna));
        printf("Quantidade de caminhos: %d\n", calculaQuantidadeCaminhoParada(&dados, linha, coluna));
        imprimerCaminhoParada(&dados, linha, coluna);
    }
    printf("\n");
    srand(time(NULL));
    do{
        printf("Deseja gerar um caso de teste aleatorio[0-NAO/1-SIM]: ");
        scanf("%d", &escolha);
    } while (escolha < 0 || escolha > 1);
    if(escolha == 1){
        printf("Digite o nome que sera usado no arquivo de teste: ");
        scanf("%s", &nomeArquivoGerarTeste);
        printf("Digite o numero de linhas: ");
        scanf("%d", &linha);
        printf("Digite o numero de colunas: ");
        scanf("%d", &coluna);
        printf("Digite o numero minimo: ");
        scanf("%d", &numeroMinimo);
        printf("Digite o numero maximo: ");
        scanf("%d", &numeroMaximo);
        status = gerarCasoTeste(nomeArquivoGerarTeste, linha, coluna, numeroMinimo, numeroMaximo);
    }

    clock_t tempoFinal = clock();
    printf("Tempo de execucao: %f ms\n", ((float)(tempoFinal-tempoIncial)) * 1000/(CLOCKS_PER_SEC));
    return 0;
}