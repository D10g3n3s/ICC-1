/*
    ICMC USP - Diógenes Silva Pedro - BCC 020
*/
#include <stdio.h>
#include <stdlib.h>

int main(){

    //Definir uma variável inteira e uma real, além da variável auxiliar
    double num, i, resultado = 1;
    int pot;

    //Definindo os valores para a conta
    scanf ("%lf %d", &num, &pot);

    //Loop para fazer a conta exponencial
    for(i=0; i < pot; i++)
    {
        resultado *= num;
      
        if(pot == 0) // Qualquer numero elevado a 0 é igual 1
        {
            resultado = 1;
        }
    }

    //Mostrando o valor para o usuário
    printf("%.4lf\n", resultado);

    return 0;
}