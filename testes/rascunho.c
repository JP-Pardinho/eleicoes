#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void limpaTela() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}


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
    limpaTela();

    printf("==============================\n");
    printf("=    Cadastro de Partidos    =\n");
    printf("==============================\n\n");


    while (continuar){
        // inserirPartido();
        printf("Deseja inserir outro partido? (1 - Sim / 0 - Não): \n");
        continuar = obterInteiro();
    } 

    limpaTela();
    printf("========================\n");
    printf("=   Menu de Votação    =\n");
    printf("= 1) Registrar Voto    =\n");
    printf("= 2) Encerrar Votação  =\n");
    printf("========================\n");    
    printf("\n");

   

    return 0;
}