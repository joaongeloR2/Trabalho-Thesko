/******************************************************
 * Turma.: EC41A - Algoritmos 1
 * Aluno.: João Angelo Costa de Oliveira
 * Ra....: a2809125
 * Data..: __/__/____
 * Descrição: __________________________________________
 ******************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    int test = 0,
        leds = 0,
        i = 0,
        j = 0,
        digito = 0;
    char num[102];

    scanf("%d", &test);

    for( i = 0 ; i < test ; i++ ){
        scanf("%s", num);
        for( j = 0 ; j < (int)strlen(num) ; j++ ){
            digito = num[j] - '0';
            if( digito == 1 ){
                leds += 2;
            }
            if( digito == 2 || digito == 3 || digito == 5 ){
                leds += 5;
            }
            if( digito == 4 ){
                leds += 4;
            }
            if( digito == 6 || digito == 9 || digito == 0 ){
                leds += 6;
            }
            if( digito == 7 ){
                leds += 3;
            }
            if( digito == 8 ){
                leds += 7;
            }
        }
        printf("%d leds\n", leds );
        leds = 0;
    }



    return 0;
}       