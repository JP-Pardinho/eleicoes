#include <stdio.h>
#include <string.h>

int main(){
    char numCandidato[5];
    int verifica;
    int tam;

    printf("Numero candidato: \n");

    do{
        scanf("%s", numCandidato);
        if(tam == 5){
            for(int i=0; i<5; i++){
                if(numCandidato[i] >= '0' && numCandidato[i] <= '9'){
                    verifica += 1;
                }
            }
            
            if(verificaCandidato()){
                printf("Voto Válido\n");
                printf("Nome do desgraçado\n");
                printf("%s\n", numCandidato);
                printf("\n");
                // chamar/criar o menuConfirmação() (função para registrar os votos validos, nulos e brancos)
            } else{
                printf("VOTO NULO!\n");
                // chamar/criar o menuConfirmação() (função para registrar os votos validos, nulos e brancos) 
            }
        }
        else{
            printf("VOTO NULO!\n");
            printf("Digite um numero")
        }

    }while(tam != 5);
    return 0;
}