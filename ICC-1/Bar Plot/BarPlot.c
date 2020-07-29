/*
    ICMC USP - Diógenes Silva Pedro - BCC 020
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(){

    //Definindo as variáveis, n = número de barras, m = número de dados, valor = valor a ser recebido
    int n, m, valor;

    //Recebendo os valores de n e m 
    scanf("%d", &n); 
    scanf("%d", &m);

    //Definindo o vetor frequência
    int *freq;

    //Alocando os dados do ponteiro dentro da memória heap e inicializando todos os valores como 0, para evitar com que a memória tenha lixo
    freq = (int *) calloc (n, sizeof(int));

    /*
    Recebemos o valor e então colocamos esse valor dentro do vetor frequência, assim qnd o valor for 1, no vetor frequência[1] será adicionado 1 unidade, para representar que o valor 1 
    apareceu 1 vez e assim por diante com todos os valores
    */
    for (int i = 0; i < m; i++){
        scanf("%d", &valor);    
        freq[valor]++;
    }

    /*
    Printando na tela com as hashtag quantas vezes cada número apareceu, para isso o primeiro for será o valor do dado a ser mostrado inicialmente e o segundo for printará o hashtag o
    número de vezes que o valor, demonstrado pela variável i, apareceu após a entrada dos dados fornecida pelo usuário
    */
    for (int i = 0; i < n; i++){
        printf("%d - ", i);
        for (int j = 0; j < freq[i]; j++){
            printf("#");
        }
        printf("\n");
    }

    //Liberando a memória heap que foi utilizada para guardar a frequência dos valores fornecidos pelo usuário
    free (freq);

    return 0;
}