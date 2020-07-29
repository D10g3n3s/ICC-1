/*
     ICMC USP - Diógenes Silva Pedro - BCC 020
*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

int main(){

    //Definindo o vetor para o número binário  
    char bin[31];

    //Definindo a variável auxiliar i e o variável para o número decimal
    int i, q, decimal = 0;

    //Lendo o binário
    scanf("%s", bin);
    
    //Achando o qual o tamanho da string
    i = strlen(bin);    

    //Usando um loop para pegar cada caracter binário e transformar no seu equivalente decimal
    for (q = 0; q < i; q++){
        if (bin[q] == '1') {
            decimal += (pow(2,((i - 1)- q))); 
        }
    }
 /*
    O loop acima está somando na variável decimal os valores transformados de binário para decimal, o comando strlen está pegando o tamanho da string e salvando numa variável int,
    criei a variável inteira q e utilizei ela para o for, na linha 26, o decimal está sendo somado a ele mesmo + o (pow(2,((i - 1)- q))), aqui a variável i é definida com o tamanho
    da string 
 */
    printf("%d\n", decimal);

    return 0;
}