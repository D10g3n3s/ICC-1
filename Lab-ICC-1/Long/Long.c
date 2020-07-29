/*
    ICMC USP - Diógenes Silva Pedro - BCC 020
*/
#include <stdio.h>
#include <stdlib.h>

int main(){

    //Definindo a variável que guardará o valor digitado pelo usuário
    long valor;

    //Recebendo o valor digitado pelo usuário 
    scanf("%ld", &valor);

    //Criando um ponteiro como unsigned para que todos os bits estejam livres para mostrar o endereço 
    unsigned char *printar;
       
    //Fazendo o ponteiro receber o endereço da variável
    printar = (unsigned char *) &valor;

    //Loop que printa cada um dos endereços bos bytes
    for (int i = 0; i < 8; i++){
        printf("%x\n", printar[i]);
    }

    return 0;
}