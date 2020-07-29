/*
    ICMC USP - Diógenes Silva Pedro - BCC 020
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(){
    //Definindo as variáveis
    char direcao[200]; //Vetor direcao receberá os comandos
    int qntordens = 0, i; //resto será utilizado para calcular a direção do robo qntordens definirá os "movimentos" do robo e a variável i auxilará o loop
 
    //Recebendo os comandos para o robo
    scanf("%s", direcao);

    //Laço de repetição para checar os comandos dados ao robo e movimentá-lo
    for (i = 0; i < strlen(direcao); i++){
        if (direcao[i] == 'D'){
            qntordens = qntordens + 1; //Ao aumentar 1 no qntordens o robo está virando para a direita
        }

        if (direcao[i] == 'E'){
            qntordens = qntordens - 1; //Ao diminuir 1 no qntordens o robo está virando para a esquerda
        }
    }

    /*
    Agora definiremos para onde o robo está apontando, utilizando do número inteiro salvo em qntordens, como temos 4 direções e o robo começa em Leste, essa direção representa o 1, Sul
    representa 2, Oeste 3 e Norte 4. Com cada direção definida só precisamos dividir o qntordens por 4 e olhar para o resto, sendo 1 o robo aponta para Leste, 2 aponta para Sul e assim em
    diante, da mesma lógica como fazemos com números imaginários com i^6 por exemplo onde i^6 equivale a i^2, pois 6/4 resta 2.
    */

    if (qntordens%4 == 1 || qntordens%4 == -3){
        printf("Leste\n");
    }
    else if (qntordens%4 == 2 || qntordens%4 == -2){
        printf("Sul\n");
    }
    else if(qntordens%4 == 3 || qntordens%4 == -1){
        printf("Oeste\n");
    }
    else {
        printf("Norte\n");
    }

    return 0;
}