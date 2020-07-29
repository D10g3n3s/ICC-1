/*
    ICMC USP - Diógenes Silva Pedro - BCC 020
    Programa que adiciona sobrenomes
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
    str = realloc (str, pos);

    return str;
}

int main(){
    
    //Criando a matriz de nomes na heap
    char **incoming_text = NULL;

    //Lendo as entradas, na readLine o caractér $ não está sendo guardado e estamos lendo até o fim
    //da entrada stdin, por estar usando char** cada linha está sendo guardada em um ponteiro char
    int i = 0;
    while (!feof(stdin)){
        //Realocando a memória heap a cada nova linha
        incoming_text = (char**) realloc (incoming_text, (i+1) * sizeof(char*));
        //Lendo a entrada com a função readLine
        incoming_text[i] = readLine(stdin);          
        i++;
    }  

    //Criando um ponteiro char auxiliar que procurará o sobrenome com a função rindex e adicionará 
    //na próxima linha caso o índice seja diferente ao número de palavras, que está guardado em i
    char *aux = NULL;
    for (int j = 0; j < i; j++){
        if ((j%2) == 0){
            if (j != i-1){
                aux = rindex(incoming_text[j], 32); //Procurando o último sobrenome
                strcat(incoming_text[j+1], aux); //Copiando o último sobrenome na proxima palavra
            }
        }
    }

    //Printando os nomes
    for (int j = 0; j < i; j++){
        printf("%s\n", incoming_text[j]);
    }

    //Liberando a memória heap
    for (int j = 0; j < i; j++){
        free(incoming_text[j]);
    }
    free(incoming_text);

    return 0;
}