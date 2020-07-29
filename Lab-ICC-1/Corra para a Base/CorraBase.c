/*
    ICMC USP - Diógenes Silva Pedro - BCC 020
*/  
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(){
    //Criando variáveis
    int **matrix, line, column, x, y, basex, basey, result;
    double movement;

    //Lendo as entradas
    scanf("%d %d\n", &line, &column);
    scanf("%d %d %lf\n", &x, &y, &movement);

    //Alocando a matriz na heap
    matrix = (int**) malloc (line * sizeof(int*));
    for (int i = 0; i < line; i++){
        matrix[i] = (int*) malloc (column * sizeof(int));
    }

    //Lendo os valores da matriz
    for (int i = 0; i < line; i++){
        for (int j = 0; j < column; j++){
            scanf("%d", &matrix[i][j]);
        }
    }

    //Procurando onde na matriz temos 1, assim acharemos as coordenadas da base
    for (int i = 0; i < line; i++){
        for (int j = 0; j < column; j++){
            if (matrix[i][j] == 1){
                basex = i;
                basey = j;
            }
        }
    }

    //Calculando a distância euclidiana entre o personagem e a base
    result = sqrt(pow(basex-x, 2) + pow(basey-y, 2));
    //Descobrindo se o personagem consegue chegar na base e printando a resposta
    (result <= movement) ? printf("Voce escapou!\n") : printf("Game Over!\n");

    //Liberando a memória heaṕ
    for(int i = 0; i < line; i++){
        free(matrix[i]);
    }
    free(matrix);

    return 0;
}