/*
    ICMC USP - Diógenes Silva Pedro - BCC 020
    Ataques e Tipos
*/

#include <stdio.h>
#include <stdlib.h>

int main(){

    int matrixsize, count = 0, *damage_multiplier, *attack_type, enemy, wich_attack = 0;
    damage_multiplier = (int*) malloc (1 * sizeof(int));
    attack_type = (int*) malloc (1 * sizeof(int));

    //Descobrindo o tamanho da matriz
    scanf("%d", &matrixsize);

    //Criando a matriz
    double **matrix, damage;
    
    //Alocando espaço na memória heap
    matrix = (double**) malloc (matrixsize * sizeof(double*));
    for (int i = 0; i < matrixsize; i++){
        matrix[i] = (double*) malloc (matrixsize * sizeof(double));
    }

    //Lendo os valores da matrix
    for (int i = 0; i < matrixsize; i++){
        for(int j = 0; j < matrixsize; j++){
            scanf("%lf", &matrix[i][j]);
        }
    }
    

    //Lendo os indices e tipos de ataques
    do{

        damage_multiplier = (int*) realloc (damage_multiplier, (count+1) * sizeof(int));
        scanf("%d", &damage_multiplier[count]);
        attack_type = (int*) realloc (attack_type, (count + 1) * sizeof(int));
        if (damage_multiplier[count] != -1) scanf("%d", &attack_type[count]);
        count++;

    } while(damage_multiplier[count-1] != -1) ;

    scanf("%d", &enemy);

    //Calculando os dados com o multiplicador, count - 1, pois está salvo o -1 no último índice do 
    //vetor damage_multiplier, pois ele precisa encotrar o -1 para parar de ler
    for (int i = 0; i < count - 1; i++){
        matrix[attack_type[i]][enemy] *= damage_multiplier[i]; 
    }

    //Vendo qual o maior dano
    damage = -1;
    for (int i = 0; i < count; i++){
        if (matrix[attack_type[i]][enemy] > damage){
            damage = matrix[attack_type[i]][enemy];
            wich_attack = i;
        }
    }

    //Printando o resultado para o usuário
    printf("O melhor ataque possui indice %d e dano %.2lf\n", wich_attack, damage);

    //Liberando o espaço da memória heap
    for (int i = 0; i < matrixsize; i++){
        free(matrix[i]);
    }
    free(matrix);
    free(damage_multiplier);
    free(attack_type);

    return 0;
}