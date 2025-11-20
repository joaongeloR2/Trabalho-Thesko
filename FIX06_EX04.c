/******************************************************
 * Turma.: EC41A - Algoritmos 1
 * Aluno.: João Angelo Costa de Oliveira
 * Ra....: a2809125
 * Data..: 27/10/2025
 * Descrição: Uma escola deseja armazenar as notas dos alunos em uma matriz. 
    Cada linha representa um aluno e cada coluna representa uma das três provas 
    aplicadas no semestre.
    Você deve escrever um programa que:

 - Leia as notas de 5 alunos, cada um com 3 notas 
   (números reais de 0.0 a 10.0).
 - Calcule a média de cada aluno.
 - Exiba a média de cada aluno com 2 casas decimais.
 ******************************************************/

#include <stdio.h>
#include <stdlib.h>
#define LIN 5
#define COL 3

int main() {
// estabelicimento de variaveis
    float matriz[LIN][COL],
          media = 0;

    int i = 0,
        j = 0;

// nota dos alunos
    for( i = 0 ;  i < LIN ; i++ ){
        for( j = 0 ; j < COL ; j++ ){
            scanf("%f", &matriz[i][j] );
        }
    }

// tabela com a media dos alunos
    printf("\n*==============================*\n");

    for( i = 0 ;  i < LIN ; i++ ){
        for( j = 0 ; j < COL ; j++ ){
            media += matriz[i][j];
        }
        printf("    Media do aluno %d: %.2f\n", i + 1, media / 3 );
        media = 0;
    }

     printf("*==============================*\n");

    return 0;
}