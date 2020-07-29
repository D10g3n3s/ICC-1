/*
    ICMC USP - Diógenes Sivla Pedro - BCC 020
*/
#include <stdio.h>
#include <stdlib.h>

int main(){
    
    //Definindo as variáveis inteiras, as reais e o vetor
    double tempo[12], mediat; //o vetor tempo guardará o tempo médio de cada mês, a variável mediat guardará o mês com maior tempo médio de uso
    int mes = 0, i; //A variável mes guardará o mês com maior tempo médio de uso e a variável i é uma variável auxiliar para o loop
    //A variável mes recebe 0 para limpar o lixo guardado na memória

    //Lendo o tempo médio de uso de cada mês, com o uso de um laço de repetição for
    for (i = 0; i < 12; i++){
        scanf("%lf", &tempo[i]);
    }

    //Fazendo a comparação com um laço de repetição para ver qual mês teve mais tempo médio de uso, definindo então o mês com mais tempo de uso e qual foi esse tempo de uso
    for (i = 0; i < 12; i++){
        if (i == 0){
            mediat = tempo[i];
        }

        if (tempo[i] > mediat){
            mediat = tempo[i];
            mes = i + 1;
        }
    }

    //Mostrando para o usuário o mês e a média de tempo usado nesse respectivo mês, sendo que o tempo mostrado para o usuário é o tempo de maior média entre todos os meses
    printf("%d %.2lf\n", mes, mediat);  

    return 0;
}