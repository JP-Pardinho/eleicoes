#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int obterInteiro(){
    int valor;
    int resultado;

    while(1){
        resultado = scanf("%d", &valor);
        
        if (resultado == 1){
            return valor;
        }
        else{
            while (getchar() != '\n');
            printf("Entrada inválida. Por favor, Digite um número inteiro: ");
        }
    }
}

int main(){

    int continuar = 1;
    printf("===============================\n");
    printf("=   Eleições Escola Crescer   =\n");
    printf("===============================\n\n");
    printf("Precione enter para iniciar...\n");

    getchar();

    // Inicia a etapa de cadastros
    
    printf("==============================\n");
    printf("=    Cadastro de Partidos    =\n");
    printf("==============================\n\n");
    printf("Precione enter para iniciar... \n");
    getchar();

    while (continuar){
        // inserirPartido();
        printf("Deseja inserir outro partido? (1 - Sim / 0 - Não): \n");
        continuar = obterInteiro();
    } 

    return 0;
}