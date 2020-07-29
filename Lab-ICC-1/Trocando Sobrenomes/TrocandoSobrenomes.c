/*
    ICMC USP - Diógenes Silva Pedro - BCC 020
    Programa que troca sobrenomes
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef struct {
    char *name;
    char *surename;
    char *fullname;
} PINFO;

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

//Função que substitui os sobrenomes
PINFO* switchSurename(PINFO *names, char**incoming_text, int count){
    //Descobrindo o último sobrenome para o específico nome e salvando ele
    for (int i = 0; i < count; i++){
        char *aux = NULL;
        aux = rindex(incoming_text[i], 32);
        names[i].surename = strdup(aux);
        names[i].name = strdup(incoming_text[i]);
    }

    //Tirando o último sobrenome do nome a partir da subtração do tamanho do nome completo - ultimo
    //sobrenome
    for (int i = 0; i < count; i++){
        int a = strlen(names[i].name) - strlen(names[i].surename);
        names[i].name = realloc (names[i].name, a * sizeof(char));
        names[i].name[a] = '\0';
    }

    //Copiando o nome e o sobrenome respectivo para a palavra completa
    for (int i = 0; i < count; i++){
        int c = count - (i + 1);
        int d = strlen(names[i].name) + strlen(names[c].surename);
        names[i].fullname = (char*) malloc (d * sizeof(char));
        strcat(names[i].fullname, names[i].name);
        strcat(names[i].fullname, names[c].surename);
    }
    
    return names;
}

void desalocateHeap(PINFO *names, char **incoming_text, int count){
    //Desalocando a memória heap
    for (int i = 0; i < count; i++){
        free(names[i].name);
        free(names[i].surename);
        free(names[i].fullname);
        free(incoming_text[i]);
    }
    free(incoming_text);
    free(names);
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
        count++;
    }

    //Criando a struct que guarda o nome, o último sobrenome e o nome completo após mudança
    PINFO *names;
    names = (PINFO*) malloc (count * sizeof(PINFO));

    //Substituindo os sobrenomes
    names = switchSurename(names, incoming_text, count);

    //Printando o resultado da substituição dos sobrenomes
    for (int i = 0; i < count; i++) printf("%s\n", names[i].fullname);

    desalocateHeap(names, incoming_text, count);

    return 0;
}