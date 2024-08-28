#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// STRUCTS E ALOCAÇÃO DE MEMÓRIA //
typedef struct{
    char nomePrtd[50];
    char siglaPrtd[10];
    char federacao;
    // Ponteiro para vetor de candidato
}partidos; 



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


int verificaExistenciaPartido(partidos*P, int *tam, char* nome){
    /* A função verifica se o partido digitado pelo usuário existe. A mesma foi criada
    com a intencao de verificar se o partido existe, a fim de não registrar outro com o
    mesmo nome. O mesmo acontece para fazer parte da federacao, visto que o partido só pode
    participar de uma federaçao.
    Ela retorna 1 caso o partido exista, caso contrário, retorna 0*/

    int i;
    for(i=0; i<*tam; i++){
        if(strcmp(P[i].nomePrtd, nome) == 0){
            return 1; //Partido encontrato
        } 
    }
    return 0; // Partido não encontrato
}

void cadastrarPartido(int pos, partidos*P, int *tam){

    printf("Digite o nome do partido: ");
    scanf("%s", P[pos].nomePrtd);
    printf("Digite a sigla do partido: ");
    scanf("%s", P[pos].siglaPrtd);
    
    if(!verificaExistenciaPartido(P,tam,P[pos].nomePrtd)){
        printf("Partido inserido\n");
        //(*tam++);
    }else{
        printf("Este Partido já existe");
    }
}

int alocaVetPartidos(int tam){
    /*Função que realiza a alocação de memória para o ponteiro dos partidos.
    Será exibida uma mensagem de erro, caso a alocação seja mal sucedida e retorna 
    o ponteiro *vetPartido*/
    int *vetPartido = NULL;
    vetPartido = (int*)malloc(tam* sizeof(int));

    if (vetPartido == NULL){
        printf("Erro: alocação mal sucedida");
        exit(1);
    }
    return *vetPartido;
}

void menu(){
    // Criar contadores para cada opção!! 
    int continuar = 1;
    int contador = 0;
    int op;
    int pos;
    partidos* P = NULL;
    // candidato* C = NULL;
    // federacao* F = NULL;

    printf("\n");
    printf("___________________________________\n");
    printf("|                                 |\n");
    printf("|     Eleições Escola Crescer     |\n");
    printf("|_________________________________|\n\n");
    printf("Pressione enter para iniciar...\n");
    getchar();

    do{
        printf("_________________________________\n");
        printf("|                               |\n");
        printf("|       Menu de Cadastros:      |\n");
        printf("|     1 - Cadastrar Partidos    |\n");
        printf("|     2 - Cadastrar Candidatos  |\n");
        printf("|     3 - Cadastrar Federações  |\n");
        printf("|     4 - Iniciar Votação       |\n");
        printf("|     5 - Sair                  |\n");
        printf("|_______________________________|\n");
        printf("Digite uma opção => \n");

        
        op = obterInteiro();

        // Inicia a etapa de cadastros

        if(op == 1){
            pos = contador;
            // Cadastrando partidos
                printf("___________________________________\n");
                printf("|                                 |\n");
                printf("|       Cadastro de Partidos      |\n");
                printf("|_________________________________|\n\n");
                printf("\n");

            while (continuar){
                printf("Cadastrando o %dº partido...\n", contador + 1);
                contador++;
                cadastrarPartido(pos, P, &contador);
                printf("Deseja inserir outro partido? (1 - Sim / 0 - Não): \n");
                continuar = obterInteiro();
            }
        }

        else if(op == 2){
            //Cadastrando Candidatos
            continuar   = 1;
            contador    = 0;

            printf("___________________________________\n");
            printf("|                                 |\n");
            printf("|      Cadastro de Candidatos     |\n");
            printf("|_________________________________|\n");
            printf("\n");

            while (continuar){
                printf("Cadastrando o %dº candidato\n", contador + 1);
                contador++;
                //cadastrarCandidato();
                printf("Deseja cadastrar outro candidato? (1 - Sim / 0 - Não): \n");
                continuar = obterInteiro();
            }
        }

        else if(op == 3){
            //Cadastrando Federações

            continuar = 1;
            contador = 0;

            printf("___________________________________\n");
            printf("|                                 |\n");
            printf("|      Cadastro de Federações     |\n");
            printf("|_________________________________|\n\n");
            printf("\n");

            while (continuar){
                printf("Cadastrando a %dª federação\n", contador +1);
                contador++;
                //registrarFederacao();
                printf("Deseja cadastrar outro candidato? (1 - Sim / 0 - Não): \n");
                continuar = obterInteiro();
            }
        }


        else if(op == 4){
            //Inicia processo de votação
            continuar = 1;
            printf("Ok!\n");

            // while (continuar){
                
            //     // Inicio Menu de Votação 
            //     // printf("=================================\n");
            //     // printf("=        Menu de Votação        =\n");
            //     // printf("=       1) Registrar Voto       =\n");
            //     // printf("=       2) Encerrar Votação     =\n");
            //     // printf("=================================\n");    
            //     // printf("\n");

            //     op = obterInteiro();

            //     // FAZER MENU DE CONFIRMAÇÃO DE VOTO, RETORNAR E VOTO EM BRANCO

            //     if (op == 1){
            //         /*
            //             Registrar numeração num vetor de tamanho n, depois esse n vai ser parametro para a função verifica candidato 
            //         */

            //        //chamafuncao()



            //         // printf("Digite o numero do candidato (5 Digitos): \n");
            //         // voto = obterInteiro();
            //         // if (){
            //         //     // comparar com numero dos candidatos existentes
            //         // }
            //         // else if ()
            //     }
            //     else if (op == 2){
            //         return 0;
            //     }
            //     */

            // }
        }
        }while(op != 5);
}

int main(){

    menu();

    return 0;
}