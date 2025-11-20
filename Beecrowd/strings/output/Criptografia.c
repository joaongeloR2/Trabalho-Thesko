/******************************************************
 * Turma.: EC41A - Algoritmos 1
 * Aluno.: João Angelo Costa de Oliveira
 * Ra....: a2809125s
 * Data..: 31/10/2025
 * Descrição: Criptografia
 ******************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    char senha[1002];

    int num = 0,
        i = 0,
        j = 0,
        temp = 0,
        s = 0;

    scanf("%d", &num);
    getchar();

    //mover a letra 3 casas para a direita

    for( i = 0 ; i < num ; i++ ){
        fgets( senha , 100 , stdin );
        senha[ strcspn( senha , "\n" )] = 0;

        for( j = 0 ; j < (int)strlen(senha) ; j++ ){
            if(( senha[j] >= 'A' && senha[j] <= 'Z' ) || ( senha[j] >= 'a' && senha[j] <= 'z' )){
                senha[j] = senha[j] + 3;
            }
        }
        
        //inverter a palavra
        
        s = strlen(senha) - 1 ;
        
        for( j = 0 ; j < (int)strlen(senha) / 2 ; j++ ){
                temp = senha[j];
                senha[j] = senha[s];
                senha[s] = temp;
                s--;   
            }
        
        //da metade em diante uma casa para a esquerda
    
        for( j = strlen(senha) - 1 ; j >= (int)strlen(senha) / 2 ; j-- ){
            senha[j] = senha[j] - 1;
        }
        printf("%s\n", senha);
    }





    return 0;
}