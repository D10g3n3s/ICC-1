/*
    ICMC USP - Diógenes Silva Pedro - BCC 020
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main (){

    //declarando o variável que vai guardar o tamanho do vetor
    int n;

    //declarando as variáveis que guardarão o maior e o menor valor
    int max, min;

    //descobrindo o tamanho do vetor
    scanf("%d", &n);

    //definindo o vetor onde ficarão guardados os valores
    int valores[n];

    //definido a variável auxiliar do loop
    int i;

    //definindo um loop onde o usuário colocará os valores
    for (i = 0; i < n; i++){
        //lendo e armazenando os valores dentro do vetor
        scanf("%d", &valores[i]);
        //a medida que o valor roda a variável i é incrementada em 1, trocando a "casa" do vetor
    }

    //criando um segundo loop para comparar os valores e definir o maior e o menor
    for (i = 0; i < n; i++){
        //na primeira passagem pelo loop eu defino, um valor que já existe no vetor, nesse caso o 1° apenas para tirar o lixo da memória
        if (i == 0) {
          max = valores[i];
          min = valores[i];
        }
        //aqui estou testando qual o maior valor, caso o valor atual do vetor seja maior que o valor já antes definido na variável max ele então o muda para o atual valor do vetor valores
        if (valores[i] > max){
            max = valores[i];
        }
        //aqui estou testando qual o menor valor, caso o valor atual do vetor seja menor que o valor já antes definido na variável min ele então o muda para o atual valor do vetor valores
        if (valores[i] < min){
            min = valores[i];
        }
      }

    //printando o resultado, mostrando para o usuário qual o valor máximo e o valor mínimo do vetor
    printf("max: %d\n", max);
    printf("min: %d\n", min);

    return 0;
}