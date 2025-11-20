/******************************************************
 * Turma.: EC41A - Algoritmos 1
 * Aluno.: João Angelo Costa de Oliveira
 * Ra....: a2809125
 * Data..: 23/10/2025
 * Descrição: Escreva um programa em Linguagem C que simule 
 *  a venda de ingressos para uma sessão de cinema, sabe-se 
 *  que o cinema possui 150 poltronas, dispostas em 15 filas 
 *  de 10 poltronas cada. Representado da seguinte maneira.: 
 *  0 - poltrona vazia
 *  1 - pagante inteira
 *  2 - pagante meia
 ******************************************************/

#include <stdio.h>
#include <stdlib.h>
#define LIN 3
#define COL 3

// estabelecimento de variaveis
int main() {
    int matriz[LIN][COL],
        i = 0,
        j = 0,
        ocupadas = 0,
        meias = 0,
        vazias = 0,
        inteiras = 0;

    int cordenadaA = 0,
        cordenadaB = 0,
        ingresso = 0,
        z = 0;

    float valor = 0;

// introdução de assentos ocupados
    for( i = 0 ; i < LIN ; i++ ){
        for( j = 0 ; j < COL ; j++ ){
            scanf("%d", &matriz[i][j]);
        }
    }

// verificação de ingresso meia/inteira/vazia
    for( i = 0 ; i < LIN ; i++ ){
        for( j = 0 ; j < COL ; j++ ){
            if ( matriz[i][j] == 0 ){
                vazias++;
            } else {
                if ( matriz[i][j] == 1 ){
                    inteiras++;
                } else {
                    meias++;
                }
            }
        }
    }

// valor arrecadado na sessão 
    valor = (meias * 9) + (inteiras * 18);
    ocupadas = meias + inteiras;

    printf("\n*==================================*\n\n");

// troca de 0 1 2 por  X x
    for( i = 0 ; i < LIN ; i++ ){
        for( j = 0 ; j < COL ; j++ ){
            if( matriz[i][j] == 1 ){
                if( j == 0 ){
                    printf("        [ X ] ");
                } else {
                    printf("[ X ] ");
                }
            } else {
                if( matriz[i][j] == 2 ){
                    if( j == 0 ){
                        printf("        [ x ] ");
                    } else {
                        printf("[ x ] ");
                    }
                }
            }
            if( matriz[i][j] == 0 ){
                if( j == 0 ){
                    printf("        [   ] ");
                } else {
                    printf("[   ] ");
                }
            } 
        }
        printf("\n");
    }

// impressão da tabela
    printf("\n*==================================*\n");
    printf("    Ocupacao total....: %d / %d\n",  ocupadas, LIN * COL );
    printf("    Poltronas vazias..: %d\n", vazias );
    printf("    Pagantes inteira..: %d\n", inteiras );
    printf("    Pagantes meia.....: %d\n", meias );
    printf("    Total de vendas.R$: %.2f\n", valor );
    printf("*==================================*\n\n");

// recebendo novos clientes
    do {
        printf("Qual o assento?\n");
        scanf("%d %d", &cordenadaA, &cordenadaB);

        if( matriz[cordenadaA][cordenadaB] != 0 ){
            printf("Poltrona ocupada.\n");
            continue;
        }

// analisando qual ingresso 
        printf("Meia ou Inteira?\n");
        scanf("%d", &ingresso);

        if( ingresso == 1 ){
            inteiras++;
            matriz[cordenadaA][cordenadaB] = 1;
            z++;
        } else {
            meias++;
            matriz[cordenadaA][cordenadaB] = 2;
            z++;
        }

    } while ( z < 5 );

// recalculando o valor arrecadado pela sessão
    valor = (meias * 9) + (inteiras * 18);
    ocupadas = meias + inteiras;

// recalculando poltronas vazias
    vazias = 0;
    for( i = 0 ; i < LIN ; i++ ){
        for( j = 0 ; j < COL ; j++ ){
            if( matriz[i][j] == 0 ){
                vazias++;
            }
        }
    }

// reorganizando os assentos
    printf("\n*==================================*\n\n");

// sala atualizada
    for( i = 0 ; i < LIN ; i++ ){
        for( j = 0 ; j < COL ; j++ ){
            if( matriz[i][j] == 1 ){
                if( j == 0 ){
                    printf("        [ X ] ");
                } else {
                    printf("[ X ] ");
                }
            } else {
                if( matriz[i][j] == 2 ){
                    if( j == 0 ){
                        printf("        [ x ] ");
                    } else {
                        printf("[ x ] ");
                    }
                }
            }
            if( matriz[i][j] == 0 ){
                if( j == 0 ){
                    printf("        [   ] ");
                } else {
                    printf("[   ] ");
                }
            } 
        }
        printf("\n");
    }

// tabela atualizada
    printf("\n*==================================*\n\n");
    printf("           Tabela Atualizada        \n");
    printf("\n*==================================*\n");
    printf("    Ocupacao total....: %d / %d\n",  ocupadas, LIN * COL );
    printf("    Poltronas vazias..: %d\n", vazias );
    printf("    Pagantes inteira..: %d\n", inteiras );
    printf("    Pagantes meia.....: %d\n", meias );
    printf("    Total de vendas.R$: %.2f\n", valor );
    printf("*==================================*\n\n");

    return 0;
}