/*
    ICMC USP - Diógenes Silva Pedro - BCC 020
*/
#include <stdio.h>
#include <stdlib.h>

//Criando a função que lerá o número de trabalhos
int readInt(){

    //Declaração de variáveis, recebimento do valor e retorno do valor para a função main
    int nt;
    scanf("%d", &nt);
    return nt;
}

//Criando a função que receberá os valores de cada trabalho e calcular a média final
double readDouble(int nt){

    //Declaração das variáveis
    double temp, mediaf;
    double *notas;

    //Alocando a memória heap para que as notas sejam salvas lá
    notas = (double *) malloc (nt * sizeof(double));

    //Loop que recebe os valores das notas
    for (int i = 0; i < nt; i++){
        scanf("%lf", &notas[i]);
    }

    //Loop que calcula o denominador da função do cálculo da média final 
    for (int i = 0; i < nt; i++){
        temp += (1/(notas[i]+1));
    }

    //Cálculo da média final
    mediaf = ((nt/temp) -1);

    //Desalocando o espaço na memória heap
    free (notas);

    //Retornando o valor da média final para a função main
    return mediaf;
}

//Função que printará na tela a média final do aluno
void printDouble(double mediaf){

    printf("%.2lf\n", mediaf);

}

int main (){

    //Chamando as funções e declarando variáveis que receberão os valores
    int nt = readInt();
    double mediaf = readDouble(nt);
    printDouble(mediaf);

    return 0;
}