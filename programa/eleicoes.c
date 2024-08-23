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
    scanf("%d", C[pos].idade);
    printf("Numero de eleitor: ");
    scanf("%d", C[pos].num_canditados);
}


int main() {

    

    return 0;
}