/******************************************************
 * Turma.: EC41A - Algoritmos 1
 * Aluno.: João Angelo Costa de Oliveira e ......................
 * Ra....: a2809125 e ...........................
 * Data..: 17/11/2025
 * Descrição: Trabalho Final de Algoritmos 01.
 ******************************************************/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>


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
    TpResidente residente;
    char medicamento[50];
    int dosagem;
    int periodo;
    int estoque;
    char tomando;
} TpMedicamento;


//struct administração
typedef struct Administração {
    int identificador;
    TpMedicamento medicamento;
    TpData dataAdmin;
    int horaRemedio;
    int idEnfermeiro;
} TpAdimin;


//FUNÇÕES:


//buscar residente pelo nome
void BuscarResidente( char nome[] ){
    if( nome[])
}


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
    if( tamanho <= 11 && tamanho >= 12 ){
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
    char nome[50];
    char telefone[15];
    TpData data;
    
    fgets( nome , 50 , stdin );
    
    //verificação do nome
    while( ValNome (nome) == 0 ){
        printf("Nome invalido. Digite novamente: ");
        
        fgets( nome , 50 , stdin );
    }
    
    fgets( telefone , 15 , stdin );
    
    //verifica o telefone
    while( ValTelefone( telefone ) == 0 ){
        printf("Telefone invalido. Digite novamente: ");
        
        fgets( telefone , 15 , stdin );
    }
    
    scanf("%d %d %d", &data.dia, &data.mes, &data.ano);
    
    //verificando a data
    while( ValData( data ) == 0 ){
        printf("Data invalida. Digite novamente (dia, mes, ano): ");
        
        scanf("%d %d %d", data.dia, data.mes, data.ano);
    }
    printf("Cadastro realizado com sucesso!\n");
}




int main(){

return 0;
}