#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// STRUCTS E ALOCAÇÃO DE MEMÓRIA //
typedef struct{
    char nomePrtd[50];
    char siglaPrtd[10];
    // Ponteiro para vetor de candidato
}partidos; 


partidos* alocaVetPartidos(int tam){
    /*Função que realiza a alocação de memória para o ponteiro dos partidos.
    Será exibida uma mensagem de erro, caso a alocação seja mal sucedida e retorna 
    o ponteiro *vetPartido*/
    partidos *vetPartido = (partidos*)malloc(tam* sizeof(partidos));
    if (vetPartido == NULL){
        printf("Erro: alocação mal sucedida!");
        exit(1);
    }
    return vetPartido;
}

typedef struct{
    char nomeCandidato[50];
    int idade;
    char num_canditados[5];
    int voto;
    partidos* filiacao; 
}candidato;


candidato* alocaVetCandidatos(int tam){
    /*Função que realiza a alocação de memória para o ponteiro dos candidatos.
    Será exibida uma mensagem de erro, caso a alocação seja mal sucedida e retorna 
    o ponteiro *vetCandidato*/
    candidato *vetCandidato = (candidato*)malloc(tam*sizeof(candidato));
    if (vetCandidato == NULL){
        printf("Erro: alocação mal sucedida!");
        exit(1);

    }
    return vetCandidato;
}

typedef struct{
    char nomeFederacao[50];
    char siglaFederacao[10];
    // Ponteiro para vetor de candidato 
}federacao;


federacao* alocaVetFederacao(int tam){
    /*Função que realiza a alocação de memória para o ponteiro dos federacoes.
    Será exibida uma mensagem de erro, caso a alocação seja mal sucedida e retorna 
    o ponteiro *vetFederacao*/
    federacao *vetFederacao = (federacao*)malloc(tam*sizeof(federacao));
    if (vetFederacao == NULL){
        printf("Erro: alocação mal sucedida!");
        exit(1);

    }
    return vetFederacao;
}


int verificaExistenciaPartido(partidos*P, int tam, char* nome){
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
int verificaSiglaPrtd(partidos*P, int tam, char* nome){
    int i;
    for(i=0; i<tam; i++){
        if(strcmp(P[i].siglaPrtd, nome) == 0){
            return 1; //Sigla encontrada
        }
    }
    return 0; //Sigla não encontrada
}

int letras(char *soLetra){
    /*Função é utilizada para verificar a entrada do usuário é apenas letra.
    É utilizado na função cadastrarPartidos, ....., para que não haja número no nome e na sigla.
    A função retorna zero, se não tem apenas letra, caso contrário retorna 1*/
    int i;
    for(i=0; soLetra[i] != '\0'; i++){
        if(!isalpha((unsigned char)soLetra[i])){
            return 0; //erro
        }
    }
    return 1; // só letra
}


int verificaNumeroCandidato(char* numCandidato){
    int i;
    int tam = strlen(numCandidato);
    int ch;

    if(tam != 5){
        return 0; // Tem menos ou mais que 5 dígitos
    }
    for(i = 0; i < 5; i++){
        if(!isdigit((unsigned char)numCandidato[i])){
            return 0; // Não são apenas números 
        }
    }
    while ((ch = getchar()) != '\n' && ch != EOF);
    return 1; //pode
}

int verificaNomeCandidato(candidato*C, int tam, char* nomeC){
    int i;
    for(i=0; i<tam; i++){
        if(strcmp(C[i].nomeCandidato, nomeC) == 0){
            return 1; //Candidato encontrado
        }
    }
    return 0; //Candidado não encontrado
}

int numCandidatoExiste (candidato*C, char *numCandidato, int tam){
    int i;
    for(i=0; i<tam; i++){
        if(strcmp(C[i].num_canditados, numCandidato) == 0){
            return 1; // Numero de condidato existe 
        }
    }
    return 0; // Numero de candidato não existe
}
int obterInteiro(){
    int valor;
    int resultado;
    char ch;

    while(1){
        resultado = scanf("%d", &valor);
        
        if (resultado == 1){
            while((ch = getchar()) != '\n' && ch != EOF);
            return valor;
        }
        else{
            while (getchar() != '\n');
            printf("Entrada inválida. Por favor, Digite um número inteiro: ");
        }
    }
}

void cadastrarPartido(partidos*P, int *contador){
    char nome[50];
    char sigla[10];
    int existePartido, existeSigla;
    

    printf("Digite o nome do partido: ");
    scanf("%s", nome);
    printf("Digite a sigla do partido: ");
    scanf("%s", sigla);
    printf("\n");

    if(!letras(nome)){
        printf("O nome do partido deve conter apenas letras!\n");
        return;
    }
    if (!letras(sigla)){
        printf("A sigla deve conter apenas letras!\n");
        return;
    }

    existePartido = verificaExistenciaPartido(P, *contador, nome);
    existeSigla = verificaSiglaPrtd(P,*contador, sigla);

    if(!existePartido && !existeSigla){
        strcpy(P[*contador].nomePrtd, nome);
        strcpy(P[*contador].siglaPrtd, sigla);
        printf("Partido e sigla inserido!\n");
        (*contador)++; //Incrementa o contador direto na main
    } else{
        if(existePartido){
            printf("Este partido já existe!\n");
        }
        if(existeSigla){
            printf("Esta sigla já existe!\n");
        }
    }
}

void cadastrarCandidato(candidato*C, partidos*P, int *contador, int numPartidos){
    char nomeCandidato[50];
    char numCandidato[6];
    char partido[50];
    int idadeCandidato;
    int existePartido, existeNome, existeNumCandidato;
    partidos *partidoFiliado = NULL;
    /*Verificar se o candidato já existe(nome composto(fgets)), se o numero já exite, se o partido que 
    ele quer participar existe*/
    
    printf("Partido Filiado: ");
    fgets(partido, sizeof(partido), stdin);
    partido[strcspn(partido, "\n")] = '\0'; //Remove caracter de Nova linha

    printf("Nome Completo: ");
    fgets(nomeCandidato, sizeof(nomeCandidato), stdin);
    nomeCandidato[strcspn(nomeCandidato, "\n")] = '\0'; //Remove caracter de Nova linha
    
    printf("Idade:");
    idadeCandidato = obterInteiro();

    printf("Numero de eleitor (5 dígitos):");
    fgets(numCandidato, sizeof(numCandidato), stdin);
    numCandidato[strcspn(numCandidato, "\n")] = '\0';

    if(!letras(partido)){
        printf("O nome do partido deve conter apenas letras!\n");
        return;
    }
    if(!letras(nomeCandidato)){
        printf("O nome do candidato deve conter apenas letras!\n");
        return;
    }
    if(!verificaNumeroCandidato(numCandidato)){
        printf("Número do candidato inválido! Faça novamente o cadastro...\n");
        return;
    }

    existePartido = verificaExistenciaPartido(P,*contador,partido);
    existeNome = verificaNomeCandidato(C, *contador, nomeCandidato);
    existeNumCandidato = numCandidatoExiste(C, numCandidato, *contador);

    if(existePartido && !existeNome && !existeNumCandidato){
        for(int i = 0; i<numPartidos; i++){
            if(strcmp(P[i].nomePrtd, partido) == 0){
                partidoFiliado = &P[i];
                break;
            }
        }
        if(partidoFiliado != NULL){
            strcpy(C[*contador].nomeCandidato, nomeCandidato);
            C[*contador].idade = idadeCandidato;
            strcpy(C[*contador].num_canditados, numCandidato);
            (*contador)++;
        }
    } else{
        if(!existePartido){
            printf("ERRO: Este partido não está cadastrado!\n");
        }
        if(existeNome){
            printf("ERRO: Este nome já está cadastrado!\n");
        }
        if(existeNumCandidato){
            printf("ERRO: Este número pertence a outro candidato!\n");
        }
    }
}

void registrarFederacao(federacao*F, int pos){
    printf("Digite o nome da Federacao: ");
    scanf("%s", F[pos].nomeFederacao);
    printf("Digite a sigla da Federacao: ");
    scanf("%s", F[pos].siglaFederacao);
}


int verificaExisFederacao(federacao*F, int tam, char* nome){
    /*A função verifica se a federação que o usuário deseja inserir já existe. Caso a federação 
    exista a função retorna 1, caso contrário retorna 0. Quando é a função retorna zero é possível
    registrar a federação.*/
    int i;
    for(i=0; i<tam; i++){
        if(strcmp(F[i].nomeFederacao, nome) == 0){
            return 1; //Federacao encontrada
        }
    }
    return 0; //Federacao não encontrada
}

void iniciarVotacao(candidato* C, int* numCandidatos, int* votosNulos, int* votosBranco, int* votosValidos) {
    /* FAZER  O DOCSTRING */
    int continuar = 1;
    int opcao, votoConfirmado = 0;
    char numCandidato[6]; // 5 dígitos + '\0'
    candidato* candidatoEscolhido = NULL;

    while (continuar) {
        printf("____________________________________\n");
        printf("|                                  |\n");
        printf("|          Menu de Votação         |\n");
        printf("|                                  |\n");
        printf("|        1) Registrar Voto         |\n");
        printf("|        2) Encerrar Votação       |\n");
        printf("|__________________________________|\n");
        printf("Digite uma opção: ");

        opcao = obterInteiro();

        if (opcao == 1) {  // Registrar voto
            printf("Digite o número do candidato (5 dígitos): ");
            scanf("%s", numCandidato);
            candidatoEscolhido = NULL;

            for (int i = 0; i < *numCandidatos; i++) {
                if (strcmp(C[i].num_canditados, numCandidato) == 0) {
                    candidatoEscolhido = &C[i];
                    break;
                }
            }

            if (candidatoEscolhido) {
                printf("Candidato: %s\n", candidatoEscolhido->nomeCandidato);
            } else {
                printf("VOTO NULO\n");
            }

            // Menu de confirmação
            printf("____________________________________\n");
            printf("|                                  |\n");
            printf("|       1) Confirmar Voto          |\n");
            printf("|       2) Retornar                |\n");
            printf("|       3) Votar em Branco         |\n");
            printf("|__________________________________|\n");
            printf("Digite uma opção: ");
            votoConfirmado = obterInteiro();

            if (votoConfirmado == 1) {  // Confirmar voto
                if (candidatoEscolhido) {
                    candidatoEscolhido->voto++;
                    (*votosValidos)++;
                    printf("Voto registrado para %s\n", candidatoEscolhido->nomeCandidato);
                } else {
                    (*votosNulos)++;
                    printf("Voto Nulo registrado.\n");
                }
            } else if (votoConfirmado == 3) {  // Votar em branco
                (*votosBranco)++;
                printf("Voto em Branco registrado.\n");
            }
            // Retornar não faz nada, apenas volta ao menu de votação
        } else if (opcao == 2) {  // Encerrar votação
            continuar = 0;
            printf("Votação encerrada.\n");
        } else {
            printf("Opção inválida. Por favor, escolha novamente.\n");
        }
    }
}



// Tentar simplificar ou unir as duas verificações
/*void imprimeNomeCandidato (candidato*C, int tam, char* nomeCandidato){
    int i;
    for(i=0; i<tam; i++){
        if(verificaCandidato(C,numero, tam)){
            printf("%s\n", C[i].nomeCandidato);
        }
    }
    printf("Número de candidato não existe!\n");
}*/

/*
void secao1(int votos, int votosValido, int votosNulo, int votosBranco, int q_eleitoral){
    Função responsavél por mostrar na tela os votos gerais, valídos, brancos, nulos e o quociente eleitoral. 

    // ADICIONAR AS VARIAVÉIS DE CADA ELEMENTO

    printf("Votos gerais: %d\n", votos);
    printf("Votos valídos: %d\n", votosValido);
    printf("Votos brancos: %d\n", votosNulo);
    printf("Votos nulos: %d\n", votosBranco);
    printf("Quocinte eleitoral: %d\n", q_eleitoral);
}

void secao2(nomeCandidato){
    Função responsavél por mostrar na tela uma tabela com todos os candidatos e o numero de votos que cada um teve. 
    printf("===================================");
    // for()
        printf("=Candidato: %c Votos recebidos: %d=", nomeCandidato);
    printf("===================================");
}

void secao3(int votoPartido, int votoFederação){
    Função responsavél por mostrar na tela o número total de votos que cada partido/federação obteve. 

    // for()
        printf("Total de votos: %d");
}

void secao4(q_partidario){
    Função responsavél por mostrar na tela uma tabela informando o quociente partidário de cada partido ou federação e o número de cadeiras ao qual ele tem direito. 

}

void secao5(){
    Função responsavél por mostrar na tela uma tabela com os nomes dos candidatos eleitos e sua legenda. 

}

void secao6(){
    Função responsavél por mostrar na tela uma tabela com os candidatos suplentes, em ordem decrescente de quociente eleitoral. 
}
*/

void menu(){
    // Criar contadores para cada opção!! 
    int continuar = 1;
    int contadorPartidos = 0;
    int op;
    int votosValidos = 0, votosNulos = 0, votosBranco = 0;
    //Partidos//
    partidos* P = NULL;
    int tamPartidos = 10;
    P = alocaVetPartidos(tamPartidos);
    //Candidatos//
    candidato* C = NULL;
    int contadorCandidatos = 0;
    int tamCandidatos = 10;
    C = alocaVetCandidatos(tamCandidatos);
    //Federação//
    federacao* F = NULL;
    int contadorFederacao = 0;
    int tamFederacao = 10;
    F = alocaVetFederacao(tamFederacao);

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
        printf("Digite uma opção => ");

        op = obterInteiro();

        // Inicia a etapa de cadastros

        if(op == 1){
            // Cadastrando partidos
            printf("___________________________________\n");
            printf("|                                 |\n");
            printf("|       Cadastro de Partidos      |\n");
            printf("|_________________________________|\n\n");
            printf("\n");

            continuar = 1;

            while (continuar){
                if(contadorPartidos >= tamPartidos){
                    tamPartidos *= 2;
                    P = realloc(P, tamPartidos* sizeof(partidos));
                    if(P ==NULL){
                        printf("ERRO: realocação mal sucedida!\n");
                        exit(1);
                    }
                }
                printf("Cadastrando o %dº partido!\n", contadorPartidos + 1);
                cadastrarPartido(P, &contadorPartidos);
                printf("Deseja inserir outro partido? (1 - Sim / 0 - Não): \n");
                continuar = obterInteiro();
            }
        }

        else if(op == 2){
            //Cadastrando Candidatos
            printf("___________________________________\n");
            printf("|                                 |\n");
            printf("|      Cadastro de Candidatos     |\n");
            printf("|_________________________________|\n");
            printf("\n");

            continuar   = 1;

            while (continuar){
                if(contadorCandidatos >= tamCandidatos){
                    tamCandidatos *= 2;
                    C = realloc(C, tamCandidatos* sizeof(candidato));
                    if(C == NULL){
                        printf("ERRO: Alocação mal sucedida!\n");
                        exit(1);
                    }
                }
                printf("Cadastrando o %dº candidato\n", contadorCandidatos + 1);
                contadorCandidatos++;
                cadastrarCandidato(C, P, &contadorCandidatos, contadorPartidos);
                printf("Deseja cadastrar outro candidato? (1 - Sim / 0 - Não): \n");
                continuar = obterInteiro();
            }
        }

        else if(op == 3){
            //Cadastrando Federações
            printf("___________________________________\n");
            printf("|                                 |\n");
            printf("|      Cadastro de Federações     |\n");
            printf("|_________________________________|\n\n");
            printf("\n");

            continuar = 1;

            while (continuar){
                if(contadorFederacao >= tamFederacao){
                    tamFederacao *= 2;
                    F = realloc(F,tamFederacao* sizeof(federacao));
                    if(F == NULL){
                        printf("Alocação mal sucedida!\n");
                        exit(1);
                    }
                }
                printf("Cadastrando a %dª federação!\n", contadorFederacao +1);
                contadorFederacao++;
                //registrarFederacao();
                printf("Deseja cadastrar outro candidato? (1 - Sim / 0 - Não): \n");
                continuar = obterInteiro();
            }
        }


        else if(op == 4){
            //Inicia processo de votação

            printf("\n");
            printf("____________________________________\n");
            printf("|                                  |\n");
            printf("|       Iniciando Votação...       |\n");
            printf("|__________________________________|\n\n");
            printf("\n");

            iniciarVotacao(C, &contadorCandidatos, &votosValidos, &votosBranco, &votosNulos);
        }
    }while(op != 5);
        printf("Finalizando...");
    free(P); // Limpa a memória
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
//XEBIU