/*
    ICMC USP - Diógenes Silva Pedro - nUSP:11883476 - BCC 020
    Código feito para a P1 de ICC 1 (SCC0221) Professor: Rodrigo Mello
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

#define TRUE 1;
#define FALSE 0;

//Função que le uma string de tamanho indefinido e a aloca na memória heap o espaço exato
char* readLine(FILE* stream){
    char *str;

    str = (char*) malloc (32 * sizeof(char)); //Fazendo uma alocação inicial

    int pos = 0, tamanho = 32;
    
    do {
        //Realocando a memória heap caso a palavra exceda o espaço máximo
        if (pos == tamanho) {
            str = realloc (str, 2 * tamanho);
            tamanho *= 2;
        }

        //Recebendo os caracteres
        str[pos] = (char) fgetc(stream);
        if (str[pos] == '\r') pos--;
        pos++;

    } while (str[pos-1] != '\n' && !feof(stream));

    str[pos-1] = '\0'; 
    str = realloc(str, pos);
    
    return str;
}

//Função auxiliar para a ordenação das strings usada no qsort
int compare(const void *str1, const void *str2){
    const char *a = *(const char**)str1;
    const char *b = *(const char**)str2;
    return strcmp(a, b);
}

//Função que descobre a maior palavra do arquivo e sua posição
int biggestWord(char **strings, int biggest_Index, int count){
    int biggest_word;
    for (int i = 0; i < count; i++){
        if (i == 0) 
            biggest_word = strlen(strings[i]);
        else if (strlen(strings[i]) > biggest_word){
            biggest_word = strlen(strings[i]);
            biggest_Index = i;
        }
    }

    return biggest_Index;
}

//Função que descobre a menor palavra do arquivo e sua posição
int smallestWord(char **archive_text, int smallest_Index, int count){
    int smallest_word;
    for (int i = 0; i < count; i++){
        if (i == 0)
            smallest_word = strlen(archive_text[i]);
        else if (strlen(archive_text[i]) < smallest_word){
            smallest_word = strlen(archive_text[i]);
            smallest_Index = i;
        }
    }

    return smallest_Index;
}

//Função que descobre a quantidade de palíndromos do arquivo
int findPalindromes(char **archive_text, int how_much_palindromes, int count){
    for (int i = 0; i < count; i++){  
        
        int begin;
        int end = strlen(archive_text[i]) - 1;
        int isPalindrome = TRUE;

        for (begin = 0; begin <= end; begin++, end--){
            if (archive_text[i][begin] != archive_text[i][end]) {
                isPalindrome = FALSE;
                break;
            }
        }

        if (isPalindrome) how_much_palindromes++;
    }

    return how_much_palindromes;
}

//Função que descobre a quantidade de aparições do parâmetro P1
int caseP1(char **archive_text, char *parameter_P1, int how_much_P1, int count){
    regex_t expression_P1;
    regcomp(&expression_P1, parameter_P1, REG_EXTENDED);
    for (int i = 0; i < count; i++){
        if(!regexec(&expression_P1, archive_text[i], 0, NULL, 0)) how_much_P1++;
    }
    regfree(&expression_P1);

    return how_much_P1;
}

//Função que descobre a maior palavra a partir do parâmetro P2 e qual sua posiçao
char** readParameter(char** archive_text, char** str, char* parameter, int *count_P2, int count) {
    
    int parameter_count = 0;

    regex_t expression_P2;
    regcomp(&expression_P2, parameter, REG_EXTENDED);
    for (int i = 0; i < count; i++){
        if(!regexec(&expression_P2, archive_text[i], 0, NULL, 0)) {
            str = (char**) realloc (str, (parameter_count + 1) * sizeof(char*));
            str[parameter_count] = strdup(archive_text[i]);
            parameter_count++;
        }
    }
    regfree(&expression_P2);

    *count_P2 = parameter_count;

    return str;
}

int findmostSimilar(char **archive_text, char* parameter_W, int pos_parameter_W, int count){
    
    //Descobrindo o tamanho da palavra a ser procurada
    int height = strlen(parameter_W);
    //Criando um vetor de matrizes para analisar a quantidade de chars iguais entre as palavras do
    //do arquivo e a palavra do parametro W
    int ***matching_matrix;
    //Alocando a memória e já preenchendo com zeros
    matching_matrix = (int***) calloc (count, sizeof(int**));
    for (int i = 0; i < count; i++){
        int lenght = strlen(archive_text[i]);
        matching_matrix[i] = (int**) calloc (height, sizeof(int*));
        
        for (int j = 0; j < height; j++){
            matching_matrix[i][j] = (int*) calloc (lenght, sizeof(int));    
        }
    }    

    //Criando uma variável auxiliar que guardará o índice de similariade máximo
    int max_parameter_W = 0;
    //Analisando quantos chars tem em comum entre cada linha do arquivo com o parametro W 
    for (int i = 0; i < count; i++){
        //Descobrindo o tamanho da palavra do arquivo para a analise char a char
        int word_lenght = strlen(archive_text[i]);
        for (int j = 0; j < height; j++){
            //Analisando char a char a palavra do arquivo com a palavra do parametro para descobrir
            //o índice de similaridade, procuraremos então o maior índice de similaridade e a menor
            //palavra que contenha esse índice máximo
            for (int k = 0; k < word_lenght; k++){
                //Na primeira linha e na primeira coluna apenas comparamos os chars
                if (j == 0 || k == 0){
                    if (parameter_W[j] == archive_text[i][k]) matching_matrix[i][j][k]++;
                }
                //Para qualquer linha ou coluna diferente de 0, primeiramente pegamos o valor da 
                //diagonal anterior a posição atual do char, assim podemos apenas somar 1 caso os 
                //chars sejam iguais
                else {
                    matching_matrix[i][j][k] = matching_matrix[i][j-1][k-1];
                    if (parameter_W[j] == archive_text[i][k]) matching_matrix[i][j][k]++;
                }

                //Descobrindo o maior índice de similaridade
                if (matching_matrix[i][j][k] > max_parameter_W){
                    max_parameter_W = matching_matrix[i][j][k];
                    pos_parameter_W = i;
                }

                //Descobrindo a menor palavra
                else if (matching_matrix[i][j][k] == max_parameter_W){
                    if (strlen(archive_text[i]) < strlen(archive_text[pos_parameter_W])) 
                        pos_parameter_W = i;
                }
            }
        }
    }

    for (int i = 0; i < count; i++){
        for (int j = 0; j < height; j++){
            free(matching_matrix[i][j]);
        }
        free (matching_matrix[i]);
    }
    free(matching_matrix);

    return pos_parameter_W;
}

//Função que desaloca ponteiros duplos de char
void desalocateDoubleCharPointer(char **string, int count){
    for (int i = 0; i < count; i++){
        free(string[i]);
    }
    free(string);
}

int main(){

    //Criando as strings que guardarão as entradas e recebendo elas
    char *filename, *parameter_P1, *parameter_P2, *parameter_P3, *parameter_W;
    filename = readLine(stdin);
    parameter_P1 = readLine(stdin);
    parameter_P2 = readLine(stdin);
    parameter_P3 = readLine(stdin);
    parameter_W = readLine(stdin);

    //Criando o ponteiro do tipo FILE para abrir o arquivo
    FILE *archive;
    //Abrindo o arquivo
    archive = fopen(filename, "r");
    
    //Crinado uma matriz de strings para receber as entradas do arquivo
    char **archive_text = NULL;

    //Criando uma variável que guarda a quantidade de linhas do arquivo
    int count = 0;

    //Lendo as entradas do arquivo
    while (!feof(archive)) {
        //Reallocando a matriz de nomes quando a cada nova linha
        archive_text = (char**) realloc (archive_text, (count+1) * sizeof(char*));
        //Guardando dentro da matriz de nomes a linha
        archive_text[count] = readLine(archive);
        //Testando para não salvar qualquer linha vazia que possa existir
        if (strcmp(archive_text[count], "") == 0) count--;
        //Aumentando o valor de count, pois ele guarda quantas linhas tem no arquivo
        count++;
    }

    //Criando as variáveis que guardarão a posição da maior palavra e menor palavra respectivamente
    int biggest_Index = 0, smallest_Index = 0;

    //Descobrindo a maior e a menor palavra
    biggest_Index = biggestWord(archive_text, biggest_Index, count);    
    smallest_Index = smallestWord(archive_text, smallest_Index, count);
    
    //Criando uma variável que guarda a quantidade de palíndromos
    int how_much_palindromes = 0;

    //Descobrindo a quantidade de palíndromos
    how_much_palindromes = findPalindromes(archive_text, how_much_palindromes, count);

    //Criando uma variável para guardar quantas aparições temos no caso do primeiro regex
    int how_much_P1 = 0;

    //Descobrindo a quantidade de aparições
    how_much_P1 = caseP1(archive_text, parameter_P1, how_much_P1, count);

    //Criando uma matriz de nomes para o caso do segundo regex
    char **strings_P2 = NULL;
    int count_P2 = 0, max_P2_index = 0;

    //Guardando na nova matriz de strings as correspondências do parâmetro P2
    strings_P2 = readParameter(archive_text, strings_P2, parameter_P2, &count_P2, count);

    //Achando a maior palavra dentro as salvas
    max_P2_index = biggestWord(strings_P2, max_P2_index, count_P2);

    //Criando uma matriz de nomes para o caso do terceiro regex
    char **strings_P3 = NULL;
    int count_P3 = 0;

    //Guardando na nova matriz de strings as correspondências do parâmetro P3
    strings_P3 = readParameter(archive_text, strings_P3, parameter_P3, &count_P3, count);

    //Ordenando as palavras da matriz de nomes em ordem lexicográfica
    qsort(strings_P3, count_P3, sizeof(char*), compare);

    //Criando uma variável que guarda a posição da palavra mais similar a palavra do parametro W
    int pos_parameter_W = 0;
    pos_parameter_W = findmostSimilar(archive_text, parameter_W, pos_parameter_W, count);

    //Printando os resultados
    printf("%d\n", count);
    printf("%s\n", archive_text[smallest_Index]);
    printf("%s\n", archive_text[biggest_Index]);
    printf("%d\n", how_much_P1);
    printf("%d\n", how_much_palindromes);
    printf("%s\n", strings_P2[max_P2_index]);  
    for (int i = 0; i < count_P3; i++){
        printf("%s\n", strings_P3[i]);
    }
    printf("%s\n", archive_text[pos_parameter_W]);  

    //Desalocando a memória heap
    desalocateDoubleCharPointer(archive_text, (count+1)); //Usando count+1 por causa da linha vazia
    //gerada pelo feof no fim do arquivo
    desalocateDoubleCharPointer(strings_P2, count_P2);
    desalocateDoubleCharPointer(strings_P3, count_P3);
    free(filename);
    free(parameter_P1);
    free(parameter_P2);
    free(parameter_P3);
    free(parameter_W);
    
    //Fechando o arquivo
    fclose(archive);

    return 0;
}