/******************************************************
 * Turma.: EC41A - Algoritmos 1
 * Aluno.: João Angelo Costa de Oliveira e Kendi Komura Hatori 
 * Ra....: a2809125 e a2769158
 * Data..: 17/11/2025
 * Descrição: Trabalho Final de Algoritmos 01.
 ******************************************************/
 
 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MAX_RESIDENTES 20
#define MAX_MEDICAMENTOS 10
#define MAX_ADMINISTRACAO 500
#define MAX_PRESCRICAO_MEDICA 50

//-------------------------
//------//STRUTCS:---------
//-------------------------

//struct data
typedef struct Data {
    int dia;
    int mes;
    int ano;
} TpData;

//struct residente
typedef struct Residente {
    char nomeResidente[50];
    char contatoResponsavel[15];
    TpData dataNascimento;
} TpResidente;

//struct medicamento
typedef struct Medicamento {
    char medicamento[50];
    int dosagem;
    int periodo;
    int quant_cartela; //quantidade que vem na cartela (caixa)
} TpMedicamento;

//struct prescrição
typedef struct Prescricao {
    int identificador;
    TpResidente residente;
    TpMedicamento medicamento;
    int quant_cartela;
    char tomando;
} TpPrescricao;

//struct administração
typedef struct Administração {
    int identificador;
    int idPrescricao;
    TpData dataAdmin;
    int horaRemedio;
    int idEnfermeiro;
} TpAdimin;


//Lista de enfermeiros 
typedef struct {
    int id;
    char nome[50];
} TpEnfermeiro;


//-----------------------------
//-------Vetores Globais:------ 
//-----------------------------

TpEnfermeiro listaEnfermeiros[] = { {1001 , "Bento Curativo"},
                                    {1002 , "Valdemar Remedio"},
                                    {1003 , "Tadeu Seringa"},
                                    {1004 , "Lucio Sergio Gaze"},
                                    {1005 , "Helena Salva Vidas"} };
int qtd_enfermeiros = 5;

TpAdimin RegistroDeAdministracao[MAX_ADMINISTRACAO] = {
    // Prescrição 1 – Joao – Losartana (intervalo 12h)
    {1, 1, {20,11,2025}, 8, 1001},
    {2, 1, {21,11,2025}, 8, 1003},
    {3, 1, {23,11,2025}, 8, 1002}, // atraso proposital para testar interrupção

    // Prescrição 2 – Maria – Omeprazol (24h)
    {4, 2, {25,11,2025}, 9, 1004},
    {5, 2, {26,11,2025}, 9, 1005},

    // Prescrição 3 – Carlos – Paracetamol (8h)
    {6, 3, {27,11,2025}, 7, 1001},
    {7, 3, {28,11,2025}, 15, 1003},
    {8, 3, {29,11,2025}, 23, 1002},

    // Prescrição 4 – Ana – Metformina (12h)
    {9, 4, {20,11,2025}, 8, 1004},
    {10, 4, {27,11,2025}, 8, 1004}, // atraso proposital

    // Prescrição 5 – Beatriz – Sinvastatina (24h)
    {11, 5, {25,11,2025}, 21, 1005}
};
int qtd_admin = 11;


TpPrescricao listaPrescricao[MAX_MEDICAMENTOS] = {
    {1, {"Joao Silva",      "011999999999", {10,5,1950}},   {"Losartana",50,12,30}, 30, 'S'},
    {2, {"Maria Souza",     "011988887777", {22,11,1945}},  {"Omeprazol",20,24,28}, 28, 'S'},
    {3, {"Carlos Pereira",  "011977776666", {3,2,1940}},    {"Paracetamol",500,8,20}, 20, 'S'},
    {4, {"Ana Oliveira",    "011966665555", {17,9,1955}},   {"Metformina",850,12,30}, 30, 'S'},
    {5, {"Beatriz Gomes",   "011955554444", {8,7,1938}},    {"Sinvastatina",40,24,30}, 30, 'S'}
};
int qtd_prescricao = 5;


TpResidente listaResidentes[MAX_RESIDENTES] = {
    {"Joao Silva",      "011999999999", {10, 5, 1950}},
    {"Maria Souza",     "011988887777", {22, 11, 1945}},
    {"Carlos Pereira",  "011977776666", {3, 2, 1940}},
    {"Ana Oliveira",    "011966665555", {17, 9, 1955}},
    {"Beatriz Gomes",   "011955554444", {8, 7, 1938}}
};
int qtd_residentes = 5;


TpMedicamento listaMedicamentos[MAX_MEDICAMENTOS] = {
    {"Losartana",     50, 12, 30},
    {"Omeprazol",     20, 24, 28},
    {"Paracetamol",  500,  8, 20},
    {"Metformina",   850, 12, 30},
    {"Sinvastatina",  40, 24, 30}
};
int qtd_medicamentos = 5;



//------------------------------------
//-----------PROTOTIPO FUNÇÕES:-------
//------------------------------------

//validação de nome
int ValNome( char nome[] );


//validação de telefone
int ValTelefone( char telefone[] );


//validação da data
int ValData( TpData a );


//cadastro de residentes
void CadastroResidente();


//buscar residente pelo nome
void BuscarResidente( char nome[] );


//cadastro de medicamentos 
void CadastroMedicamento();


//buscar medicamento pelo nome
void BuscarMedicamento( char nome[] );


//cadastrar prescricao
void CadastrarPrescricao();


//busca prescricao pelo nome do residente 
void buscaPrescricaoResidente(char nome[]);


//busca prescricao pelo id da prescricao
void buscaPrescricaoId(int id);


//estoque baixo de medicamento
int lowEstoque(TpPrescricao p);


//retirando o \n das strings
void lerString( char str[], int tamanho );


//limpar buffer de entrada
void limparBufferEntrada();


// Função para verificar se um enfermeiro é válido
int verificaEnfermeiro(int id);


//Administração
void RegistrarAdministracao();


//data para dias desde o dia zero 
int dataParaDias(TpData d);


//Funcao auxiliar para encontrar a ujltima administração de uma prescrição
TpData ultimaAdministracao(int idPrescricao);


//funcao auditoria 
void AuditoriaInterrupcao7Dias();


//funcao auxiliar para encontrar a penultima administração
TpData penultimaAdministracao(int idPrescricao);


//funcao para detectar atrasos e marcar interrupcoes 
void DetectarInterrupcoes();

int main()
{
    int opcao = 0;
    
    do{
        printf("\n==========================================\n");
        printf("           SISTEMA DE RESIDENTES      \n");
        printf("==========================================\n");
        printf("01. Auditoria de interrupcao (7 dias)\n");
        printf("02. Cadastrar medicamento\n");
        printf("03. Cadastrar prescricao\n");
        printf("04. Cadastrar residente\n");
        printf("05. Buscar medicamento\n");
        printf("06. Buscar prescricao por ID\n");
        printf("07. Buscar prescricao por nome\n");
        printf("08. Buscar residente\n");
        printf("09. Detectar interrupcoes automaticamente\n");
        printf("10. Registrar administracao de medicamento\n");
        printf("11. Verificar estoque baixo\n");
        printf("00. Sair\n");
        printf("==========================================\n");
        printf("Digite uma opcao: "); 
        
        scanf("%d", &opcao);
        limparBufferEntrada();
        printf("==========================================\n");
        
        
        switch(opcao)
        {
            case 4:{
                CadastroResidente();
                break;
            }
            
            
            case 8: {
                char nome[50];
                printf("Digite o nome: ");
                lerString(nome , 50);
                BuscarResidente(nome);
                break;
            }
            
            
            case 2: {
                CadastroMedicamento();
                break;
            }
            
                
            case 5: {
                char nomeMed[50];
                printf("Digite o nome do medicamento: ");
                lerString(nomeMed , 50);
                BuscarMedicamento(nomeMed);
                break;
            }
            
                
            case 3: {
                CadastrarPrescricao();
                break;
            }
                
                
            case 7: {
                char nomeRes[50];
                printf("Digite o nome do residente: ");
                lerString(nomeRes , 50);
                buscaPrescricaoResidente(nomeRes);
                break;
            }
            
            
            case 6: {
                int id;
                printf("digite o ID da prescricao: ");
                scanf("%d", &id);
                limparBufferEntrada();
                buscaPrescricaoId(id);
                break;
            }
            
            
            case 11: {
                printf("====== prescricoes com estoque baixo =====\n");
                
                int encontrou = 0;
                
                for(int i = 0 ; i < qtd_prescricao ; i++){
                    if(lowEstoque(listaPrescricao[i])){
                        encontrou = 1;
                        printf("ID: %d | Residente : %s | Medicamento: %s | Restante: %d", 
                               listaPrescricao[i].identificador , 
                               listaPrescricao[i].residente.nomeResidente ,
                               listaPrescricao[i].medicamento.medicamento , 
                               listaPrescricao[i].quant_cartela);
                    }
                }
                
                if(!encontrou){
                    printf("Nenhum medicamento com estoque baixo");
                    break;
                }
                break;
            }
            
            case 10: {
                RegistrarAdministracao();
                break;
            }
            
            
            case 1: {
                AuditoriaInterrupcao7Dias();
                break;
            }
            
            
            case 9: {
                DetectarInterrupcoes();
                break;
            } 
            
            
            case 0: {
                printf("Saindo do sistema...\n");
                break;
            }
            
            
            default: {
                printf("Opcao invalida!! Tente Novamente.\n");
        }
    }
            
    }while(opcao != 0);


    return 0;
}


//-------------------------------
//----------FUNÇÕES:-------------  
//-------------------------------

//validação de nome
int ValNome( char nome[] ){
    int tam = strlen( nome );
    int val = 0;

    //verifica o tamanho
    if( tam < 8 ){
        return 0;
    }

    //verifica a primeira caracter
    if( nome[0] == ' ' ){
        return 0;
    }

    //verificando o ultimo caracter
    if( nome[ tam -1 ] == ' ' ){
        return 0;
    }

    //verficia se a numeros
    for( int i = 0 ; i < tam ; i++ ){
        if( nome[i] >= '0' && nome[i] <= '9' ){
            return 0;
        }
        //verifica se é nome composto
        if( nome[i] == ' ' ){
            val++;
        }
    }
    return val;
}

//validação de telefone
int ValTelefone( char telefone[] ){
    int tamanho = 0;

    //verifica o primeiro numero
    if( telefone[0] != '0' ){
        return 0;
    }

    tamanho = strlen( telefone );

    //verfica o tamanho
    if( tamanho != 11 && tamanho != 12 ){
        return 0;
    }

    //verificando se todos são numeros
    for( int i = 0 ; i < tamanho ; i++ ){
        if( telefone[i] < '0' || telefone[i] > '9' ){
            return 0;
        }
    }

    return 1;
}

//validação da data
int ValData( TpData a ){
    int validacao = 0,
        bissexto = 0;

    //verficando mes valido
    if( a.mes < 1 || a.mes > 12 ){
        return 0;
    }
    //verificando meses com 31 dias
    if( a.mes == 1 || a.mes == 3 || a.mes == 5 || a.mes == 7 ||
        a.mes == 8 || a.mes == 10 || a.mes == 12 ){
        if( a.dia <= 31 && a.dia >= 1 ){
            validacao++;
        }
    }
    //verificando meses com 30 dias
    if( a.mes == 4 || a.mes == 6 || a.mes == 9 || a.mes == 11 ){
        if( a.dia <= 30 && a.dia >= 1 ){
            validacao++;
        }
    }
    //verificando ano bissexto
    bissexto = (a.ano % 400 == 0) || (a.ano % 4 == 0 && a.ano % 100 != 0);

    //verificando fevereiro
    if( a.mes == 2 ){
        if( bissexto == 1 ){
            if( a.dia <= 29 && a.dia >= 1 ){
                validacao++;
            }
        } else {
            if( a.dia <= 28 && a.dia >= 1 ){
                validacao++;
            }
        }    
    }
    return validacao;
}

//cadastro de residentes
void CadastroResidente(){
    TpData data;
    TpResidente temp;

    printf("Nome do Residente: ");
    lerString( temp.nomeResidente , 50 );

    //verificação do nome
    while( ValNome ( temp.nomeResidente ) == 0 ){
        printf("Nome invalido.\nDigite novamente: ");

        lerString( temp.nomeResidente , 50 );
    }

    printf("Telefone do responsavel: ");
    lerString( temp.contatoResponsavel , 15 );

    //verifica o telefone
    while( ValTelefone( temp.contatoResponsavel ) == 0 ){
        printf("Telefone invalido.\nDigite novamente: ");

        lerString( temp.contatoResponsavel , 15 );
    }

    printf("Data de nascimento (dia, mes, ano): ");
    scanf("%d %d %d", &data.dia, &data.mes, &data.ano);

    //limpando o buffer do scanf
    limparBufferEntrada();

    temp.dataNascimento = data;

    //verificando a data
    while( ValData( temp.dataNascimento ) == 0 ){
        printf("Data invalida.\nDigite novamente (dia, mes, ano): ");

        scanf("%d %d %d", &data.dia, &data.mes, &data.ano);

        //limpando o buffer do scanf
        limparBufferEntrada();

        temp.dataNascimento = data;
    }
   
    listaResidentes[qtd_residentes++] = temp;
    printf("Cadastro realizado com sucesso!!");
    
}

//buscar residente pelo nome
void BuscarResidente( char nome[] ){
    int i = 0;
    int validacao = 0;
    int encontrado = 0;

    //compara nomes
    do{
        for(i = 0 ; i < qtd_residentes ; i++){
            if(strcmp(listaResidentes[i].nomeResidente , nome) == 0){
                printf("Residente Encontrado!!\n");
                printf("Nome: %s\n", listaResidentes[i].nomeResidente); 
                printf("Telefone do Responsavel: %s\n", listaResidentes[i].contatoResponsavel);
                printf("Data de nascimento: %d / %d / %d\n", 
                        listaResidentes[i].dataNascimento.dia ,
                        listaResidentes[i].dataNascimento.mes , 
                        listaResidentes[i].dataNascimento.ano );
                encontrado++;
                break;
            }
        }
        if( encontrado == 0 ){
            printf("Residente nao encontrado/cadastrado");
            //pergunta se quer verificar novamente
            printf("Deseja verificar novamente?\n");
            printf("1 (sim) / 2 (nao)");
            scanf("%d", &validacao);
        }
    } while ( validacao == 1 );
}

//cadastro de medicamentos 
void CadastroMedicamento(){
    TpMedicamento novo;

    
    //obtem nome e infos do medicamento  
    printf("Nome do Medicamento: ");
    lerString(novo.medicamento , 50 ); 
    
    for( int i = 0 ; i < qtd_medicamentos ; i++ ){
        if( strcmp (listaMedicamentos[i].medicamento , novo.medicamento) == 0){
            printf("Medicamento ja cadastrado!\n");
            return;
        }
    }

    //dosagem
    printf("Dosagem(mg): ");
    scanf("%d", &novo.dosagem);
    limparBufferEntrada();

    //periodo
    printf("Periodo(em horas): ");
    scanf("%d", &novo.periodo);
    limparBufferEntrada();

    //quantidade na cartela
    printf("Quantidade na cartela: ");
    scanf("%d", &novo.quant_cartela);
    limparBufferEntrada();

    //armazena no vetor global
    listaMedicamentos[qtd_medicamentos] = novo;
    qtd_medicamentos++;

    printf("Medicamento cadastrado com sucesso!!");
}

//buscar medicamento pelo nome
void BuscarMedicamento( char nome[] ){
    int i = 0;
    int validacao = 0;
    int encontrado = 0;
    
    do{
        validacao = 0;
        //compara todos medicamentos
        for( i = 0 ; i < qtd_medicamentos ; i++ ){
            if( strcmp(listaMedicamentos[i].medicamento , nome) == 0 ){
                printf("Medicamento Encontrado\n");
                printf("Nome: %s\n", nome);
                printf("Dosagem(mg): %d\n", listaMedicamentos[i].dosagem);
                printf("Periodo(em horas): %d\n", listaMedicamentos[i].periodo);
                printf("Quantidade por cartela: %d", listaMedicamentos[i].quant_cartela);
                encontrado++;
                break;
            } 
        }
        if( encontrado == 0 ){
            printf("Medicamento nao encontrado/cadastrado\n");
            //pergunta se quer verificar novamente
            printf("Deseja verificar novamente?\n");
            printf("1 (sim) / 2 (nao)\n");
            scanf("%d", &validacao);
        }
    } while ( validacao == 1 );
}

//cadastrar prescricao
void CadastrarPrescricao(){
  
    TpPrescricao novo;
    novo.identificador = qtd_prescricao + 1;
    
    //residente.........
    
    char nome[50];
    int achou = 0;
    
    do{
        printf("Nome do Residente: ");
        lerString(nome , 50); 
        
    
        for(int i = 0 ; i < qtd_residentes ; i++){
            if(strcmp(listaResidentes[i].nomeResidente , nome) == 0){
                novo.residente = listaResidentes[i];
                achou = 1;
                break;
            }
        }

        if(!achou){
            printf("Residente nao encontrado!\n");
        }
    } while (!achou);
   
   //medicamento....................
    TpMedicamento temp;
    achou = 0;
    
    do {
        printf("Nome do Medicamento: ");
        lerString( temp.medicamento , 50 );
        
        //procura o medicamento pelo nome 
        
        
        for( int i = 0 ; i < qtd_medicamentos ; i++ ){
            if( strcmp( listaMedicamentos[i].medicamento , temp.medicamento) == 0){
                novo.medicamento = listaMedicamentos[i];
                

                //colocando a quantia da cartela
                novo.quant_cartela = listaMedicamentos[i].quant_cartela;
                achou = 1;
                break;
            }
        }
        
        if(!achou ){
            printf("Medicamento nao encontrado!\n");
        }
    } while (!achou);

    //inicializa dizendo que o paciente esta tomando o remedio
    novo.tomando = 'S';
    
    listaPrescricao[qtd_prescricao++] = novo;
    
    printf("Prescricao cadastrada com sucesso!!04");
}

//busca prescricao pelo nome do residente 
void buscaPrescricaoResidente(char nome[]){
    int encontrado = 0,
        validacao = 0;
        
    do{
        for(int i = 0 ; i < qtd_prescricao ; i++){
            if(strcmp(listaPrescricao[i].residente.nomeResidente , nome) == 0){
                printf("PRESCRICAO ENCONTRADA\n"); 
                printf("Id prescricao: %d\n", listaPrescricao[i].identificador);
                printf("Residente: %s\n", listaPrescricao[i].residente.nomeResidente);
                printf("Medicamento: %s\n", listaPrescricao[i].medicamento.medicamento);
                printf("Dosagem: %d m/g\n", listaPrescricao[i].medicamento.dosagem);
                printf("Periodo: %d\n", listaPrescricao[i].medicamento.periodo);
                printf("Quantidade por cartela: %d\n", listaPrescricao[i].medicamento.quant_cartela); 
                printf("Tomando: %c", listaPrescricao[i].tomando);
                encontrado = 1;
                break;
            }
        }
        
        if(!encontrado){
            printf("Prescricao nao encontrada para este residente\n");
            printf("Deseja buscar novamente?\n1(sim) 2(nao): ");
            
            scanf("%d", &validacao);
            limparBufferEntrada();
            
            if(validacao == 1){
                printf("Digite o nome: ");
                
                lerString(nome , 50);
                
            }
        }
    }while(validacao == 1);
}


//busca prescricao pelo id da prescricao
void buscaPrescricaoId(int id){
    int encontrado = 0;
    int validacao = 0;
    
    do{
        for(int i = 0 ; i < qtd_prescricao ; i++){
            if(listaPrescricao[i].identificador == id){
                printf("PRESCRICAO ENCONTRADA\n"); 
                printf("Id prescricao: %d\n", listaPrescricao[i].identificador);
                printf("Residente: %s\n", listaPrescricao[i].residente.nomeResidente);
                printf("Medicamento: %s\n", listaPrescricao[i].medicamento.medicamento);
                printf("Dosagem: %d m/g\n", listaPrescricao[i].medicamento.dosagem);
                printf("Periodo: %d\n", listaPrescricao[i].medicamento.periodo);
                printf("Quantidade por cartela: %d\n", listaPrescricao[i].medicamento.quant_cartela); 
                printf("Tomando: %c", listaPrescricao[i].tomando);
                encontrado = 1;
                break;
            }
        }
        
        if(!encontrado){
            printf("Prescricao nao encontrada parta este residente\n");
            printf("Deseja buscar novamente?\n1(sim) 2(nao): ");
            
            scanf("%d", &validacao);
            limparBufferEntrada();
            
            if(validacao == 1){
                printf("Digite o ID: ");
                
                scanf("%d", &id);
                limparBufferEntrada();
            }
        }
    
    }while(validacao == 1);

}


//estoque baixo de medicamento
int lowEstoque(TpPrescricao p){
    //verifica se o residente esta tomando
    if(p.tomando == 'N' || p.tomando == 'n'){
        return 0;
    }
    
    double  limite = p.medicamento.quant_cartela * 0.10;
    
    return(p.quant_cartela <= limite );
}


//retirando o \n das strings
void lerString( char str[], int tamanho ){

    //tenta ler a string usando fgets
    if( fgets( str , tamanho , stdin ) != NULL ){
        str[strcspn( str, "\n" )] = 0;
    }
}


//limpar buffer de entrada
void limparBufferEntrada(){
    int c;
    while ((c = getchar()) != '\n' && c != EOF){}
}


// Função para verificar se um enfermeiro é válido
int verificaEnfermeiro(int id) {
    for(int i = 0 ; i < qtd_enfermeiros ; i++){
        if(listaEnfermeiros[i].id == id){
            return 1;
        }
    }
    return 0;
}


//administracao-
void RegistrarAdministracao() {
    int idPrescricao;
    printf("Digite o ID da prescricao: ");
    scanf("%d", &idPrescricao);
    limparBufferEntrada();
    
    // buscar prescrição pelo ID
    int indice = -1;
    for(int i = 0 ; i < qtd_prescricao ; i++){
        if(listaPrescricao[i].identificador == idPrescricao){
            indice = i;
            break;
        }
    }

    if(indice == -1){
        printf("Prescricao nao encontrada!\n");
        return;
    }

    // verificar estoque
    if(listaPrescricao[indice].quant_cartela <= 0){
        printf("Nao ha mais unidades desse medicamento em estoque!\n");
        return;
    }

    // coletar data
    TpData data;
    printf("Digite a data da administracao (dia mes ano): ");
    scanf("%d %d %d", &data.dia, &data.mes, &data.ano);
    limparBufferEntrada();

    if(ValData(data) == 0){
        printf("Data invalida!\n");
        return;
    }

    // coletar hora
    int hora;
    printf("Digite o horario da administracao (0-23): ");
    scanf("%d", &hora);
    limparBufferEntrada();

    if(hora < 0 || hora > 23){
        printf("Horario invalido!");
        return;
    }

    // coletar ID do enfermeiro
    int idEnf;
    printf("Digite o ID do enfermeiro: ");
    scanf("%d", &idEnf);
    limparBufferEntrada();

    // validar enfermeiro
    int valido = 0;
    for(int i = 0 ; i < qtd_enfermeiros ; i++){
        if(listaEnfermeiros[i].id == idEnf){
            valido = 1;
            break;
        }
    }

    if(!valido){
        printf("Enfermeiro nao encontrado!");
        return;
    }

    // criar registro
    TpAdimin novo;
    novo.identificador = qtd_admin + 1;  // auto incremental
    novo.idPrescricao = idPrescricao;
    novo.dataAdmin = data;
    novo.horaRemedio = hora;
    novo.idEnfermeiro = idEnf;

    // salvar no vetor global
    RegistroDeAdministracao[qtd_admin] = novo;
    qtd_admin++;

    // diminuir estoque da prescrição
    listaPrescricao[indice].quant_cartela--;

    printf("\nAdmistracao cadastrada com sucesso!!\n");
    printf("ID do registro: %d\n", novo.identificador);
    printf("Residente: %s\n", listaPrescricao[indice].residente.nomeResidente);
    printf("Medicamento: %s\n", listaPrescricao[indice].medicamento.medicamento);
    printf("Quantidade restante: %d\n", listaPrescricao[indice].quant_cartela);
}


//data para dias desde o dia zero 
int dataParaDias(TpData d){
    return d.ano * 365 + d.mes * 30 + d.dia;
}


//Funcao auxiliar para encontrar a ujltima administração de uma prescrição
TpData ultimaAdministracao(int idPrescricao) {
    TpData ultimo = {0,0,0};
    
    int diasUltimo = -1;

    for (int i = 0; i < qtd_admin; i++) {
        if (RegistroDeAdministracao[i].idPrescricao == idPrescricao) {
            int dias = dataParaDias(RegistroDeAdministracao[i].dataAdmin);
            if (dias > diasUltimo) {
                diasUltimo = dias;
                ultimo = RegistroDeAdministracao[i].dataAdmin;
            }
        }
    }

    return ultimo;
}


//funcao auditoria 
void AuditoriaInterrupcao7Dias() {

    printf("\n======== auditoria de interrupcao ========\n\n");

    int encontrou = 0;

    for (int i = 0; i < qtd_prescricao; i++) {

        // precisa estar marcado como interrompido
        if (listaPrescricao[i].tomando == 'N' || listaPrescricao[i].tomando == 'n') {

            // ainda há estoque
            if (listaPrescricao[i].quant_cartela > 0) {

                TpData ult = ultimaAdministracao(listaPrescricao[i].identificador);

                // se nunca tomou, não entra na auditoria
                if (ult.dia == 0) continue;

                // calcular diferença de dias
                int hojeDias = dataParaDias((TpData){1,12,2025});  // SIMULAÇÃO DO "HOJE"
                int ultDias  = dataParaDias(ult);

                if (hojeDias - ultDias >= 7) {

                    encontrou = 1;

                    printf("Residente: %s\n", listaPrescricao[i].residente.nomeResidente);
                    printf("  Medicamento: %s\n", listaPrescricao[i].medicamento.medicamento);
                    printf("  Ultima dose: %02d/%02d/%04d\n", 
                           ult.dia, ult.mes, ult.ano);
                    printf("  Estoque restante: %d\n", listaPrescricao[i].quant_cartela);
                    printf("---------------------------------------------------\n");
                }
            }
        }
    }

    if (!encontrou) {
        printf("Nenhuma interrupcao medica encontrada.\n");
    }
}


//funcao auxiliar para encontrar a penultima administração
TpData penultimaAdministracao(int idPrescricao){
    TpData ultima = {0,0,0};
    TpData penultima = {0,0,0};

    int diasUlt = -1, diasPen = -1;

    for (int i = 0; i < qtd_admin; i++) {
        if (RegistroDeAdministracao[i].idPrescricao == idPrescricao) {
            
            int dias = dataParaDias(RegistroDeAdministracao[i].dataAdmin);

            if (dias > diasUlt) {
                diasPen = diasUlt;
                penultima = ultima;

                diasUlt = dias;
                ultima = RegistroDeAdministracao[i].dataAdmin;
            }
            else if (dias > diasPen) {
                diasPen = dias;
                penultima = RegistroDeAdministracao[i].dataAdmin;
            }
        }
    }

    return penultima;
}


//funcao para detectar atrasos e marcar interrupcoes 
void DetectarInterrupcoes() {

    printf("\n======== deteccao de interrupcoes ========\n\n");

    double limitePercentual;
    printf("Digite a tolerancia percentual de atraso: \n");
    scanf("%lf", &limitePercentual);
    limparBufferEntrada();

    int encontrou = 0;

    for(int i = 0 ; i < qtd_prescricao ; i++){

        if(listaPrescricao[i].tomando == 'N') 
            continue;  // já está interrompido
        
        
        TpData ult = ultimaAdministracao(listaPrescricao[i].identificador);
        TpData pen = penultimaAdministracao(listaPrescricao[i].identificador);

        if (ult.dia == 0 || pen.dia == 0)
            continue;  // sem histórico suficiente

        int diasUlt = dataParaDias(ult);
        int diasPen = dataParaDias(pen);

        int intervaloReal = diasUlt - diasPen;
        int intervaloPrev = listaPrescricao[i].medicamento.periodo / 24; // transformar horas em dias

        if (intervaloPrev == 0) intervaloPrev = 1;

        double limite = intervaloPrev + (intervaloPrev * (limitePercentual/100.0));

        if (intervaloReal > limite) {

            // marca como interrompido!
            listaPrescricao[i].tomando = 'N';
            encontrou = 1;

            printf("Interrupcao detectada!\n");
            printf("Residente: %s\n", listaPrescricao[i].residente.nomeResidente);
            printf("Medicamento: %s\n", listaPrescricao[i].medicamento.medicamento);
            printf("Intervalo real: %d dias | Intervalo permitido: %.1f dias\n",
                   intervaloReal, limite);
            printf("Status: NAO TOMANDO\n");
            printf("-----------------------------------------------\n");
        }
    }

    if (!encontrou) {
        printf("Nenhuma interrupcao detectada.\n");
    }
}