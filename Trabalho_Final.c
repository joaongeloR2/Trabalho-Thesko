/******************************************************
 * Turma.: EC41A - Algoritmos 1
 * Aluno.: João Angelo Costa de Oliveira e ......................
 * Ra....: a2809125 e ...........................
 * Aluno.: João Angelo Costa de Oliveira e Kendi Komura Hatori 
 * Ra....: a2809125 e a2769158
 * Data..: 17/11/2025
 * Descrição: Trabalho Final de Algoritmos 01.
 ******************************************************/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

#define MAX_RESIDENTES 20
#define MAX_MEDICAMENTOS 10
#define MAX_ADMINISTRACAO 500
#define MAX_PRESCRICAO_MEDICA 50

//Vetores Globais: 

TpAdimin RegistroDeAdministracao[MAX_ADMINISTRACAO];
int qtd_admin = 0;

TpPrescricao listaPrescricao[MAX_MEDICAMENTOS];
int qtd_prescricao = 0;

TpResidente listaResidentes[MAX_RESIDENTES];
int qtd_residentes = 0;

TpMedicamento listaMedicamentos[MAX_MEDICAMENTOS];
int qtd_medicamentos = 0;

//STRUTCS:

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

//FUNÇÕES:

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
    if( a.mes < 0 || a.mes > 12 ){
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

    lerString( temp.nomeResidente , 50 );

    //verificação do nome
    while( ValNome ( temp.nomeResidente ) == 0 ){
        printf("Nome invalido. Digite novamente: ");

        lerString( temp.nomeResidente , 50 );
    }

    lerString( temp.contatoResponsavel , 15 );

    //verifica o telefone
    while( ValTelefone( temp.contatoResponsavel ) == 0 ){
        printf("Telefone invalido. Digite novamente: ");

        lerString( temp.contatoResponsavel , 15 );
    }

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
    printf("Cadastro realizado com sucesso!\n");
    
    listaResidentes[qtd_residentes] = temp;
    qtd_residentes++;
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
    fgets(novo.medicamento , 50 , stdin); 
    
    for( int i = 0 ; i < qtd_medicamentos ; i++ ){
        if( strcmp (listaMedicamentos[i].medicamento , novo.medicamento) == 0){
            printf("Medicamento ja cadastrado!\n");
            return;
        }
    }

    //dosagem
    printf("Dosagem(mg): ");
    scanf("%d", &novo.dosagem);
    limparBufferEntrada():

    //periodo
    printf("Periodo(em horas): ");
    scanf("%d", &novo.horaRemedio);
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
                printf("Periodo( em horas): %d\n", listaMedicamentos[i].horaRemedio);
                printf("Quantidade por cartela: %d\n", listaMedicamentos[i].quant_cartela);
                encontrado++;
                break;
            } 
        }
        if( encontrado == 0 ){
            printf("Medicamento nao encontrado/cadastrado");
            //pergunta se quer verificar novamente
            printf("Deseja verificar novamente?\n");
            printf("1 (sim) / 2 (nao)");
            scanf("%d", &validacao);
        }
    } while ( validacao == 1 );
}

//cadastrar prescricao
void CadastrarPrescricao(){
    char busca[100];
    TpResidente residente;
    TpPrescricao novo;
    
    do{
        printf("Nome do Residente: ");
        lerString(residente.nomeResidente , 50); 
        
        //procura o residente pelo nome 
        int idResidente = -1; //inicializado com -1 pois ao inicializar com  0 , um residente ja cadastrado pode ser identificado como n cadastrado...
    
        for(int i = 0 ; i < qtd_residentes ; i++){
            if(strcmp(listaResidentes[i].nomeResidente , residente.nomeResidente) == 0){
                novo.residente = listaResidentes[i];
                idResidente = 1;
                break;
            }
        }

        if(idResidente == -1){
            printf("Residente nao encontrado\n");
        }
    } while (idResidente == -1);
   
    
    do {
        printf("Nome do Medicamento: ");
        lerString( medicamento.medicamento , 50 );
        
        //procura o medicamento pelo nome 
        int idMedicamento = -1;
        
        for( int j = 0 ; j < qtd_medicamentos ; j++ ){
            if( strcmp( listaMedicamentos[j].medicamento , medicamento.medicamento) == 0){
                novo.medicamento = listaMedicamentos[j];
                idMedicamento = 1;

                //colocando a quantia da cartela
                novo.quant_cartela = listaMedicamentos[j].quant_cartela;
                break;
            }
        }
        
        if(idMedicamento == -1){
            printf("Medicamento nao encontrado\n");
        }
    } while (idMedicamento == -1 );

    //inicializa dizendo que o paciente esta tomando o remedio
    novo.tomando = 'S';
    
    listaPrescricao[qtd_prescricao] = novo;
    qtd_prescricao++;
    
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
    while ((c = getcharr()) != '\n' && c != EOF){}
}

int main(){

return 0;
}