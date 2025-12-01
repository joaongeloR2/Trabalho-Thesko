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


//-----------------------------
//-------Vetores Globais:------ 
//-----------------------------

TpAdimin RegistroDeAdministracao[MAX_ADMINISTRACAO];
int qtd_admin = 0;

TpPrescricao listaPrescricao[MAX_MEDICAMENTOS];
int qtd_prescricao = 0;

TpResidente listaResidentes[MAX_RESIDENTES];
int qtd_residentes = 0;

TpMedicamento listaMedicamentos[MAX_MEDICAMENTOS];
int qtd_medicamentos = 0;


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


int main()
{
    int opcao = 0;
    
    do{
        printf("\n================================\n");
        printf("      SISTEMA DE RESIDENTES      \n");
        printf("================================\n");
        printf("1. Cadastrar Residente\n");
        printf("2. Buscar Residente\n");
        printf("3. Cadastrar Medicamento\n");
        printf("4. Buscar Medicamento\n");
        printf("5. Cadastrar Prescrição\n");
        printf("6. Buscar Prescricao por nome\n");
        printf("7. Buscar prescricao por ID\n");
        printf("8. Verificar estoque baixo\n");
        printf("0. Sair\n");
        printf("================================\n");
        printf("Digite uma opcao: "); 
        
        scanf("%d", &opcao);
        limparBufferEntrada();
        
        
        switch(opcao)
        {
            case 1:{
                CadastroResidente();
                break;
            }
        
            case 2: {
                char nome[50];
                printf("Digite o nome: ");
                lerString(nome , 50);
                BuscarResidente(nome);
                break;
            }
            
            case 3: {
                CadastroMedicamento();
                break;
            }
                
            case 4: {
                char nomeMed[50];
                printf("Digite o nome do medicamento: ");
                lerString(nomeMed , 50);
                BuscarMedicamento(nomeMed);
                break;
            }
                
            case 5: {
                CadastrarPrescricao();
                break;
            }
                
                
            case 6: {
                char nomeRes[50];
                printf("Digite o nome do residente: ");
                lerString(nomeRes , 50);
                buscaPrescricaoResidente(nomeRes);
                break;
            }
            
            
            case 7: {
                int id;
                printf("digite o ID da prescricao: ");
                 scanf("%d", id);
                limparBufferEntrada();
                buscaPrescricaoId(id);
                break;
            }
            
            
            case 8: {
                printf("\n ------ PRESCRICOES COM ESTOQUE BAIXO ------\n");
                
                int encontrou = 0;
                
                for(int i = 0 ; i < qtd_prescricao ; i++){
                    if(lowEstoque(listaPrescricao[i])){
                        encontrou = 1;
                        printf("ID: %d | Residente : %s | Medicamento: %s | Restante: %d\n", 
                               listaPrescricao[i].identificador , 
                               listaPrescricao[i].residente.nomeResidente ,
                               listaPrescricao[i].medicamento.medicamento , 
                               listaPrescricao[i].quant_cartela);
                    }
                }
                
                if(!encontrou){
                    printf("Nenhum medicamento com estoque baixo\n");
                    break;
                }
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
            return 1;
        }
    }
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
        printf("Nome invalido. Digite novamente: ");

        lerString( temp.nomeResidente , 50 );
    }

    printf("Telefone do responsavel: ");
    lerString( temp.contatoResponsavel , 15 );

    //verifica o telefone
    while( ValTelefone( temp.contatoResponsavel ) == 0 ){
        printf("Telefone invalido. Digite novamente: ");

        lerString( temp.contatoResponsavel , 15 );
    }

    printf("Data de nascimento (dia mes ano): ");
    scanf("%d %d %d", &data.dia, &data.mes, &data.ano);

    //limpando o buffer do scanf
    limparBufferEntrada();

    temp.dataNascimento = data;

    //verificando a data
    while( ValData( temp.dataNascimento ) == 0 ){
        printf("Data invalida. Digite novamente (dia, mes, ano): ");

        scanf("%d %d %d", &data.dia, &data.mes, &data.ano);

        //limpando o buffer do scanf
        limparBufferEntrada();

        temp.dataNascimento = data;
    }
   
    listaResidentes[qtd_residentes++] = temp;
    printf("Cadastro realizado com sucesso!\n");
    
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
                printf("Residente Encontrado\n");
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
    char searchName[50];
    TpMedicamento novo;

    
    //obtem nome e infos do medicamento  
    printf("Nome do Medicamento: ");
    lerString( novo.medicamento , 50 ); 
    
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
                printf("Periodo( em horas): %d\n", listaMedicamentos[i].periodo);
                printf("Quantidade por cartela: %d\n", listaMedicamentos[i].quant_cartela);
                encontrado++;
                break;
            } 
        }
        if( encontrado == 0 ){
            printf("Medicamento nao encontrado/cadastrado\n");
            //pergunta se quer verificar novamente
            printf("Deseja verificar novamente?\n");
            printf("1 (sim) / 2 (nao)");
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
            printf("Residente nao encontrado\n");
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
            printf("Medicamento nao encontrado\n");
        }
    } while (!achou);

    //inicializa dizendo que o paciente esta tomando o remedio
    novo.tomando = 'S';
    
    listaPrescricao[qtd_prescricao++] = novo;
    
    printf("Prescricao cadastrada com sucesso");
}

//busca prescricao pelo nome do residente 
void buscaPrescricaoResidente(char nome[]){
    int encontrado = 0,
        validacao = 0;
        
    do{
        for(int i = 0 ; i < qtd_prescricao ; i++){
            if(strcmp(listaPrescricao[i].residente.nomeResidente , nome) == 0){
                printf("PRESCRICAO ENCONTRADA"); 
                printf("Id prescricao: %d\n", listaPrescricao[i].identificador);
                printf("Residente: %s\n", listaPrescricao[i].residente.nomeResidente);
                printf("Medicamento: %s\n", listaPrescricao[i].medicamento.medicamento);
                printf("Dosagem: %d m/g\n", listaPrescricao[i].medicamento.dosagem);
                printf("Periodo: %d\n", listaPrescricao[i].medicamento.periodo);
                printf("Quantidade por cartela: %d\n", listaPrescricao[i].medicamento.quant_cartela); 
                printf("Tomando: %c\n", listaPrescricao[i].tomando);
                encontrado = 1;
                break;
            }
        }
        
        if(!encontrado){
            printf("Prescricao nao encontrada para este residente\n");
            printf("Deseja buscar novamente? 1(sim) 2(nao): ");
            
            scanf("%d", &validacao);
            limparBufferEntrada();
            
            if(validacao == 1){
                printf("Digite o nome:");
                
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
                printf("PRESCRICAO ENCONTRADA"); 
                printf("Id prescricao: %d\n", listaPrescricao[i].identificador);
                printf("Residente: %s\n", listaPrescricao[i].residente.nomeResidente);
                printf("Medicamento: %s\n", listaPrescricao[i].medicamento.medicamento);
                printf("Dosagem: %d m/g\n", listaPrescricao[i].medicamento.dosagem);
                printf("Periodo: %d\n", listaPrescricao[i].medicamento.periodo);
                printf("Quantidade por cartela: %d\n", listaPrescricao[i].medicamento.quant_cartela); 
                printf("Tomando: %c\n", listaPrescricao[i].tomando);
                encontrado = 1;
                break;
            }
        }
        
        if(!encontrado){
            printf("Prescricao nao encontrada parta este residente\n");
            printf("Deseja buscar novamente? 1(sim) 2(nao): ");
            
            scanf("%d", &validacao);
            limparBufferEntrada();
            
            if(validacao == 1){
                printf("Digite o ID:");
                
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
