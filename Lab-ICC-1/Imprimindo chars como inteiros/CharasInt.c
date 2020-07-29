/*
    ICMC USP - Diógenes Silva Pedro - BCC 020
    Programa que imprime chars como inteiros
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Função que le uma string de tamanho indefinido e a aloca na memória heap o espaço exato
char* readLine(FILE* stream, int* amountOfChars){
    char *str;

    str = (char*) malloc (16 * sizeof(char)); //Fazendo uma alocação inicial

    int pos = 0, tamanho = 16;
    
    //Lendo até achar o x
    do {
        //Realocando a memória heap caso a palavra exceda o espaço máximo
        if (pos == tamanho) {
            str = realloc (str, 2 * tamanho);
            tamanho *= 2;
        }

        //Recebendo a letra
        str[pos] = (char) fgetc(stdin);
        //Caso haja '\n' ou '\r' voltaremos a posição em 1, para guardar a letra na posição do \n ou
        //do \r
        if (str[pos] == '\n' || str[pos] == '\r') pos--;
        pos++;

    } while (str[pos-1] != 'x');
    
    //Fazendo a string ao adicionar \0 no final
    str[pos+1] = '\0';
    str = realloc (str, pos);

    *amountOfChars = pos;

    //Returnando a string para a main
    return str;
}

//Funções para fazer a ordenação com quicksort
void swap (char* a, char* b){ 
        char temp;
        temp = *a;
        *a = *b;
        *b = temp;
}

int partition (char *arr, int low, int high){

        int pivot = arr[high];
        int i = (low - 1);

        for (int j = low; j <= high- 1; j++){

                if (arr[j] < pivot){

                        i++;
                        swap(&arr[i], &arr[j]);
                }
        }
        swap(&arr[i + 1], &arr[high]);

return (i + 1);
}

void quickSort(char *arr, int low, int high){

        if (low < high){

        int pi = partition(arr, low, high);

        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}  

int main(){

    //Criando a string que receberá os dados
    char *string;
    
    int amountOfChars = 0;
    
    //Lendo a string
    string = readLine(stdin, &amountOfChars);
    //Ordenando a string
    quickSort(string, 0, amountOfChars - 1);

    //Criando o ponteiro que lerá os chars como int
    unsigned int *integer;

    //Recebendo o endereço que o ponteiro string aponta para o ponteiro int
    integer = (unsigned int*) string;

    //Imprimindo os chars como inteiros
    for (int i = 0; i < amountOfChars/4; i++){
        printf("%u\n", integer[i]);
    }

    //Liberando a memória heap
    free(string);

    return 0;
}