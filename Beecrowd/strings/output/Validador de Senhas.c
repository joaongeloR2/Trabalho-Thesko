/******************************************************
 * Turma.: EC41A - Algoritmos 1
 * Aluno.: João Angelo Costa de Oliveira
 * Ra....: a2809125
 * Data..: 06/11/2025
 * Descrição: Validador de Senhas (beecrowd)
 ******************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    char senha[100];

    int i = 0,
        maiuscula = 0,
        minuscula = 0,
        numero = 0,
        invalido = 0,
        tam = 0;

    while( fgets( senha , 100 , stdin) != NULL) {
        
        maiuscula = 0;
        minuscula = 0;
        invalido = 0;
        numero = 0;

        tam = strlen(senha);
        
        if ( tam > 0 && senha[tam - 1] == '\n'){
             senha[tam - 1] = '\0';
             tam--;
        }


        if( tam < 6 || tam > 32 ){
            printf("Senha invalida.\n");
            continue;
        }

        for( i = 0 ; i < tam ; i++ ){

            if( senha[i] >= 'A' && senha[i] <= 'Z' ){
                maiuscula++;
            } else {
                if( senha[i] >= 'a' && senha[i] <= 'z' ){
                    minuscula++;
                } else {
                    if( senha[i] >= '0' && senha[i] <= '9' ){
                        numero++;
                    } else {
                        invalido++;
                    }
                }
            }
        }

        if( maiuscula > 0 && minuscula > 0 && numero > 0 && invalido == 0 ){
            printf("Senha valida.\n");
        } else {
            printf("Senha invalida.\n");
        }

        }

    return 0;
}