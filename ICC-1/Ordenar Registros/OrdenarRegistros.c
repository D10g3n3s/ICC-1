/*
    ICMC USP - Diógenes Silva Pedro - BCC 020
    Programa que le e ordena registros    
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int number;
    char *information;
} DATA;

typedef struct {
    DATA *treated_data;
    int lines_number;
    int operation;
} INFO;

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
        pos++;

    } while (str[pos-1] != '\r' && str[pos-1] != '\n' && !feof(stream));
    
    str[pos-1] = '\0';
    str = realloc (str, pos);

    return str;
}

INFO* analizeData(INFO *text, char **incoming_text){

    //Criando uma matriz dupla auxiliar para procurar a parte inteira do registro
    char **str;
    str = (char**) malloc (text->lines_number * sizeof(char*));

    //Alocando o espaço exato para o registro sem a parte inteira
    for (int i = 0; i < text->lines_number; i++){
        //Calculando o tamanho da string
        int a = strlen(incoming_text[i+1]);
        //Alocando a string na struct
        text->treated_data[i].information = (char*) malloc (a * sizeof(char));
        strcpy(text->treated_data[i].information, incoming_text[i+1]);
    }

    for (int i = 0; i < text->lines_number; i++){
        //Procurando pelo valor inteiro do espaço na tabela ascii
        str[i] = rindex(incoming_text[i+1], 32);
        //Criando variável auxiliar com o tamanho do ponteiro apontando para o valor inteiro não
        //contando o espaço
        int b = strlen(str[i]) - 1; 
        char aux[b]; 
        //Copiando a string do ponteiro para dentro da variável aux sem o espaço, copiando apenas o
        //valor inteiro. O +1 anda 1 byte no ponteiro, fazendo o espaço não ser copiado
        strcpy(aux, str[i]+1);
        //Guardando o valor da string aux dentro da struct DATA, transformando a string para inteiro
        text->treated_data[i].number = atoi(aux);
    }

    for (int i = 0; i < text->lines_number; i++){
        int c = strlen(incoming_text[i+1]) - strlen(str[i]);
        text->treated_data[i].information = realloc (text->treated_data[i].information, c);
        text->treated_data[i].information[c] = '\0';
    }

    //Desalocando a memória heap se não será mais usada
    free(str);
    return text;
}

//Função que ordena os dados a partir dos valores inteiros
INFO* sort_Number(INFO* text){
    //Definindo variáveis auxiliares que ajudarão a ordenar os registros
    int i, j, temp;
    char *temp2;
    
    for(i = 0; i < text->lines_number; i++) {
        for(j = 0; j < (text->lines_number)-i-1; j++) {
            //Caso o 1° número seja maior que o segundo trocaremos os 2 de lugar, mudando também a
            //string dessa linha para elas continuarem juntas
            if(text->treated_data[j].number > text->treated_data[j+1].number) {
                //Trocando os elementos
                temp = text->treated_data[j].number;
                text->treated_data[j].number = text->treated_data[j+1].number;
                text->treated_data[j+1].number = temp;

                temp2 = text->treated_data[j].information;
                text->treated_data[j].information = text->treated_data[j+1].information;
                text->treated_data[j+1].information = temp2;    
            } 
        }
    }

    return text;
}

//Função que ordena os registros pela ordem lexicográfica
INFO* sort_Letter(INFO* text){
    //Definindo variáveis auxiliares que ajudarão a ordenar os registros
    int i, j, temp2;
    char *temp;

    for(i = 0; i < text->lines_number; i++) {
        for(j = 0; j < (text->lines_number)-i-1; j++){
            //Caso a palavra 2° palavra seja maior que a 1° faremos a segunda palavra ir para a
            //posição da primeira, mudando também o número dessas 2 linhas
            if(strcmp(text->treated_data[j].information, text->treated_data[j+1].information) > 0) {
                //Trocando os elementos
                temp = text->treated_data[j].information;
                text->treated_data[j].information = text->treated_data[j+1].information;
                text->treated_data[j+1].information = temp;

                temp2 = text->treated_data[j].number;
                text->treated_data[j].number = text->treated_data[j+1].number;
                text->treated_data[j+1].number = temp2;
            }
        }
    }

    return text;
}

//Função que printa os registros ordenados
void show_Ordenated(INFO* text){
    for (int i = 0; i < text->lines_number; i++){
        printf("%d\t%s\n", text->treated_data[i].number, text->treated_data[i].information);
    }
}

//Função que desaloca memória heap
void desalocateHeap(INFO* text, char** str){
    //Desalocando a memória heap utilizada
    for (int i = 0; i < text->lines_number+1; i++){
        free(str[i]);
    }
    free(str);
    
    for(int i = 0; i < text->lines_number; i++){
        free(text->treated_data[i].information);
    }
    free(text->treated_data);
    free(text);
}

int main(){    
    //Criando variáveis e armazenando na heap
    //Criando a struct INFO
    INFO *text;
    text = (INFO*) malloc (1*sizeof(INFO));

    //Criando uma matrix dupla onde cada linha guardará as entradas do programa
    char **incoming_text; 
    incoming_text = (char**) malloc (1*sizeof(char*));

    int i = 0;
    //Lendo os registros a serem ordenados
    while (!feof(stdin)){
        //Realocando a memória heap a cada nova linha
        incoming_text = (char**) realloc (incoming_text, (i+1) * sizeof(char*));
        //Lendo a entrada com a função readLine
        incoming_text[i] = readLine(stdin);
        //Salvando na variável que conta quantas linhas tem caso o tamanho do texto seja maior que 1
        //pois a primeira operação tem apenas 1 caracter
        if (strlen(incoming_text[i]) != 1) (text->lines_number)++;
        //Retirando o espaço do final da linha, caso ele exista
        int a = strlen(incoming_text[i]);
        if (incoming_text[i][a - 1] == 32){
            incoming_text[i] = realloc (incoming_text[i], a-1);
            incoming_text[i][a - 1] = '\0';
        }       
        i++;
    }  

    //Criando a struct que armazenará os dados analisados e separados 
    text->treated_data = (DATA*) malloc (text->lines_number * sizeof(DATA));

    //Analisando os dados e separando os registros
    text = analizeData(text, incoming_text);

    //Como a primeira linha é sempre a operação temos que guardar esse valor em uma variável inteira
    //no caso utilizamos a função atoi(ascii to integer) para guardar a informação lida como char e 
    //guardá-la como inteiro
    text->operation = atoi(incoming_text[0]);

    //Ordena os registros pela ordem lexicográfica
    if (text->operation == 1){
        //Chamando a função de ordenação 
        sort_Letter(text);
        //Chamando a função que printa os registros ordenados
        show_Ordenated(text);
    }
    
    //Ordena os registros pela ordem crescente
    else if(text->operation == 2){
        //Chamando a funçaõ de ordenação
        sort_Number(text);
        //Chamando a função que printa os registros ordenados
        show_Ordenated(text);
    }

    //Desalocando a memória heap
    desalocateHeap(text, incoming_text);
    
    return 0;
}