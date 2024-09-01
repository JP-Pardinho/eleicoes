#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// STRUCTS E ALOCAÇÃO DE MEMÓRIA //
typedef struct{
    char nomePrtd[50];
    char siglaPrtd[10];
    char siglaFederacao[10];
    int voto;
    // Ponteiro para vetor de candidato
}partidos; 

//Partido em Outra Federacao//
int partidoEmOutraFederacao(partidos* P, int numFederacoes, char* siglaPartido){
    int i;
    for(i = 0; i < numFederacoes; i++){
        if(strcmp(P[i].siglaPrtd, siglaPartido) == 0){
            if(P[i].siglaFederacao[0] != '\0'){
                return 1; //Tá em outra federação
            }
            break;
        }
    }
    return 0; //Não está em outra federação
}


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
    int voto;
    int numPartido;
    partidos* partidosNaFederacao;
    
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
    for(i=0; i<(tam + 1); i++){
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
    for (i = 0; soLetra[i] != '\0'; i++) {
        if (!(isalpha((unsigned char)soLetra[i]) || (soLetra[i] & 0x80) || soLetra[i] == ' ')) {
            // isalpha verifica letras padrão; (soLetra[i] & 0x80) verifica se é um caractere com acento
            return 0; // erro
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
void normalizaString(char *str) {
    for (int i = 0; str[i]; i++) {
        str[i] = tolower(str[i]);
    }
}

void cadastrarPartido(partidos*P, int *contador){
    char nome[50];
    char sigla[10];
    int existePartido, existeSigla;
    

    printf("Digite o nome do partido: ");
    fgets(nome, sizeof(nome), stdin);
    nome[strcspn(nome, "\n")] = '\0';
    printf("Digite a sigla do partido: ");
    fgets(sigla, sizeof(sigla), stdin);
    sigla[strcspn(sigla, "\n")] = '\0';
    printf("\n");

    if(!letras(nome)){
        //Dando erro quando põe acentos
        printf("O nome do partido deve conter apenas letras!\n");
        return;
    }
    if (!letras(sigla)){
        //Dando erro quando põe acentos
        printf("A sigla/ deve conter apenas letras!\n");
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
    
    printf("Idade: ");
    idadeCandidato = obterInteiro();

    printf("Numero de eleitor (5 dígitos): ");
    fgets(numCandidato, sizeof(numCandidato), stdin);
    numCandidato[strcspn(numCandidato, "\n")] = '\0';

    if(!letras(partido)){
        printf("O nome do partido deve conter apenas letras!\n");
    }
    if(!letras(nomeCandidato)){
        printf("O nome do candidato deve conter apenas letras!\n");
    }
    if(!verificaNumeroCandidato(numCandidato)){
        printf("Número do candidato inválido! Faça novamente o cadastro...\n");
    }

    existePartido = verificaExistenciaPartido(P,*contador, partido);
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
            C[*contador].voto = 0;
            (*contador)++;
            printf("Candidato Cadastrado com sucesso!\n\n");
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

void registrarFederacao(federacao*F,partidos*P,  int *contadorFederacao, int numPartidos){
    char nomeF[50];
    char siglaF[10];
    char siglaPartidoInserir[50];
    int continuar = 1;
    int numPartidosFederacao = 0;

    if(numPartidos < 2){
        printf("Não é possível cadastrar Federação! Menos de dois partidos cadastrados!\n");
        return;
    }

    
    printf("Digite o nome da Federacao: ");
    fgets(nomeF, sizeof(nomeF), stdin);
    nomeF[strcspn(nomeF, "\n")] = '\0'; // Remove o \n da nova linha;
    
    if(verificaExisFederacao(F, *contadorFederacao, nomeF)){
        printf("ERRO: Existe uma federação com esse nome!\n");
        return;
    }

    printf("Digite a sigla da Federacao: ");
    fgets(siglaF, sizeof(siglaF), stdin);
    siglaF[strcspn(siglaF, "\n")] = '\0'; //Remove o \n da nova linha;

    if(verificaExisFederacao(F, *contadorFederacao, siglaF)){
        printf("ERRO: Existe uma federação com essa sigla!\n");
        return;
    }
    
    F[*contadorFederacao].partidosNaFederacao = alocaVetPartidos(numPartidos);
    F[*contadorFederacao].numPartidos = 0;

    printf("Quais partidos vão fazer parte desta federação: ");
    while(continuar){
        printf("Digite a sigla do partido que você deseja adicionar a federação ('fim' para terminar): ");
        fgets(siglaPartidoInserir, sizeof(siglaPartidoInserir), stdin);
        siglaPartidoInserir[strcspn(siglaPartidoInserir, "\n")] = '\0';
        
        if (strcmp(siglaPartidoInserir, "fim") == 0){
            if(F[*contadorFederacao].numPartidos < 2){
                printf("ERRO: Uma federação deve conter pelo menos 2 partidos!\n");
                return;
            }
            break;
        }

        if(!verificaSiglaPrtd(P, numPartidos, siglaPartidoInserir)){
            printf("ERRO: Sigla não encontrada!\n");
            continue;
        }
        
        if(partidoEmOutraFederacao(P,numPartidos, siglaPartidoInserir)){
            printf("ERRO: Este partido já está em uma federação!\n");
            continue;
        }

        for(int i = 0; i < numPartidos; i++){
            if(strcmp(P[i].siglaPrtd, siglaPartidoInserir) == 0){
                strcpy(P[i].siglaFederacao, siglaF);
                F[*contadorFederacao].numPartidos++;
                break;
            }
        }
    }

    strcpy(F[*contadorFederacao].nomeFederacao, nomeF);
    strcpy(F[*contadorFederacao]. siglaFederacao, siglaF);
    (*contadorFederacao)++;

    printf("Federação cadastrada!\n");
    
}

// Incrementa o voto no partido ou federação correto
void incrementarVoto(partidos* P, int numPartidos, federacao* F, int numFederacao, char* siglaPartido) {
    int idxFederacao = verificaExisFederacao(F, numFederacao, siglaPartido);
    if (idxFederacao != -1) {
        F[idxFederacao].voto++;  // Incrementa o voto na federação
    } else {
        for (int i = 0; i < numPartidos; i++) {
            if (strcmp(P[i].siglaPrtd, siglaPartido) == 0) {
                P[i].voto++;  // Incrementa o voto no partido
                break;
            }
        }
    }
}


void secao1(int* votosValidos, int* votosNulos, int* votosBranco, double* q_eleitoral){
    // Função responsavél por mostrar na tela os votos gerais, valídos, brancos, nulos e o quociente eleitoral. 

    int votos = 0;

    *q_eleitoral += (*q_eleitoral + *votosValidos)/24;

    votos += *votosValidos + *votosNulos + *votosBranco;

    printf("Votos totais: %d\n", votos);
    printf("Votos valídos: %d\n", *votosValidos);
    printf("Votos brancos: %d\n", *votosBranco);
    printf("Votos nulos: %d\n", *votosNulos);
    printf("Quocinte eleitoral: %.2lf\n", *q_eleitoral);
}
void secao2(candidato* C, int numCandidatos) {
    printf("_____________________________________________\n");
    printf("|                                           |\n");
    printf("|            Candidatos e Votos             |\n");
    printf("|___________________________________________|\n");
    

    printf("_____________________________________________\n");
    printf("|                                           |\n");
    printf("| %-28s | %-10s |\n", "Nome do Candidato", "Votos");
    printf("|___________________________________________|\n");

    for (int i = 0; i < numCandidatos; i++) {
        printf("  %-30s | %-10d \n", C[i].nomeCandidato, C[i].voto);
    }
    
    printf("|___________________________________________|\n");
}



void secao3(partidos* P, int numPartidos, federacao* F, int numFederacao){
   // Função responsavél por mostrar na tela o número total de votos que cada partido/federação obteve. 

    printf("_____________________________________________\n");
    printf("|                                           |\n");
    printf("|             Partidos e Votos              |\n");
    printf("_____________________________________________\n");
    printf("|                                           |\n");
    printf("| %-30s | %-10s |\n", "Nome do Partido", "Votos");
    printf("|___________________________________________|\n");

    for (int j = 0; j < numFederacao; j++) {
        if (F[j].voto > 0) {
            printf("| %-30s | %-10d |\n", F[j].nomeFederacao, F[j].voto);
        }
    }

    // Imprime os votos por partido
    for (int k = 0; k < numPartidos; k++) {
        if (P[k].voto > 0) {
            printf("| %-30s | %-10d |\n", P[k].nomePrtd, P[k].voto);
        }
    }
    printf("|___________________________________________|\n");
}

void secao4(partidos* P, int numPartidos, federacao* F, int numFederacao, int votosValidos){
   // Função responsavél por mostrar na tela uma tabela informando o quociente partidário de cada partido ou federação e o número de cadeiras ao qual ele tem direito. 
    double quocienteEleitoral = (double)votosValidos / 24;

    if (quocienteEleitoral == 0) {
        printf("Erro: Quociente eleitoral é zero, não é possível calcular o quociente partidário.\n");
        return;
    }

    printf("_________________________________________________________________\n");
    printf("|                                                               |\n");
    printf("|        Partido/Federacao         | Quociente Part. | Cadeiras |\n");
    printf("|_______________________________________________________________|\n");

    
    for (int i = 0; i < numFederacao; i++) {
        double quocientePartidario = (double)F[i].voto / quocienteEleitoral;
        int numeroCadeiras = (int)quocientePartidario;
        printf("| %-30s | %-16.2lf | %-8d |\n", F[i].nomeFederacao, quocientePartidario, numeroCadeiras);
    }

    for (int j = 0; j < numPartidos; j++) {
        if (P[j].siglaFederacao[0] == '\0') { 
            double quocientePartidario = (double)P[j].voto / quocienteEleitoral;
            int numeroCadeiras = (int)quocientePartidario;
            printf("| %-30s | %-16.2lf | %-8d |\n", P[j].nomePrtd, quocientePartidario, numeroCadeiras);
        }
    }

    printf("_________________________________________________________________\n");
}

void secao5(candidato* C, int numCandidatos, double q_eleitoral){
   // Função responsavél por mostrar na tela uma tabela com os nomes dos candidatos eleitos e sua legenda.
    printf("_____________________________________________\n");
    printf("|                                           |\n");
    printf("|       Candidatos Eleitos e Legenda        |\n");
    printf("|___________________________________________|\n");
    printf("| %-28s | %-10s |\n", "Nome do Candidato", "Legenda");
    printf("|___________________________________________|\n");
    printf("                                             \n");
    for (int i = 0; i < numCandidatos; i++) {
        double quocienteMinimo = 0.1 * q_eleitoral;
        // Verificar se o candidato tem votos > 0
        if (C[i].voto >= quocienteMinimo) {  // Assumindo que todos com votos > 0 são considerados eleitos
            printf("  %-28s | %-10s \n", C[i].nomeCandidato, C[i].filiacao->siglaPrtd);
        }
    }
    printf("_____________________________________________\n");
}


void secao6(candidato* C, int numCandidatos, double q_eleitoral) {
    // Vetor para armazenar suplentes
    candidato* suplentes = malloc(numCandidatos * sizeof(candidato));
    int contadorSuplentes = 0;

    // Encontrar suplentes
    for (int i = 0; i < numCandidatos; i++) {
        double quocienteMinimo = 0.1 * q_eleitoral;

        // Candidatos que têm votos > 0, não foram eleitos, mas pertencem a um partido/federação com vagas
        if (C[i].voto < quocienteMinimo) {
            suplentes[contadorSuplentes++] = C[i];
        }
    }

    // Ordenar suplentes por número de votos e idade (em caso de empate)
    for (int i = 0; i < contadorSuplentes - 1; i++) {
        for (int j = i + 1; j < contadorSuplentes; j++) {
            if (suplentes[j].voto > suplentes[i].voto || 
               (suplentes[j].voto == suplentes[i].voto && suplentes[j].idade > suplentes[i].idade)) {
                candidato temp = suplentes[i];
                suplentes[i] = suplentes[j];
                suplentes[j] = temp;
            }
        }
    }

    // Imprimir os suplentes
    printf("_____________________________________________\n");
    printf("|                                           |\n");
    printf("|       Candidatos Suplentes                |\n");
    printf("|___________________________________________|\n");
    printf("| %-28s | %-16s | %-8s |\n", "Nome do Candidato", "Votos", "Idade");
    printf("|___________________________________________|\n");

    for (int i = 0; i < contadorSuplentes; i++) {
        printf("| %-28s | %-16d | %-8d |\n", suplentes[i].nomeCandidato, suplentes[i].voto, suplentes[i].idade);
    }

    printf("|___________________________________________|\n");

    // Libera memória
    free(suplentes);
}



void iniciarVotacao(candidato* C, int* numCandidatos, int* votosNulos, int* votosBranco, int* votosValidos, double q_eleitoral, partidos* P, int* numPartidos, federacao* F, int* numFederacao) {
    /* FAZER  O DOCSTRING */
    int continuar = 1;
    int opcao, votoConfirmado = 0;
    int escola;
    char numCandidato[6]; // 5 dígitos + '\0'
    candidato* candidatoEscolhido = NULL;

    while (continuar) {

        printf("\n");
        printf("____________________________________\n");
        printf("|                                  |\n");
        printf("|    É aluno da escola crescer?    |\n");
        printf("|        Sim (1) | Não (0)         |\n");
        printf("|__________________________________|\n");
        printf("Escolha uma opção: ");
        escola = obterInteiro();
        printf("\n");
        
        if(escola == 0){
            printf("Você não pode participar dessa votação\n");
        } 
        
        else {
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
                        incrementarVoto(P, *numPartidos, F, *numFederacao, candidatoEscolhido->filiacao->siglaPrtd);
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
                printf("____________________________________\n");
                printf("|                                  |\n");
                printf("|        Votação encerrada...      |\n");
                printf("|__________________________________|\n");
                printf("\n");

                printf("Iniciando seção 1\n");
                printf("Pressione enter para continuar...\n");
                getchar();
                secao1(votosValidos, votosNulos, votosBranco, &q_eleitoral);
                printf("\n");
                printf("Iniciando seção 2\n");
                printf("Pressione enter para continuar...\n");
                getchar();
                secao2(C, *numCandidatos);
                printf("\n");
                printf("Iniciando seção 3\n");
                printf("Pressione enter para continuar...\n");
                getchar();
                secao3(P, *numPartidos, F, *numFederacao);
                printf("Iniciando seção 4\n");
                printf("Pressione enter para continuar...\n");
                getchar();
                secao4(P, *numPartidos, F, *numFederacao, *votosValidos);
                printf("Iniciando seção 5\n");
                printf("Pressione enter para continuar...\n");
                getchar();
                secao5(C, *numCandidatos, q_eleitoral);
                printf("Iniciando seção 6\n");
                printf("Pressione enter para continuar...\n");
                getchar();
                secao6(C, *numCandidatos, q_eleitoral);

            } else {
                printf("Opção inválida. Por favor, escolha novamente.\n");
            }
        }
        // COLOCAR GETCHAR() PARA PRESSIONAR ENTER PARA CONTINUAR
    }

    // Não pode voltar para o menu depois do usuario escolher a opção de numero 2 no menu de votação 
}

void menu(){
    // Criar contadores para cada opção!! 
    int continuar = 1;
    int op;
    int votosValidos = 0, votosNulos = 0, votosBranco = 0;
    double q_eleitoral = 0;
    //Partidos//
    partidos* P = NULL;
    int tamPartidos = 10;
    int contadorPartidos = 0;
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
        printf("|                               |\n");
        printf("|    1 - Cadastrar Partidos     |\n");
        printf("|    2 - Cadastrar Candidatos   |\n");
        printf("|    3 - Cadastrar Federações   |\n");
        printf("|    4 - Iniciar Votação        |\n");
        printf("|    5 - Sair                   |\n");
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
                printf("Deseja inserir outro partido? (1 - Sim / 0 - Não): ");
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
                cadastrarCandidato(C, P, &contadorCandidatos, contadorPartidos);
                // contadorCandidatos++;
                printf("Deseja cadastrar outro candidato? (1 - Sim / 0 - Não): ");
                continuar = obterInteiro();
            }
        }

        else if (op == 3) {
            //Cadastrando Federações
            printf("___________________________________\n");
            printf("|                                 |\n");
            printf("|      Cadastro de Federações     |\n");
            printf("|_________________________________|\n\n");
            printf("\n");

            continuar = 1;

            while (continuar) {
                if(contadorFederacao >= tamFederacao){
                    tamFederacao *= 2;
                    F = realloc(F,tamFederacao* sizeof(federacao));
                    if(F == NULL){
                        printf("Alocação mal sucedida!\n");
                        exit(1);
                    }
                }
                printf("Cadastrando a %dª federação!\n", contadorFederacao +1);
                registrarFederacao(F, P, &contadorFederacao, contadorPartidos);
                printf("\n");
                printf("Deseja cadastrar outra federação? (1 - Sim / 0 - Não): ");
                continuar = obterInteiro();
            }
        }


        else if (op == 4) {
            //Inicia processo de votação
            printf("\n");
            printf("____________________________________\n");
            printf("|                                  |\n");
            printf("|       Iniciando Votação...       |\n");
            printf("|__________________________________|\n");

            iniciarVotacao(C, &contadorCandidatos, &votosValidos, &votosBranco, &votosNulos, q_eleitoral, P, &contadorPartidos, F, &contadorFederacao);
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