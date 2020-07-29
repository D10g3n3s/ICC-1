/*
    ICMC USP - Diógenes Silva Pedro - BCC 020
*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main (){

    //Definindo a variável que guardada o número de trabalhos e a variável auxilar para os loops
    int n, i;
    
    //Descobrindo o número de trabalhos
    scanf("%d", &n);

    //Definindo o vetor que guardará as notas dos trabalhos, uma variável temporária para ajudar na média final e definindo a média final
    double notas[n], temp = 0, mediafinal = 0;

    //Loop de repetição que salva as notas
    for (i = 0; i < n; i++){
        scanf("%lf", &notas[i]);
    }

    //Loop para fazer utilizar as notas e achar 1 único denominador antes da média final 
    for (i = 0; i < n; i++){
        temp += (1/(notas[i] + 1));
    }

    //Cálculo da média final e printando para o usuário após a conta
    mediafinal = ((n/temp) - 1);
    printf("%.2lf\n", mediafinal);

    return 0;
}