#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// STRUCTS E ALOCAÇÃO DE MEMÓRIA //
typedef struct{
    char nomePrtd[50];
    char siglaPrtd[10];
}partidos;


int alocaVetPartidos(int tam){
    /*Função que realiza a alocação de memória para o ponteiro dos partidos.
    Será exibida uma mensagem de erro, caso a alocação seja mal sucedida e retorna 
    o ponteiro *vetPartido*/
    int *vetPartido = NULL;
    vetPartido = (int*)maloc(tam*sizeof(int));

    if (vetPartido == NULL){
        printf("Erro: alocação mal sucedida");
        exit(1);

    }
    return *vetPartido;
}

typedef struct{
    char nomeCandidato[50];
    int idade;
    int num_canditados;
    partidos filiacao;
}candidato;

int alocaVetCandidatos(int tam){
    /*Função que realiza a alocação de memória para o ponteiro dos candidatos.
    Será exibida uma mensagem de erro, caso a alocação seja mal sucedida e retorna 
    o ponteiro *vetCandidato*/
    int *vetCandidato = NULL;
    vetCandidato = (int*)maloc(tam*sizeof(int));

    if (vetCandidato == NULL){
        printf("Erro: alocação mal sucedida");
        exit(1);

    }
    return *vetCandidato;
}

typedef struct{
    char nomeFederacao[50];
    char siglaFederacao[10];
}federacao;

int alocaVetFederacao(int tam){
    /*Função que realiza a alocação de memória para o ponteiro dos federacoes.
    Será exibida uma mensagem de erro, caso a alocação seja mal sucedida e retorna 
    o ponteiro *vetFederacao*/
    int *vetFederacao = NULL;
    vetFederacao = (int*)maloc(tam*sizeof(int));

    if (vetFederacao == NULL){
        printf("Erro: alocação mal sucedida");
        exit(1);

    }
    return *vetFederacao;
}
// ------------------------------------------------------------------------------------------------------//

// CADASTROS / REGISTROS //
void inserirPartido(partidos*P, int pos){
    printf("Digite o nome do partido: ");
    scanf("%s", P[pos].nomePrtd);
    printf("Digite a sigla do partido: ");
    scanf("%s", P[pos].siglaPrtd);
}

void cadastrarCandidato(candidato*C, int pos){
    printf("Pardido Filiado: ");
    scanf("%s", C[pos].filiacao.nomePrtd);
    printf("Nome Completo: ");
    scanf("%s", C[pos].nomeCandidato);
    printf("Idade: ");
    scanf("%d", &(C[pos].idade));
    printf("Numero de eleitor: ");
    scanf("%d", &(C[pos].num_canditados));
}

void registrarFederacao(federacao*F, int pos){
    printf("Digite o nome da Federacao: ");
    scanf("%s", F[pos].nomeFederacao);
    printf("Digite a sigla da Federacao: ");
    scanf("%s", F[pos].siglaFederacao);

}

int verificaExistenciaPartido(partidos*P, int tam, char nome){
    /* A função verifica se o partido digitado pelo usuário existe. A mesma foi criada
    com a intencao de verificar se o partido existe, a fim de não registrar outro com o
    mesmo nome. O mesmo acontece para fazer parte da federacao, visto que o partido só pode
    participar de uma federaçao.
    Ela retorna 1 caso o partido exista, caso contrário, retorna 0*/

    int i;
    for(i=0; i<tam; i++){
        if(strcmp(P[i].nomePrtd, nome) == 0){
            return 1; //Partido encontrato
        } 
    }
    return 0; // Partido não encontrato
}

void participarDaFederacao(federacao*f, partidos*P, char nome){
    
    
}

void registraVoto(candidato*C, int numero, int tam){
    int i;
    printf("Digite o número do candidato (5 digitos): ");
    for(i=0; i<tam; i++){
        if (C[i].num_canditados == numero){
            printf("%s", C[i].nomeCandidato);
        } else{
            printf("VOTO NULO");
        }
    }

}


int main() {

    

    return 0;
}