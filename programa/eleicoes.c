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
    char num_canditados;
    int voto;
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
    // Ponteiro para vetor de candidato 
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

//-------------------------------------------------------------------------//

// CADASTROS / REGISTROS //
// Criar mais um função para cadastrar partido, verificar(ok), inserir(ok)
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
    printf("Idad    e: ");
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

char verificaNumeracao(){
    
}

void registraVoto(candidato*C, int numero, int tam){
    /*
        Alterar informações no registra voto...
        - Temos que receber um string, verificar se todos os digitos digitados, são numeros inteiros, depois verificar se o numero pertence a um candidato
        - Se o verificaCandidato() retornar que existe, chamar a função menuConfirmação(), para armazenar voto++, em voto_valido, voto_nulo, voto_branco e voto(dentro da struct do candidato)
    */
    int i;
    char numCandidato;

    printf("Digite o número do candidato (5 digitos): ");
    scanf("%s", numCandidato);

    for(i=0; i<tam; i++){
        if (C[i].num_canditados == numCandidato){
            printf("%s", C[i].nomeCandidato);
        } else{
            printf("VOTO NULO");
        }
    }
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

// Mesclar as duas funções verificaCandidato() e imprimeNomeCandidato()
int verificaCandidato (candidato*C, int numero, int tam){
    int i;
    for(i=0; i<tam; i++){
        if(C[i].num_canditados == numero){
            return 1; // Numero de condidato existe 
        }
        return 0; // Numero de candidato não existe
    }
}

// Tentar simplificar ou unir as duas verificações
void imprimeNomeCandidato (candidato*C, int numero, int tam){
    int i;
    for(i=0; i<tam; i++){
        if(C[i].num_canditados == numero){
            printf("%s", C[i].nomeCandidato);
        }
    }
}


void secao1(int votos, int votosValido, int votosNulo, int votosBranco, int q_eleitoral){
    /*Função responsavél por mostrar na tela os votos gerais, valídos, brancos, nulos e o quociente eleitoral. */

    // ADICIONAR AS VARIAVÉIS DE CADA ELEMENTO

    printf("Votos gerais: %d\n", votos);
    printf("Votos valídos: %d\n", votosValidos);
    printf("Votos brancos: %d\n", votosNulo);
    printf("Votos nulos: %d\n", votosBranco);
    printf("Quocinte eleitoral: %d\n", q_eleitoral);
}

void secao2(nomeCandidato){
    /*Função responsavél por mostrar na tela uma tabela com todos os candidatos e o numero de votos que cada um teve. */
    printf("===================================");
    for()
        printf("=Candidato: %c Votos recebidos: %d=", nomeCandidato);
    printf("===================================");
}

void secao3(int votoPartido, int votoFederação){
    /*Função responsavél por mostrar na tela o número total de votos que cada partido/federação obteve. */


    for()
        printf("Total de votos: %d");
}

void secao4(q_partidario){
    /*Função responsavél por mostrar na tela uma tabela informando o quociente partidário de cada partido ou federação e o número de cadeiras ao qual ele tem direito. */

}

void secao5(){
    /*Função responsavél por mostrar na tela uma tabela com os nomes dos candidatos eleitos e sua legenda. */

}

void secao6(){
    /*Função responsavél por mostrar na tela uma tabela com os candidatos suplentes, em ordem decrescente de quociente eleitoral. */
}

void menu(){

    int continuar = 1;
    int contador = 0;
    int op, voto;

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
            // Cadastrando partidos
                printf("___________________________________\n");
                printf("|                                 |\n");
                printf("|       Cadastro de Partidos      |\n");
                printf("|_________________________________|\n\n");
                printf("\n");

            while (continuar){
                printf("Cadastrando o %dº partido\n", contador + 1);
                contador++;
                // inserirPartido();
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
            printf("|_________________________________|\n\n");
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

            while (continuar){

                // Inicio Menu de Votação 
                // printf("=================================\n");
                // printf("=        Menu de Votação        =\n");
                // printf("=       1) Registrar Voto       =\n");
                // printf("=       2) Encerrar Votação     =\n");
                // printf("=================================\n");    
                // printf("\n");

                op = obterInteiro();

                // FAZER MENU DE CONFIRMAÇÃO DE VOTO, RETORNAR E VOTO EM BRANCO

                if (op == 1){
                    /*
                        Registrar numeração num vetor de tamanho n, depois esse n vai ser parametro para a função verifica candidato 
                    */

                   //chamafuncao()



                    // printf("Digite o numero do candidato (5 Digitos): \n");
                    // voto = obterInteiro();
                    // if (){
                    //     // comparar com numero dos candidatos existentes
                    // }
                    // else if ()
                }
                else if (op == 2){
                    return 0;
                }

            }
        }
    }while(op != 5);
}

int main() {

    // Criar variaveis contadoras para Votos Nulos, Votos Validos, Votos em Branco
    menu();




    return 0;
}


/* CASO TENHA TEMPO, TENTAR INCLUIR A EXTENSÃO TIME.H PARA PEGAR A HORA DO COMPUTADOR E MOSTRA A HORA EXATA QUE CADA VOTO FOI COMPUTADO.  
int main() {
    // Variável para armazenar o tempo atual
    time_t tempo_atual;
    // Estrutura para armazenar a data e hora local
    struct tm *hora_local;
    // String para armazenar a hora formatada
    char buffer[80];

    // Obtém o tempo atual em segundos desde 1 de Janeiro de 1970 (Epoch)
    time(&tempo_atual);

    // Converte o tempo para a hora local
    hora_local = localtime(&tempo_atual);

    // Formata a hora em uma string legível
    strftime(buffer, 80, "Hora atual: %H:%M:%S", hora_local);

    // Imprime a hora atual
    printf("%s\n", buffer);

    return 0;
}*/