/******************************************************
 * Turma.: EC41A - Algoritmos 1
 * Aluno.: João Angelo Costa de Oliveira
 * Data..: 22/10/2025
 * Exxercicio: Coluna na Matriz (Beecrowd)
 ******************************************************/

#include <stdio.h>
#include <stdlib.h>
#define LIN 12
#define COL 12

int main() {
    int i = 0,
        j = 0,
        escolha = 0;

    char T = 'x';

    float matriz[LIN][COL],
          soma = 0,
          media = 0;
    
    scanf("%d", &escolha);
          
    scanf(" %c", &T);
          
          for( i = 0 ; i < LIN ; i++ ){
        for( j = 0 ; j < COL ; j++ ){
            scanf("%f", &matriz[i][j]);
        }
    }

    for( i = 0 ; i < LIN ; i++ ){
        soma += matriz[i][escolha];
    } 

    media  = soma / LIN;

    if( T == 'S' ){
        printf("%.1f\n", soma);
    } else {
        if( T == 'M' ){
            printf("%.1f\n", media);
        }
    }
    return 0;
}
