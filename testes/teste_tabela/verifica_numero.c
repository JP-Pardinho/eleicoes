#include <stdio.h>
#include <string.h>

int main(){
    char numCandidato[5];
    int tam;
    int verifica;

    printf("Numero candidato: \n");
    do{
        verifica = 0;
        scanf("%s", numCandidato);
        tam = strlen(numCandidato);
        if(tam == 5){
            for(int i=0; i<5; i++){
                if(numCandidato[i] >= '0' && numCandidato[i] <= '9'){
                    verifica += 1;
                }
            }
            
            if(verifica == 5){
                printf("Voto Válido\n");
                printf("Nome do desgraçado\n");
                printf("%s\n", numCandidato);
                printf("\n");
                // chamar/criar o menuConfirmação() (função para registrar os votos validos, nulos e brancos)
            } else{
                printf("Numero do Candidato invalido, digite apenas numeros!\n");

                // chamar/criar o menuConfirmação() (função para registrar os votos validos, nulos e brancos) 
            }
        }
        else{
            printf("VOTO NULO!\n");
        }

    }while(verifica != 5);
    return 0;
}