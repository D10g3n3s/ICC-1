/*
    ICMC USP - Diógenes Silva Pedro - BCC 020
    Programa de mistura de cores
*/

#include <stdio.h>
#include <stdlib.h>

//Função que le a matriz
int** readMatrix (int **color_matrix){

    //Lendo as entradas e salvando na matriz
    for (int i = 0; i < 6; i++){
        for (int j = 0; j < 3; j++){
            scanf("%d", &color_matrix[i][j]);  
        }
    }

    return color_matrix;
}

//Função que mistura as cores
int** mixColors(int **color_matrix, int color1, int color2, int wich_color){
    int c1[3], c2[3];
    
    //Descobrindo o valor que será somado para a cor, valores referentes a 1° cor
    for (int i = 0; i < 3; i++){   
        c1[i] = (color_matrix[color1][i]) / 2;   
    }

    //Descobrindo o valor que será somado para a cor, valores referentes a 2° cor
    for (int i = 0; i < 3; i++){   
        c2[i] = (color_matrix[color2][i]) / 2;   
    }

    //Misturando as cores
    for (int i = 0; i < 3; i++){
        color_matrix[wich_color][i] = c1[i] + c2[i] + color_matrix[wich_color][i];
        if (color_matrix[wich_color][i] > 255){
            color_matrix[wich_color][i] = 255;
        }
    }

    return color_matrix;
}

//Função que printa a matriz
void startColors(int **color_matrix){
    //Mostrando a matriz inicialmente
    printf("Start:\n");
    for (int i = 0; i < 6; i++){
        printf("Color(%d): [\t%d\t%d\t%d\t]\n", i, color_matrix[i][0], color_matrix[i][1], color_matrix[i][2]);
    }
}

//Função que printa a matriz
void resultColors(int **color_matrix){
    //Mostrando a matriz após a mistura de cores
    printf("\nResult:\n");
    for (int i = 0; i < 6; i++){
        printf("Color(%d): [\t%d\t%d\t%d\t]\n", i, color_matrix[i][0], color_matrix[i][1], color_matrix[i][2]); 
    }
}

int main(){

    //Criando variáveis
    int color1, color2, wich_color, **color_matrix;

    //Alocando a matrix na memória heap
    color_matrix = (int**) malloc (6 * sizeof(int*));
    for (int i = 0; i < 6; i++){
        color_matrix[i] = (int*) malloc (3 * sizeof(int));
    }

    //Lendo quais cores deverão ser misturadas e em qual cor deve ser adicionado a mistura
    scanf("%d %d %d", &color1, &color2, &wich_color);

    //Lendo os valores da matrix
    color_matrix = readMatrix(color_matrix);

    //Imprimindo a matriz antes da mudança
    startColors(color_matrix);

    //Fazendo a mistura de cores
    color_matrix = mixColors(color_matrix, color1, color2, wich_color);

    //Imprimindo a matriz pós mudança de cores
    resultColors(color_matrix);

    //Desalocando a memória heap
    for (int i = 0; i < 3; i++){
        free(color_matrix[i]);
    }
    free(color_matrix);

    return 0;
}