/******************************************************
 * Turma.: 
 * Aluno.: João Angelo Costa de Oliveira
 * Ra....: a2809125
 * Data..: __/__/____
 * Descrição: __________________________________________
 ******************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    int num = 0,
        i = 0,
        j = 0,
        s = 0;


    char senha[52],
         oculta[52];

    scanf("%d", &num);
    getchar();

    for( i = 0 ; i < num ; i++ ){

        fgets( senha , 52 , stdin );
        
        if( senha[0] >= 'a' && senha[0] <= 'z' ){
            oculta[j] = senha[0];
            j++;
        }

        for( s = 0 ; senha[s] != '\0' ; s++ ){
            if( senha[s] == ' ' ){
                if( senha[ s + 1 ] >= 'a' && senha[ s + 1 ] <= 'z' ){
                    oculta[j] = senha[ s + 1 ];
                    j++;
                }
            }
        }

        oculta[j] = '\0';
        j = 0;

        printf("%s\n", oculta);
    }



    return 0;
}