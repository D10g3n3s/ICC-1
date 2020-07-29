/*
    ICMC USP - Diógenes Silva Pedro - BCC 020
    Programa para substituir uma palavra escolhida pela nova palavra em uma string qualquer
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Função que le uma string de tamanho indefinido e a aloca na memória heap o espaço exato
char* readline(FILE* stream){
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
        pos++;

    } while (str[pos-1] != '\n' && !feof(stream));
    
    str[pos-1] = '\0';
    str = realloc (str, pos);

    return str;
}

//Função que muda uma palavra antiga por uma nova dentro de uma frase
char *MudaPalavra(const char *frase, const char *velhaPal, const char *novaPal){
    char *novaFrase;
    int i, count = 0;
    int novoTam = strlen(novaPal);
    int velhoTam = strlen(velhaPal);
    
    //Contando quantas vezes a velha palavra aparece na antiga frase
    for (i = 0; frase[i] != '\0'; i++){

        //Achando a velha palavra na frase
        if (strstr(&frase[i], velhaPal) == &frase[i]){
            count++;
            i += velhoTam - 1;
        }
    }

    //Fazendo que a nova frase tenha tamanho suficiente
    novaFrase = (char*) malloc (i + count * sizeof(char));

    i = 0;
    while (*frase) {
        //Compara a substring com a nova frase
        if (strstr(frase, velhaPal) == frase){
            strcpy (&novaFrase[i], novaPal);
            i += novoTam;
            frase += velhoTam;
        }
        else 
            novaFrase[i++] = *frase++;
    }

    novaFrase[i] = '\0';
    return novaFrase;
}

int main(){

    //Criando as variáveis que receberão as strings 
    char *velhaPal, *novaPal, *frase, *novaFrase = NULL;

    //As variáveis a seguir serão alocadas na heap a partir da função ReadLine
    //Lendo a palavra a que será substituida
    velhaPal = readline(stdin);
    //Lendo a palavra que entrará no lugar da palavra antiga
    novaPal = readline(stdin);
    //Lendo a frase onde procuraremos a palavra antiga que será trocada pela nova
    frase = readline(stdin);

    //Mudando a frase, substituindo as antigas palavras pelas novas
    novaFrase = MudaPalavra(frase, velhaPal, novaPal);

    printf("%s\n", novaFrase);

    //Liberando a memória heap alocada para as strings
    free(velhaPal);
    free(novaPal);
    free(frase);

    return 0;
}