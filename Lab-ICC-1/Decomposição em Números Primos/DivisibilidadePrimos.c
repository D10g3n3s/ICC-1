/*
    ICMC USP - Diógenes Silva Pedro - BCC 020
*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main (){

    //Definindo as variáveis 
    int num, primo, vezes; //num o número digitado pelo usuário, primo para guardar o n° primo testado na conta e vezes para guardar quantas vezes aquele n° primo foi usado

    //Recebendo o valor escolhido pelo usuário
    scanf("%d", &num);

    //Definindo o primeiro número primo 2, após esse o programa irá incrementando e testando se o número servirá para decompor o número digitado
    primo = 2;

    //Calculando os primos que formam o número digitado com um laço de repetição
    while (num > 1){ //Definindo que enquanto o num for > 1 o laço deve acontecer, pois o num ainda é divisível por algo
        vezes = 0; //Definindo o vezes = 0 dentro do laço para que a cada vez que o programa faça o laço o contador resete
        while (num % primo == 0){ //Definindo que enquanto o resto da divisão do número pelo primo for 0 ele deve realizar o laço, caso o resto seja != 0, o número primo da vez não serve
            vezes++;
            num = num / primo;
        } 
        //Condicionando que se o vezes != 0, indica que apenas mostraremos na tela se o n° primo foi mesmo utilizado para dividir o n° definido pelo usuário
        if (vezes != 0){ 
            //Printando para o usuário o n° primo que foi utilizado e quantas vezes ele foi utilizado para dividir o n° escolhido
            printf("%d %d\n", primo, vezes); 
        }
        //Aumentando o n° primo para que o laço continue até que o n° digitado pelo usuário seja igual a 1, caso o primo++ resulte em um n° que não foi usado o código apenas adicionará 1
        //a essa variável e testará ela novamente até obtermos num = 1
        primo++;
    }

    return 0;
}