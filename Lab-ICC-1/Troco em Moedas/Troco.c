/*
    ICMC USP - Diógenes Silva Pedro - BCC 020
*/
#include <stdio.h>
#include <stdlib.h>

void Troco(int valor, int moedas[]){
    //Definindo as variáveis que serão utilizadas para realizar a conta do troco
    int real, c50, c25, c10, c5, c1;
    real = valor / 100; //Achando quantas moedas de 1 real que compõem o valor
    moedas[0] = real; //Retornano o valor para a main
    c50 = ((valor % 100) / 50); //Achando quantas moedas de 50 centavos compõem o valor
    moedas[1] = c50;
    c25 = (((valor % 100) % 50) / 25); //Achando quantas moedas de 25 compôem o valor
    moedas[2] = c25;
    c10 = (((valor % 100) % 25) / 10); //Achando quantas moedas de 10 compôem o valor
    moedas[3] = c10;
    c5 = ((((valor % 100) % 25) % 10) / 5); //Achando quantas moedas de 5 compôem o valor
    moedas[4] = c5;
    c1 = (((valor % 100) % 5) / 1); //Achando quantas moedas de 1 compôem o valor
    moedas[5] = c1;

    /*
        Para testar as moedas eu pego o resto da divisão do valor por 100 pois essa é a parte inteira do número, dividindo por 50 eu descubro se uma moeda de 50 centavos satisfaz o 
        problema pois estamos apenas analisando a parte inteira dela, caso não haja nenhuma moeda é por que a divisão foi um número real do tipo 0,x. Para as moedas de 25 centavos eu pego
        o resto da divisão por 100 e o resto da divisão por 50, caso haja resto é pq apenas 1 moeda de 50 centavos n seria capaz de fazer o troco, então divido por 25 para testar se uma 
        moeda de 25 ajudaria e testamos isso olhando a parte real da divisão. Para o 10 pegar o resto da divisão por 100 e o resto da divisão por 25 e divimos esse valor por 10 analisando
        a parte inteira e testando se uma moeda de 10 ajudaria. Para 5 pegamos o resto da divisão por 100 e o resto da divisão por 25 e o resto da divisão por 10 e então divimos esse valor 
        por 5 analisando a parte inteira da divisão para ver se essa ajudaria. Para as moedas de 1 centavo pegamos o resto da divisão por 100 e o resto da divisão por 5, pois caso haja 
        um número inteiro nessa parte apenas a moeda de 1 centavo nos ajudaria, tanto que as moedas de 1 centavo irão de 1 moeda até 4 moedas no máximo.
    */

}


int main(){
    
    //Definindo a variável que guardará o preço
    long int valor;
        
    //Definindo as variáveis que guardarão o resultado da conta feita na função Troco
    int moedas[6];

    //Definindo o preço
    scanf("%ld", &valor);

    //Agora eu mandarei o valor pra cada função e lá será feita a conta para o troco
    Troco (valor, moedas);

    //Imprimindo a resposta do troco
    printf("O valor consiste em %d moedas de 1 real\n", moedas[0]);
    printf("O valor consiste em %d moedas de 50 centavos\n", moedas[1]);
    printf("O valor consiste em %d moedas de 25 centavos\n", moedas[2]);
    printf("O valor consiste em %d moedas de 10 centavos\n", moedas[3]);
    printf("O valor consiste em %d moedas de 5 centavos\n", moedas[4]);
    printf("O valor consiste em %d moedas de 1 centavo\n", moedas[5]);

    return 0;
}