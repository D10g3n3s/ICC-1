#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <define.h>
#include <archive.h>
#include <utils.h>
#include <math.h>

//Função que le uma string de tamanho indefinido e a aloca na memória heap o espaço exato
char* readLine(FILE* input){
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
        str[pos] = (char) fgetc(input);
        if (str[pos] == '\r') pos--;
        pos++;

    } while (str[pos-1] != '\n' && !feof(input));

    str[pos-1] = '\0'; 
    str = realloc(str, pos);
    
    return str;
}

//Função auxiliar para ordenação das chaves int
int intCompare(const void* a, const void* b) {
    return ((*(REGISTER*)a).key.type.i - (*(REGISTER*)b).key.type.i);
}

//Função auxiliar para ordenação das chaves float
int fCompare(const void* a, const void* b){
    float dif = ((*(REGISTER*)a).key.type.f - (*(REGISTER*)b).key.type.f);
    return dif > 0 ? ceil(dif) : floor(dif);
}

//Função auxiliar para ordenação das chaves float
int dCompare(const void* a, const void* b){
    double dif = ((*(REGISTER*)a).key.type.d - (*(REGISTER*)b).key.type.d);
    return dif > 0 ? ceil(dif) : floor(dif);
}

//Função auxiliar para ordenação das chaves str
int strCompare(const void* a, const void* b){
    return strcmp((*(REGISTER*)a).key.type.str, (*(REGISTER*)b).key.type.str);
}

//Função que faz a busca binária em inteiros
int intBinarySearch(int *elements, int lo, int hi, int key){
    if (hi >= lo) { 
        int mid = lo + (hi - lo) / 2; 
  
        //Caso o elemento seja o próprio elemento do meio 
        if (elements[mid] == key) return mid; 
   
        //Caso o elemento seja menor que o termo do meio, então o elemento só pode estar presente no
        //suboconjunto a direita
        if (elements[mid] > key) return intBinarySearch(elements, lo, mid - 1, key); 
  
        //O elemento pode só pode estar presente no subconjunto a direita 
        return intBinarySearch(elements, mid + 1, hi, key); 
    } 

    // Caso o elemento não esteja presente no conjunto
    return -1; 
}

//Função que faz a busca binária em floats
int floatBinarySearch(float *elements, int lo, int hi, float key){
    if (hi >= lo) { 
        int mid = lo + (hi - lo) / 2; 
  
        //Caso o elemento seja o próprio elemento do meio 
        if (elements[mid] == key) return mid; 
   
        //Caso o elemento seja menor que o termo do meio, então o elemento só pode estar presente no
        //suboconjunto a direita
        if (elements[mid] > key) return floatBinarySearch(elements, lo, mid - 1, key); 
  
        //O elemento pode só pode estar presente no subconjunto a direita 
        return floatBinarySearch(elements, mid + 1, hi, key); 
    } 

    // Caso o elemento não esteja presente no conjunto
    return -1; 
}

//Função que faz a busca binária em double
int doubleBinarySearch(double *elements, int lo, int hi, double key){
    if (hi >= lo) { 
        int mid = lo + (hi - lo) / 2; 
  
        //Caso o elemento seja o próprio elemento do meio 
        if (elements[mid] == key) return mid; 
   
        //Caso o elemento seja menor que o termo do meio, então o elemento só pode estar presente no
        //suboconjunto a direita
        if (elements[mid] > key) return doubleBinarySearch(elements, lo, mid - 1, key); 
  
        //O elemento pode só pode estar presente no subconjunto a direita 
        return doubleBinarySearch(elements, mid + 1, hi, key); 
    } 

    // Caso o elemento não esteja presente no conjunto
    return -1; 
}

//Função que faz a busca binária em strings
int stringBinarySearch(char **elements, int lo, int hi, char *key){
    if (hi >= lo) {
        int mid = lo + (hi - lo) / 2;

        printf("%d\n", strcmp(elements[mid], key));
        //Caso o elemento seja o próprio elemento do meio 
        if (!strcmp(elements[mid], key)) return mid; 

        //Caso o elemento seja menor que o termo do meio, então o elemento só pode estar presente no
        //suboconjunto a direita
        if (strcmp(elements[mid], key) > 0) return stringBinarySearch(elements, lo, mid - 1, key); 
  
        //O elemento pode só pode estar presente no subconjunto a direita 
        return stringBinarySearch(elements, mid + 1, hi, key); 
    } 

    // Caso o elemento não esteja presente no conjunto
    return -1; 
}

