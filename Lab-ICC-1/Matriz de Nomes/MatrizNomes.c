/*
    ICMC USP - Diógenes Silva Pedro - BCC 020
    Programas que le nomes e printa-os em ordem alfabética
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
        if (str[pos] == '\r') pos--;
        pos++;

    } while (str[pos-1] != '\n' && !feof(stdin));

    str[pos-1] = '\0';
    str = realloc(str, pos);

    return str;
}

int main(){

    //Criando a matriz de strings auxiliar que le todas as entradas antes de analizar e separá-las
    char **incoming_text = NULL;

    //Lendo as entradas, na readLine o caractér $ não está sendo guardado e estamos lendo até o fim
    //da entrada stdin, por estar usando char** cada linha está sendo guardada em um ponteiro char
    int count = 0;
    while (!feof(stdin)){
        //Realocando a memória heap a cada nova linha
        incoming_text = (char**) realloc (incoming_text, (count+1) * sizeof(char*));
        //Lendo a entrada com a função readLine
        incoming_text[count] = readLine(stdin);          
        if (strcmp(incoming_text[count], "") != 0) count++;
    }

    //Ordenando através da ordem alfabética
    char *temp;
    for (int i = 0; i < count; i++){
        for (int j = 0; j < count-i-1; j++){
            if (strcmp(incoming_text[j], incoming_text[j+1]) > 0){
                temp = incoming_text[j];
                incoming_text[j] = incoming_text[j+1];
                incoming_text[j+1] = temp;
            }
        }
    }

    //Printando os nomes em ordem alfabética
    for (int i = 0; i < count; i++){
        printf("%s\n", incoming_text[i]);
    }

    //Liberando a memória HEAP usada
    for (int i = 0; i < count; i++){
        free(incoming_text[i]);
    }
    free (incoming_text);

    return 0;
}
