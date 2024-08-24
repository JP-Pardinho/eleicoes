#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
    char nomePrtd[50];
    char siglaPrtd[10];
}partidos;

typedef struct{
    char nomeCandidato[50];
    int idade;
    int num_canditados;
    partidos filiacao;
}candidato;

typedef struct{
    char nomeFederacao[50];
    char siglaFederacao[10];
}federacao;

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