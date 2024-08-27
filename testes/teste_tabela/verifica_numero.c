#include <stdio.h>

int main(){
    char numCandidato[5];
    int verifica;
    int tam;

    printf("Numero candidato: \n");

    do{
        scanf("%s", numCandidato);
        for(int i=0; i<5; i++){
            if(numCandidato[i] >= '0' && numCandidato[i] <= '9'){
                verifica += 1;
            }
        }
        if(verifica == 5){
            printf("Voto Válido\n");
            printf("Nome do desgraçado\n");
            printf("%s\n", numCandidato);
        }
        else{
            printf("VOTO NULO!\n");
        }

    }while(tam == 5);
    return 0;
}