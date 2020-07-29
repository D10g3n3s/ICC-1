/*
    ICMC USP - Diógenes Silva Pedro - BCC 020
    Programa que faz o padding(adição de bordas) de imagens
*/

#include <stdio.h>
#include <stdlib.h>

int main(){

    //Criando variáveis
    int **image, **padimage, width, height, edge;

    //height = quantidade de linhas, width = quantidade de colunas
    //Lendo o tamanho da imagem
    scanf("%d %d", &width, &height);

    //Alocando espaço para a imagem original
    image = (int**) malloc (height * sizeof(int*));
    for (int i = 0; i < height; i++){
        image[i] = (int*) malloc (width * sizeof(int));
    }

    //Lendo os valores da iamgem original
    for (int i = 0; i < height; i++){
        for (int j = 0; j < width; j++){
            scanf("%d", &image[i][j]);
        }    
    }

    //Lendo o tamanho da borda
    scanf("%d", &edge);

    //Alocando a memória para a imagem com bordas
    padimage = (int**) calloc ((height+(edge*2)), sizeof(int*));
    for (int i = 0; i < (height+(edge*2)); i++){
        padimage[i] = (int*) calloc ((width+(edge*2)), sizeof(int));
    }

    //Copiando os termos da imagem original para a imagem com bordas
    for (int i = edge; i < height+edge; i++){
        for (int j = edge; j < width+edge; j++){
            padimage[i][j] = image[i-edge][j-edge];
        }
    }

    //Printando a imagem após adição das bordas
    for (int i = 0; i < (height+(edge*2)); i++){
        for(int j = 0; j < (width+(edge*2)); j++){
            printf("%d ", padimage[i][j]);
        }
        printf("\n");
    }

    printf("\n");

    //Printando a imagem original
    for (int i = 0; i < height; i++){
        for(int j = 0; j < width; j++){
            printf("%d ", image[i][j]);
        }
        printf("\n");
    }

    //Desalocando a memória heap
    for (int i = 0; i < height; i++){
        free(image[i]);
    }
    free(image);

    for (int i = 0; i < (height+(edge*2)); i++){
        free(padimage[i]);
    }
    free(padimage);

    return 0;
}