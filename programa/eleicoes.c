#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


// STRUCTS E ALOCAÇÃO DE MEMÓRIA
typedef struct{
    char nomePrtd[50];
    char siglaPrtd[10];
    char siglaFederacao[10];
    int voto;
}partidos; 


typedef struct{
    char nomeCandidato[50];
    int idade;
    char num_canditados[5];
    int voto;
    char candidatoEscolhido[50];
    partidos* filiacao; 
}candidato;


typedef struct{
    char nomeFederacao[50];
    char siglaFederacao[10];
    int voto;
    int numPartido;
    partidos* partidosNaFederacao; 
}federacao;


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


void normalizaString(char *str) {
    /*Função responsável por transformar as letras que o usuário 
    passa nas entradas em maiusculas. Ele não retorna nada. */
    for (int i = 0; str[i]; i++) {
        str[i] = tolower(str[i]);
    }
}


int verificaExistenciaPartido(partidos*P, int tam, char* nome){
    /*
        A função verifica se o partido digitado pelo usuário existe, a fim de não registrar outro com o
        mesmo nome. Ela retorna 1 caso o partido exista, caso contrário, retorna 0
    */
    int i;
    char nomeNormal[50];
    strcpy(nomeNormal, nome);
    normalizaString(nomeNormal);

    for(i=0; i<tam; i++){
        normalizaString(P[i].nomePrtd);
        if(strcmp(P[i].nomePrtd, nomeNormal) == 0){
            return 1; //Partido encontrato
        } 
    }
    return 0; // Partido não encontrato
}


int verificaSiglaPrtd(partidos*P, int tam, char* nome){
    /*A função verifica se a sigla do partido digitado pelo usuário existe, a fim de não registrar outro com o
        mesmo nome. Ela retorna 1 caso o partido exista, caso contrário, retorna 0*/
    int i;
    char nomeNormal[10];
    strcpy(nomeNormal, nome);
    normalizaString(nomeNormal);

    for(i=0; i<tam; i++){
        normalizaString(P[i].siglaPrtd);
        if(strcmp(P[i].siglaPrtd, nomeNormal) == 0){
            return 1; //Sigla encontrada
        }
    }
    return 0; //Sigla não encontrada
}


int letras(char *soLetra){
    /*A função é utilizada para verificar a entrada do usuário é apenas letra.
    É utilizado em todas as funções de cadastro, para que não haja número no nome e na sigla.
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
    /*A função verifica se o número do candidato digitado pelo usuário é um string 
    com 5 casas do tipo inteiro, a fim de não registrar numeros que números inválidos*/
    int i;
    int tam = strlen(numCandidato);
    int verifica = 0;   

    if(tam == 5) {
        for (i=0; i<tam; i++) {
            if (numCandidato[i] >= '0' && numCandidato[i] <= '9') {
                verifica++;
            }
        }
        if (verifica == 5) {
            return 1;
        } else {
            printf("O número do candidato deve conter apenas números.\n");
            return 0;
        }
    } else {
        printf("O número do candidato precisa ter 5 dígitos.\n");
        return 0;
    }
    return 0;
}


int verificaNomeCandidato(candidato*C, int tam, char* nomeC){
    /*A função verifica se o nome do candidato digitado pelo usuário existe, 
    a fim de não registrar outro com o mesmo. Ela retorna 1 caso o nome 
    do candidato exista, caso contrário, retorna 0*/
    int i;
    char nomeNormal[50];
    strcpy(nomeNormal, nomeC);
    normalizaString(nomeNormal);

    for(i=0; i<tam; i++){
        normalizaString(C[i].nomeCandidato);
        if(strcmp(C[i].nomeCandidato, nomeNormal) == 0){
            return 1; //Candidato encontrado
        }
    }
    return 0; //Candidato não encontrado
}

int numCandidatoExiste (candidato*C, char *numCandidato, int tam){
    /*A função verifica se o número do candidato digitado pelo usuário
     já foi inserido no cadastro de outro eleitor, a fim de não registar 
     outro candidato com o mesmo numero. Ela retorna 1 caso o número do candida*/
    int i;
    for(i=0; i<tam; i++){
        if(strcmp(C[i].num_canditados, numCandidato) == 0){
            return 1; // Numero de condidato existe 
        }
    }
    return 0; // Numero de candidato não existe
}


int verificaExisFederacao(federacao*F, int tam, char* nome){
    /*A função verifica se a federação que o usuário deseja inserir já existe. Caso a federação 
    exista a função retorna 1, caso contrário retorna 0. Quando a função retorna 0 é possível
    registrar a federação.*/
    int i;
    char nomeNormal[50];
    strcpy(nomeNormal, nome);
    normalizaString(nomeNormal);

    for(i=0; i<tam; i++){
        normalizaString(F[i].nomeFederacao);
        if(strcmp(F[i].nomeFederacao, nomeNormal) == 0){
            return 1; //Federacao encontrada
        } else if (strcmp(F[i].siglaFederacao, nomeNormal) == 0){
            return 1;
        }
    }
    return 0; //Federacao não encontrada
}


//Partido em Outra Federacao//
int partidoEmOutraFederacao(partidos* P, int numFederacoes, char* siglaPartido){
    /*Essa função verifica se o partido que o usuário passou na entrada já faz parte de uma federação. Retorna 1 caso o partido faça parte de uma federação e 0 caso contrário.*/
    int i;
    char nomeNormal[10];
    strcpy(nomeNormal, siglaPartido);
    normalizaString(nomeNormal);

    for(i = 0; i < numFederacoes; i++){
        normalizaString(P[i].siglaPrtd);
        if(strcmp(P[i].siglaPrtd, nomeNormal) == 0){
            if(P[i].siglaFederacao[0] != '\0'){
                return 1; //Tá em outra federação
            }
            break;
        }
    }
    return 0; //Não está em outra federação
}


int obterInteiro() {
    /*Verifica se o que o usuário passou na entra é número. Retorna o valor que o usuário passou, caso contrário retorna mensagem de erro.*/
    int valor;
    char ch;

    while (1) {

        if (scanf("%d", &valor) == 1) {
            // Verificar se sobrou algo no buffer de entrada
            ch = getchar();
            if (ch == '\n') {
                return valor;  // Entrada válida, retorna o número
            } else {
                // Se sobrou algo no buffer, é uma entrada inválida
                
                printf("Por favor, digite apenas números inteiros.\n");
                printf("-> ");
                while (getchar() != '\n');  // Limpar o buffer
            }
        } else {
            // Limpar o buffer se scanf falhar
            printf("Entrada inválida.\n");
            printf("Por favor, digite apenas números inteiros.\n");
            while (getchar() != '\n');  // Limpar o buffer
        }
    }
}


void cadastrarPartido(partidos*P, int *contador){
    /*Função responsável por cadastrar e verificar se todas as entradas do partido estão certas. Não retorna nada.*/
    char nome[50];
    char sigla[10];
    int erro = 0;
    int existePartido, existeSigla;
    printf("Digite o nome do partido: ");
    fgets(nome, sizeof(nome), stdin);
    nome[strcspn(nome, "\n")] = '\0';
    printf("Digite a sigla do partido: ");
    fgets(sigla, sizeof(sigla), stdin);
    sigla[strcspn(sigla, "\n")] = '\0';
    printf("\n");

    if(!letras(nome)){
        printf("O nome do partido deve conter apenas letras!\n");
        erro++;
    }
    if (!letras(sigla)){
        printf("A sigla deve conter apenas letras!\n");
        erro++;
    }
    if (erro >= 1){
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
    /*Função responsável por cadastrar e verificar se todas as entradas do candidato estão certas. Não retorna nada.*/
    char nomeCandidato[50];
    char numCandidato[10];
    char partido[50];
    int idadeCandidato;
    int erro = 0;
    int existePartido, existeNome, existeNumCandidato;
    partidos *filiacao = NULL;
    
    printf("Partido Filiado: ");
    fgets(partido, sizeof(partido), stdin);
    partido[strcspn(partido, "\n")] = '\0'; //Remove caracter de Nova linha
    normalizaString(partido);

    printf("Nome Completo: ");
    fgets(nomeCandidato, sizeof(nomeCandidato), stdin);
    nomeCandidato[strcspn(nomeCandidato, "\n")] = '\0'; //Remove caracter de Nova linha
    normalizaString(nomeCandidato);

    printf("Idade: ");
    idadeCandidato = obterInteiro();

    printf("Numero de eleitor (5 dígitos): ");
    fgets(numCandidato, sizeof(numCandidato), stdin);
    numCandidato[strcspn(numCandidato, "\n")] = '\0';
    

    if(!letras(partido)){
        printf("O nome do partido deve conter apenas letras!\n");
        erro++;
    }
    if(!letras(nomeCandidato)){
        printf("O nome do candidato deve conter apenas letras!\n");
        erro++;
    }
    if(!verificaNumeroCandidato(numCandidato)){
        printf("Número do candidato inválido! Faça novamente o cadastro...\n");
        erro++;
    }
    if(erro >= 1){
        return;
    }

    existePartido = verificaExistenciaPartido(P, numPartidos, partido);
    existeNome = verificaNomeCandidato(C, *contador, nomeCandidato);
    existeNumCandidato = numCandidatoExiste(C, numCandidato, *contador);

    filiacao = NULL;
    if(existePartido && !existeNome && !existeNumCandidato){
        for(int i = 0; i<numPartidos; i++){
            if(strcmp(P[i].nomePrtd, partido) == 0){
                filiacao = &P[i];
                break;
            }
        }
        if(filiacao != NULL){
            strcpy(C[*contador].nomeCandidato, nomeCandidato);
            C[*contador].idade = idadeCandidato;
            strcpy(C[*contador].num_canditados, numCandidato);
            C[*contador].voto = 0;
            C[*contador].filiacao = filiacao;
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


void registrarFederacao(federacao*F,partidos*P,  int *contadorFederacao, int numPartidos){
    /*Função responsável por cadastrar e verificar se todas as entradas da federação estão certas. Não retorna nada.*/
    char nomeF[50];
    char siglaF[10];
    char siglaPartidoInserir[50];
    int continuar = 1;


    if(numPartidos < 2){
        printf("Não é possível cadastrar Federação! Menos de dois partidos cadastrados!\n");
        return;
    }

    
    printf("Digite o nome da Federacao: ");
    fgets(nomeF, sizeof(nomeF), stdin);
    normalizaString(nomeF);
    nomeF[strcspn(nomeF, "\n")] = '\0'; // Remove o \n da nova linha;

    if(!letras(nomeF)){
        printf("ERRO: O nome da federação deve conter apenas letras!\n");
        return;
    }
    if(verificaExisFederacao(F, *contadorFederacao, nomeF)){
        printf("ERRO: Existe uma federação com esse nome!\n");
        return;
    }

    printf("Digite a sigla da Federacao: ");
    fgets(siglaF, sizeof(siglaF), stdin);
    normalizaString(siglaF);
    siglaF[strcspn(siglaF, "\n")] = '\0'; //Remove o \n da nova linha;

    if(!letras(siglaF)){
        printf("ERRO: A sigla da federação deve conter apenas letras!\n");
        return;
    }
    if(verificaExisFederacao(F, *contadorFederacao, siglaF)){
        printf("ERRO: Existe uma federação com essa sigla!\n");
        return;
    }
    
    F[*contadorFederacao].partidosNaFederacao = alocaVetPartidos(numPartidos);
    F[*contadorFederacao].numPartido = 0;

    printf("Quais partidos vão fazer parte desta federação: ");
    while(continuar){
        printf("Digite a sigla do partido que você deseja adicionar a federação ('fim' para terminar): ");
        fgets(siglaPartidoInserir, sizeof(siglaPartidoInserir), stdin);
        normalizaString(siglaPartidoInserir);
        siglaPartidoInserir[strcspn(siglaPartidoInserir, "\n")] = '\0';

        if (strcmp(siglaPartidoInserir, "fim") == 0){
            if(F[*contadorFederacao].numPartido < 2){
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
                F[*contadorFederacao].numPartido++;
                break;
            }
        }
    }

    strcpy(F[*contadorFederacao].nomeFederacao, nomeF);
    strcpy(F[*contadorFederacao]. siglaFederacao, siglaF);
    (*contadorFederacao)++;

    printf("Federação cadastrada!\n");
    
}



void secao1(int* votosValidos, int* votosNulos, int* votosBranco, double* q_eleitoral){
    /* Função responsavél por mostrar na tela os votos gerais, valídos, brancos, nulos e o quociente eleitoral. Não retorna nada. */ 
    int votos = 0;

    *q_eleitoral += (*q_eleitoral + *votosValidos)/24;
    votos += *votosValidos + *votosNulos + *votosBranco;
    
    printf("_____________________________________________\n");
    printf("|                                           |\n");
    printf("            Votos totais: %d                \n", votos);
    printf("            Votos valídos: %d               \n", *votosValidos);           
    printf("            Votos brancos: %d               \n", *votosBranco);
    printf("            Votos nulos: %d                 \n", *votosNulos);
    printf("            Quocinte eleitoral: %.2lf       \n", *q_eleitoral);
    printf("|___________________________________________|\n");

}
void secao2(candidato* C, int numCandidatos) {
    /*Função responsavél por mostrar na tela o nome e o número total de votos que cada candidato obteve. Não retorna nada. */
    printf("_____________________________________________\n");
    printf("|                                           |\n");
    printf("|            Candidatos e Votos             |\n");
    printf("|___________________________________________|\n");
    printf("|                                           |\n");
    printf("| %-28s | %-10s |\n", "Nome do Candidato", "Votos");
    printf("|___________________________________________|\n");
    printf("|                                           |\n");

    for (int i = 0; i < numCandidatos; i++) {
        printf("  %-28s | %-10d \n", C[i].nomeCandidato, C[i].voto);
    }
    
    printf("|___________________________________________|\n");
}


void secao3(partidos* P, int numPartidos, federacao* F, int numFederacao){
   /* Função responsavél por mostrar na tela o nome e o número total de votos que cada partido/federação obteve. Não retorna nada.*/

    printf("_____________________________________________\n");
    printf("|                                           |\n");
    printf("|             Partidos e Votos              |\n");
    printf("|___________________________________________|\n");
    printf("|                                           |\n");
    printf("| %-30s | %8s |\n", "Nome do Partido", "Votos");
    printf("|___________________________________________|\n");
    printf("|                                           |\n");

    // Mostrar votos por federação
    for (int j = 0; j < numFederacao; j++) {
        int votosFederacao = F[j].voto;
        // Somar votos dos partidos que pertencem à federação
        for (int p = 0; p < numPartidos; p++) {
            if (strcmp(P[p].siglaFederacao, F[j].siglaFederacao) == 0) {
                votosFederacao += P[p].voto;  // Adiciona votos do partido à federação
            }
        }
        F[j].voto = votosFederacao;
        printf("  %-30s | %-10d  \n", F[j].nomeFederacao, votosFederacao);
    }

    // Mostrar votos por partido que não faz parte de nenhuma federação
    for (int k = 0; k < numPartidos; k++) {
        if (P[k].siglaFederacao[0] == '\0') {  // Verifica se o partido não pertence a nenhuma federação
            printf("  %-30s | %-10d  \n", P[k].nomePrtd, P[k].voto);
        }
    }
    printf("|___________________________________________|\n");
}

void secao4(partidos* P, int numPartidos, federacao* F, int numFederacao, int votosValidos){
    /*Função responsavél por mostrar na tela uma tabela informando o nome, o quociente partidário de cada partido ou federação e o número de cadeiras ao qual ele tem direito. Não retorna nada*/
    double quocienteEleitoral = (double)votosValidos / 24;

    if (votosValidos == 0) {
        printf("Erro: Não há votos válidos suficientes para calcular o quociente eleitoral.\n");
        return;
    }

    printf("_________________________________________________________________\n");
    printf("|                                                               |\n");
    printf("|        Partido/Federacao         | Quociente Part. | Cadeiras |\n");
    printf("|_______________________________________________________________|\n");
    printf("|                                                               |\n");
    

    
    for (int i = 0; i < numFederacao; i++) {
        double quocientePartidario = F[i].voto / quocienteEleitoral;
        int numeroCadeiras = quocientePartidario;
        printf("  %-32s | %-16.2lf | %-8d  \n", F[i].nomeFederacao, quocientePartidario, numeroCadeiras);
    }

    for (int j = 0; j < numPartidos; j++) {
        if (P[j].siglaFederacao[0] == '\0') { 
            double quocientePartidario = P[j].voto / quocienteEleitoral;
            int numeroCadeiras = quocientePartidario;
            printf("  %-32s | %-16.2lf | %-8d  \n", P[j].nomePrtd, quocientePartidario, numeroCadeiras);
        }
    }

    printf("|_______________________________________________________________|\n");
}

void secao5(candidato* C, int numCandidatos, double q_eleitoral){
   /*Função responsavél por mostrar na tela uma tabela com os nomes dos candidatos eleitos e sua respectiva legenda. Não retorna nada.*/
    printf("____________________________________________________________\n");
    printf("|                                                          |\n");
    printf("|               Candidatos Eleitos e Legenda               |\n");
    printf("|__________________________________________________________|\n");
    printf("|                                                          |\n");
    printf("| %-34s | %-19s |\n", "Nome do Candidato", "Legenda");
    printf("|__________________________________________________________|\n");
    printf("|                                                          |\n");

    double quocienteMinimo = 0.1 * q_eleitoral;
    int vagasDistribuidas = 0;


    for (int i = 0; i < numCandidatos; i++) {
        if (C[i].voto >= quocienteMinimo) {
            printf("  %-34s | %-10s  \n", C[i].nomeCandidato, C[i].filiacao->siglaPrtd);
            vagasDistribuidas++;
        }
    }

    // Aqui verificamos se há vagas remanescentes e as distribuímos pela média
    // Ordenar os candidatos que não foram eleitos mas têm votos > 0 por votos e idade
    for (int i = 0; i < numCandidatos - 1; i++) {
        for (int j = i + 1; j < numCandidatos; j++) {
            if (C[j].voto > C[i].voto || 
               (C[j].voto == C[i].voto && C[j].idade > C[i].idade)) {
                candidato temp = C[i];
                C[i] = C[j];
                C[j] = temp;
            }
        }
    }

    // Considerando que o número de cadeiras seja conhecido (24 por exemplo)
    int numCadeiras = 24;

    // Distribuir as vagas remanescentes
    int vagasRestantes = numCadeiras - vagasDistribuidas;
    for (int i = 0; i < numCandidatos && vagasRestantes > 0; i++) {
        if (C[i].voto < quocienteMinimo && C[i].voto > 0) {
            printf("| %-34s | %-10s |\n", C[i].nomeCandidato, C[i].filiacao->siglaPrtd);
            vagasRestantes--;
        }
    }
    printf("|__________________________________________________________|\n");
}


void secao6(candidato* C, int numCandidatos, double q_eleitoral) {
    /*Função responsável por mostrar na tela uma tabela com os candidatos suplentes, em ordem decrescente de quociente eleitoral. Em caso de empate, o candidato com maior idade terá preferência. Não retorna nada.*/
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
    printf("______________________________________________________________\n");
    printf("|                                                             |\n");
    printf("|                    Candidatos Suplentes                     |\n");
    printf("|_____________________________________________________________|\n");
    printf("|                                                             |\n");
    printf("| %-28s | %-16s | %-9s |\n", "Nome do Candidato", "Votos", "Idade");
    printf("|_____________________________________________________________|\n");
    printf("|                                                             |\n");

    for (int i = 0; i < contadorSuplentes; i++) {
        printf("  %-28s | %-16d | %-8d  \n", suplentes[i].nomeCandidato, suplentes[i].voto, suplentes[i].idade);
    }

    printf("|_____________________________________________________________|\n");

    // Libera memória
    free(suplentes);
}

void incrementarVoto(partidos* P, int numPartidos, federacao* F, int numFederacao, char* siglaPartido) {
    /*Função responsável por contar os votos, tanto dos partidos quanto das federações. Não retorna nada.*/
     normalizaString(siglaPartido);
    //
    int iFederacao = verificaExisFederacao(F, numFederacao, siglaPartido);
    if (iFederacao != 0) {  // Verifica se a federação foi encontrada
        F[iFederacao].voto++;  // Incrementa o voto na federação
    } else {
        for (int i = 0; i < numPartidos; i++) {
            if (strcmp(P[i].siglaPrtd, siglaPartido) == 0) {
                P[i].voto++;  // Incrementa o voto no partido
                break;
            }
        }
    }
}

void iniciarVotacao(candidato* C, int* numCandidatos, int* votosNulos, int* votosBranco, int* votosValidos, double q_eleitoral, partidos* P, int* numPartidos, federacao* F, int* numFederacao) {
    /* Função responsável por mostrar na tela todos os menus relacionados a votação, confirma e conta os votos, por fim mostra todas as seções do programa. Não retorna nada. */
    int continuar = 1;
    int opcao, votoConfirmado = 0;
    int escola;
    char numCandidato[6]; // 5 dígitos + '\0'
    candidato *candidatoEscolhido = NULL;

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
                    normalizaString(C[i].num_canditados);
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

                do{
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
                        if (candidatoEscolhido && candidatoEscolhido->filiacao != NULL) {
                            candidatoEscolhido->voto++;
                            (*votosValidos)++;
                            incrementarVoto(P, *numPartidos, F, *numFederacao, candidatoEscolhido->filiacao->siglaPrtd);
                            printf("Voto registrado para %s\n", candidatoEscolhido->nomeCandidato);
                        } else if (!candidatoEscolhido) {
                            (*votosNulos)++;
                            printf("Voto Nulo registrado.\n");
                        }
                    }
                    else if (votoConfirmado == 2){
                        break;
                    } else if (votoConfirmado == 3) {  // Votar em branco
                        (*votosBranco)++;
                        printf("Voto em Branco registrado.\n");
                    } else {
                        printf("Escolha entre as opções disponiveis.\n");
                    }
                }while(votoConfirmado != 1 && votoConfirmado != 3);
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
    }
}

void menu(){
    /*Função responsável por armazenar o valor de todas as variavéis, mostrar os menus principais, de cadastros, inicio da votação e finalizar o programa. Não retorna nada. */
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
    int tamCandidatos = 50;
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
                    if(P == NULL){
                        printf("ERRO: realocação mal sucedida!\n");
                        exit(1);
                    }
                }
                printf("Cadastrando o %dº partido!\n", contadorPartidos + 1);
                cadastrarPartido(P, &contadorPartidos);
                printf("Deseja inserir outro partido? (1 - Sim / 0 - Não): ");
                continuar = obterInteiro();
                printf("\n");
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
                printf("Deseja cadastrar outro candidato? (1 - Sim / 0 - Não): ");
                continuar = obterInteiro();
                printf("\n");
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
                printf("\n");
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
            break;
        }
    }while(op != 5);
        printf("Finalizando...\n");
    free(P); // Limpa a memória
}

int main() {
    /*Função responsável por chamar o menu e retorna 0.*/
    menu();
    return 0;
}