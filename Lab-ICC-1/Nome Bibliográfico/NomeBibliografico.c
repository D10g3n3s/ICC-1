/*
    ICMC USP - Diógenes Silva Pedro - BCC 020
    Programa que troca faz um nome bibliográfico
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

int main(){
    
    //Criando variaveis
    char *name, *libraryname;

    //Lendo a entrada
    name = readLine(stdin);

    //Procurando o último sobrenome
    char *aux;
    aux = rindex(name, 32);
    
    //Transformando as letras do último sobrenome em letras maiúsculas
    for (int i = 1; i < strlen(aux); i++){
        aux[i] = toupper(aux[i]);
    }

    //Alocando o espaço necessário para a palavra no modo bibliográfico, o +1 é por conta da vírgula
    libraryname = (char*) malloc ((strlen(name) + 1) * sizeof(char));

    //Descobrindo o tamanho da palavra sem o último sobrenome e removendo-o
    int r = strlen(name) - strlen(aux);
    name = realloc (name, r * sizeof(char));
    name[r] = '\0';

    //Transofrmando em sobrenome bibliográfico
    strcat(libraryname, aux+1);
    strcat(libraryname, ", ");
    strcat(libraryname, name);
    
    //Printando o nome bibliográfico
    printf("%s\n", libraryname);

    //Liberando a memória heap
    free(name);
    free(libraryname);

    return 0;
}