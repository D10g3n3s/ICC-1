/*
    ICMC USP - Diógenes Silva Pedro - BCC 020
*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(){

    //Declarando as variáveis que definem a quantidade de números inteiros a ser impresso e quais serão os multiplos a achar, além de variáveis para calcular
    int n, i, j, mt = 0, count = 0; //Definindo 0 para as variáveis que guardarão os números inteiros para excluir o lixo dentro da memória das variáveis

    //Definindo o número de inteiros a ser apresentado
    scanf("%d", &n);
    //Definindo os números para o teste
    scanf("%d", &i);
    scanf("%d", &j);

    while (count < n){
        //Verificaremos quais são os números multiplos de i e de j
        if (mt%i == 0 || mt%j == 0){
            printf("%d\n", mt); //Imprimindo os múltiplos na tela
            count += 1; //Adicionando 1 a contagem, para que a repetição do while pare qnd chegar a 6 números
        }
            mt += 1; //Estamos adicionando 1 no número de teste mt, para que a cada vez que o programa repita o while ele consiga testar se o número é multiplo ou não dos números i e j
    }



    return 0;
}
