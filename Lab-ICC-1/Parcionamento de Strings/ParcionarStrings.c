/*
    ICMC USP - Diógenes Silva Pedro - BCC 020
    Programa que particiona e ordena uma string
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

//Função que le uma string de tamanho indefinido e a aloca na memória heap o espaço exato
char* readLine(FILE* stream){
    char *str;

    str = (char*) malloc (16 * sizeof(char)); //Fazendo uma alocação inicial

    int pos = 0, tamanho = 16;
    
    do {
        //Realocando a memória heap caso a palavra exceda o espaço máximo
        if (pos == tamanho) {
            str = realloc (str, 2 * tamanho);
            tamanho *= 2;
        }

        //Recebendo os caracteres
        str[pos] = (char) fgetc(stdin);
        if (str[pos] == '$') pos--;
        pos++;

    } while (str[pos-1] != '\r' && str[pos-1] != '\n' && !feof(stdin));
    
    str[pos-1] = '\0';
    str = realloc(str, pos);

    return str;
}

//Função que ordena os registros pela ordem lexicográfica
char** sort_Letter(char **string, int count){
    //Definindo variáveis auxiliares que ajudarão a ordenar os registros
    int i, j;
    char *temp;

    for(i = 0; i < count; i++) {
        for(j = 0; j < count-i-1; j++){
            //Caso a palavra 2° palavra seja maior que a 1° faremos a segunda palavra ir para a
            //posição da primeira, mudando também o número dessas 2 linhas
            if(strcmp(string[j], string[j+1]) > 0) {
                //Trocando os elementos
                temp = string[j];
                string[j] = string[j+1];
                string[j+1] = temp;
            }
        }
    }

    return string;
}

int main(int argc, char *argv[]) {
    
    char *string;
    
    //Lendo a string
    string = readLine(stdin);
    
    int opt;
    //Lendo qual a operação
    scanf("%d", &opt);

    //Alocando na heap antes de realocar
    char **savedString;
    savedString = (char**) malloc (1 * sizeof(char*));

    //Declarando variáveis auxiliares
    char *retorno;
    char *p = string;

    //Particionando a string
    int count = 0;
    while ((retorno = strsep(&p, " ")) != NULL) {
        savedString = realloc (savedString, (count+1) * sizeof(char*));
        savedString[count] = strdup(retorno);
        count++;
    }

    //Opertaion 1 = printar na tela
    if (opt == 1){
        for (int i = 0; i < count; i++){
            printf("%s\n", savedString[i]);
        }
    }
    //Operation 2 = printar na tela em ordem alfabética
    else {

        //Deixando todas as letras minúsculas
        for (int i = 0; i < count; i++){
            for (int j = 0; j < strlen(savedString[i]); j++){
                savedString[i][j] = tolower(savedString[i][j]);
            }
        }

        savedString = sort_Letter(savedString, count);
        
        for (int i = 0; i < count; i++){
            printf("%s\n", savedString[i]);
        }
    }

    //Liberando Heap
    free(string);
    free(retorno);
    for (int i = 0; i < count; i++){
        free(savedString[i]);
    }
    free(savedString);

    return 0;
}