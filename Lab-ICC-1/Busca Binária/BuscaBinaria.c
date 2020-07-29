/*
    ICMC USP - Diógenes Silva Pedro - BCC 020
    Programa que faz o algoritmo de busca binária
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

//Função que le os dados
void readElements(int *elements, int lenght){
    for (int i = 0; i < lenght; i++){
        scanf("%d", &elements[i]);
    }
}

//Função que ordena os dados
void bubbleSort(int *arr, int n){
    int i, j, temp;
    for(i = 0; i < n; i++){
        for(j = 0; j < n-i-1; j++){
            if( arr[j] > arr[j+1]){
                // swap the elements
                temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
            } 
        }
    }
}

//Função que faz a busca binária recursivamente
int binarySearch(int *elements, int lo, int hi, int key){
    if (hi >= lo) { 
        int mid = lo + (hi - lo) / 2; 
  
        //Caso o elemento seja o próprio elemento do meio 
        if (elements[mid] == key) return mid; 
   
        //Caso o elemento seja menor que o termo do meio, então o elemento só pode estar presente no
        //suboconjunto a direita
        if (elements[mid] > key) return binarySearch(elements, lo, mid - 1, key); 
  
        //O elemento pode só pode estar presente no subconjunto a direita 
        return binarySearch(elements, mid + 1, hi, key); 
    } 
  
    // Caso o elemento não esteja presente no conjunto
    return -1; 
}

int main(){

    //Criando as variáveis
    int lenght, key, *elements, result;
    scanf("%d %d", &lenght, &key);
    //Armazenando na memória heap
    elements = (int*) malloc (lenght * sizeof(int));

    //Para que possamos realizar uma busca binária precisamos primeiro armazenar todos os nossos
    //dados, depois precisamos ordená-los e 

    //Lendo os elementos
    readElements(elements, lenght);
    //Ordenando os elementos
    bubbleSort(elements, lenght);
    //Busca binária
    result = binarySearch(elements, 0, lenght-1, key);
    //Imprimindo o resultado
    (result == -1) ? printf("Chave inexistente\n") : printf("%d\n", result);    

    //Liberando a memória heap
    free(elements);

    return 0;
}