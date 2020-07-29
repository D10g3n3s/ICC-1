/*
    ICMC USP - Diógenes Silva Pedro - BCC 020
    Programa que cálcula o determinante
*/  
#include <stdio.h>
#include <stdlib.h>

//Função que calcula e printa o determinante de uma matriz bidimensional de tamanho 1x1
void Det1x1(int **matriz, int nl){
    //O determinante recebe ao valor digitado na matriz unidimensional, que nesse caso é o próprio número digitado
    int det = matriz[0][0];

    //Printando o determinante para o usuário
    printf("O determinante da matriz de entrada equivale a %d e tem ordem %d\n", det, nl);
}

//Função que calcula e printa o determinante de uma matriz bidimensional de tamanho 2x2
void Det2x2(int **matriz, int nl){
    int det;

    //Fazendo o cálculo do determinante
    det = ((matriz[0][0] * matriz [1][1]) - (matriz[0][1] * matriz[1][0]));

    //Printando o determinante para o usuário
    printf("O determinante da matriz de entrada equivale a %d e tem ordem %d\n", det, nl);
}

//Função que calcula e printa o determinante de uma matriz bidimensional de tamanho 3x3
void Det3x3 (int **matriz, int nl){
    int det = 0;

    //Loop que calcula o determinante da matriz
    for (int i = 0; i < nl; i++){
        det += matriz[0][i] * (matriz[1][(i+1)%3] * matriz[2][(i+2)%3] - matriz[2][(i+1)%3] * matriz[1][(i+2)%3]);
    }
    /*
    Para a matriz | a b c |
                  | d e f |
                  | g h i |
    Podemos simplificá-la como a*(ei - fh) + b*(di-fg) + c*(dh - eg)
    Pensando que nossa matriz 3x3 começa na linha 0 e coluna 0 e que os "números" a, b e c, são os números em evidência, temos que andar apenas para a direita nessa linha, ou seja,
    +1. Para os valores dentro dos parenteses sabemos que eles estão na linha 1 e 2, para eles também só precisamos andar para a direita, então divimos por 3 pegando seu resto para
    que o valor da linha sempre esteja entre 0 e 2. 
    Fazemos isso para todas os "números" a, b e c, somando todos esses valores a uma variável determinante. No final do loop teremos o valor do determinante.
    */

    //Printando o determinante para o usuário
    printf("O determinante da matriz de entrada equivale a %d e tem ordem %d\n", det, nl);
}

int main(){

    //Definindo as variáveis que guardarão n° de linha, n° de colunas e o valor do determinante
    int nl = 0, nc = 0;

    //Recebendo os valores do n° de linhas e de n° de colunas
    scanf("%d", &nl);
    scanf("%d", &nc);

    //Criando o ponteiro da matriz
    int **matriz;

    //Alocando na memória heap n vetores, que serão minhas n linhas
    matriz = (int **) malloc (nl * sizeof(int *)); //sizeof(int*) = 8 bytes por ser um ponteiro

    //Definindo o tamanho dos n vetores guardarão os números de cada linha
    for (int i = 0; i < nl; i++){
        matriz[i] = (int *) malloc (nc * sizeof(int)); 
    }

    //Loop para receber os valores da matriz
    if (nl == 1 && nc == 1) {
        scanf("%d", &matriz[0][0]);
    }

    else if ((nl == 2 && nc == 2) || (nl == 3 && nc == 3)){
        for (int i = 0; i < nl; i++){
            for (int j = 0; j < nc; j++){
                scanf("%d", &matriz[i][j]);  
            }
        }
    }

    //Testando se a matriz é possível de se calcular o determinante    
    if (nl == 1 && nc == 1){
        Det1x1(matriz, nl);
    }
    
    else if (nl == 2 && nc == 2){
        Det2x2(matriz, nl);
    }

    else if (nl == 3 && nc == 3){
        Det3x3(matriz, nl);
    }

    else if (nl != nc){
        printf("A matriz de entrada nao possui determinante!\n");
    }

    else {
        printf("Entradas invalidas!\n");
    }

    //Desalocando a memória heap
    for (int i = 0; i < nc; i++) free(matriz[i]);
    free (matriz);

    return 0;
}