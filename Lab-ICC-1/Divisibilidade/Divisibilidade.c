/*
     ICMC USP - Diógenes Silva Pedro - BCC 020
*/
#include <stdio.h>
#include <stdlib.h>

int main (){

    //Definindo o vetor que guardará os valores, uma variável auxiliar i que ajudará no loop de repetição e uma variável para testar os divisíveis
    int valores[31], i, teste;

    //Loop para receber e guardar os valores no vetor 
    for(i = 0; i < 31; i++){
        scanf("%d", &valores[i]);   
    }

    //Loop para definidir os divisíveis pelo último valor (vetor[30])
    for (i = 0; i < 30; i++){
        teste = valores[i] % valores[30]; //Testando se o número tem resto 0, caso o resto seja 0 o número é divisível
            if (teste == 0){
                printf("%d\n", valores[i]); //Sendo divisível ele printa o valor
            }
    }

    return 0;
}