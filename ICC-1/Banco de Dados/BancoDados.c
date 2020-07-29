/*
 _____________________________________________________________
|     ___________________________________________________     |
|    |             Universidade de São Paulo             |    |
|    |                                                   |    |
|    | Instituto de Ciências Matemáticas e de Computação |    |
|    |                                                   |    |
|    |           Diógenes Silva Pedro BCC 020            |    |
|    |                                                   |    |
|    |                  nUSP: 11883476                   |    |
|    |                                                   |    |
|    |               diogenes.pedro@usp.br               |    |
|    |                                                   |    |
|    |            diogenes.pedro60@gmail.com             |    |
|    |                                                   |    |
|    |                                                   |    |
|    |                       SGBD                        |    |
|    |                                                   |    |
|    |___________________________________________________|    |
|_____________________________________________________________|
       |_______________________________________________|       
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define TRUE 1;
#define FALSE 0;

typedef union {
    int i;
    float f;
    double d;
    char *str;
} TYPE;

typedef enum {INT = 1, FLOAT, DOUBLE, CHAR} DATA_TYPE;

typedef struct {
    TYPE type;
    DATA_TYPE data_type;
    int size;
} KEY;

typedef struct {
    TYPE type;
    DATA_TYPE data_type;
    int size;
} FIELDS;

typedef struct {
    FIELDS *fields;
    KEY key;
} REGISTER;

typedef struct {
    REGISTER reg_field;
    REGISTER *regs;
    int howmanyregs;
    char *datname;
    char *regname;
    char *regidx;
    int *offset;
    int patternoffset;
} DATABASE;

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

//Função que le o arquivo .dat
char** readDat(DATABASE *data, char **aux, int *count, int *null_line){
    //Descobrindo o nome do arquivo a ser aberto
    data->datname = readLine(stdin);

    //Abrindo o arquivo
    FILE* archive;
    archive = fopen(data->datname, "r");

    //Testando o erro de arquivo inexistente
    if (archive == NULL){
        printf("Não possível abrir o arquivo\n");
    }

    //Lendo o arquivo
    while(!feof(archive)){
        aux = (char**) realloc (aux, (*count+1) * sizeof(char*));
        aux[*count] = readLine(archive);
        if (strcmp(aux[*count], "")) (*count)++;
        else if (!strcmp(aux[*count], "")) (*null_line)++;
    }

    //Fechando o primeiro arquivo
    fclose(archive);
    
    return aux;
}

//Função que salva o nome do registro para o .reg e o .idx
void regName(DATABASE *data, char *aux){
    //Salvando o .reg
    char *str = rindex(aux, ' ');
    data->regname = strdup(str+1);

    //Salvando o nome .idx
    str = rindex(aux, '.');
    data->regidx = strdup(data->regname);
    data->regidx[strlen(data->regname) - strlen(str)] = '\0';
    strcat(data->regidx, ".idx");
    data->regidx[strlen(data->regidx)] = '\0';
}

//Função que cria os campos dos tipos do registro
DATABASE* createRegFields(DATABASE *data, char **aux, int count){
    //Salvando o nome da chave
    char *str = index(aux[1], ' ');
    data->reg_field.key.type.str = strdup(str+1);

    //Salvando o tipo da chave e seu tamanho
    str = index(aux[2], ' ');
    if(!strncmp(str+1, "int", 3)){ 
        data->reg_field.key.data_type = INT;
        data->reg_field.key.size = sizeof(int);
    }
    else if(!strncmp(str+1, "float", 5)){ 
        data->reg_field.key.data_type = FLOAT;
        data->reg_field.key.size = sizeof(float);
    }
    else if(!strncmp(str+1, "double", 6)){ 
        data->reg_field.key.data_type = DOUBLE;
        data->reg_field.key.size = sizeof(double);
    }
    else if(!strncmp(str+1, "char", 4)){ 
        data->reg_field.key.data_type = CHAR;
        char *size_aux = strdup(str+6); //Achando o tamanho do char
        size_aux[2] = '\0'; //Tirando o último ']'
        int size = atoi(size_aux); //Salvando como inteiro a string do tamanho
        data->reg_field.key.size = sizeof(char) * size;
        free(size_aux); //Liberando a memória usada na variável auxiliar
    }

    //Descobrindo quantos campos são e allocando
    int words = (count - 3) / 2;
    data->reg_field.fields = (FIELDS*) calloc(words, sizeof(FIELDS)); 

    //Salvando os campos dos registros, começamos na posição 3 pois é onde começam
    for (int i = 3, j = 0; i < count; i++){
        //Salvando os nomes, toda linha ímpar contem o nome do campo
        if ((i % 2) != 0){
            str = index(aux[i], ' ');
            data->reg_field.fields[j].type.str = strdup(str+1);
        }
        //Salvando o tipo do dado e o tamanho
        else {
            str = index(aux[i], ' ');
            if(!strncmp(str+1, "int", 3)){ 
                data->reg_field.fields[j].data_type = INT;
                data->reg_field.fields[j].size = sizeof(int);
            }
            else if(!strncmp(str+1, "float", 5)){ 
                data->reg_field.fields[j].data_type = FLOAT;
                data->reg_field.fields[j].size = sizeof(float);
            }
            else if(!strncmp(str+1, "double", 6)){ 
                data->reg_field.fields[j].data_type = DOUBLE;
                data->reg_field.fields[j].size = sizeof(double);
            }
            else if(!strncmp(str+1, "char", 4)){ 
                data->reg_field.fields[j].data_type = CHAR;
                char *size_aux = strdup(str+6); //Achando o tamanho do char
                int a = atoi(size_aux); //Salvando como inteiro a string do tamanho
                data->reg_field.fields[j].size = sizeof(char) * a;
                free(size_aux); //Liberando a memória usada na variável auxiliar
            }
            j++;
        }
    }

    return data;
}

//Função que cria o arquivo .reg
void createRegArchive(DATABASE *data, int count, FILE* regarchive){
    //Descobrindo quantos bytes escrever
    int size = data->regs[data->howmanyregs].key.size;

    //Escrevendo a chave baseado em seu tipo
    if (data->regs[data->howmanyregs].key.data_type == INT){
        fwrite(&data->regs[data->howmanyregs].key.type.i, sizeof(char), size, regarchive);
    }
    else if (data->regs[data->howmanyregs].key.data_type == FLOAT){        
        fwrite(&data->regs[data->howmanyregs].key.type.f, sizeof(char), size, regarchive);
    }
    else if (data->regs[data->howmanyregs].key.data_type == DOUBLE){
        fwrite(&data->regs[data->howmanyregs].key.type.d, sizeof(char), size, regarchive);
    }
    else if (data->regs[data->howmanyregs].key.data_type == CHAR){
        fwrite(&data->regs[data->howmanyregs].key.type.str, sizeof(char), size, regarchive);
    }

    //Escrevendo os campos
    for (int i = 0; i < (count - 3) / 2; i++){
        int fs = data->regs[data->howmanyregs].fields[i].size; //fs == field size
        if (data->regs[data->howmanyregs].fields[i].data_type == INT){
            fwrite(&data->regs[data->howmanyregs].fields[i].type.i, sizeof(char), fs, regarchive);
        }
        else if (data->regs[data->howmanyregs].fields[i].data_type == FLOAT){
            fwrite(&data->regs[data->howmanyregs].fields[i].type.f, sizeof(char), fs, regarchive);
        }
        else if (data->regs[data->howmanyregs].fields[i].data_type == DOUBLE){
            fwrite(&data->regs[data->howmanyregs].fields[i].type.d, sizeof(char), fs, regarchive);
        }
        else if (data->regs[data->howmanyregs].fields[i].data_type == CHAR){
            fwrite(data->regs[data->howmanyregs].fields[i].type.str, sizeof(char), fs, regarchive);
        }
    }
}

//Função de inserção dos dados
DATABASE* insertData(DATABASE *data, char *string, int count, FILE* regarchive){
    //Descobrindo a quantidade de campos de cada registro
    int words = (count - 3) / 2;

    //Alocando os registros
    data->regs = (REGISTER*) realloc (data->regs, (data->howmanyregs + 1) * sizeof(REGISTER));
    //Alocando a quantidade de campos em cada registro
    data->regs[data->howmanyregs].fields = (FIELDS*) calloc (words, sizeof(FIELDS));

    //Strings auxiliares para a copia dos registros
    char *keep = NULL, *str_aux;

    //Achando o valor da chave
    keep = strsep(&string, ",");

    // Salvando a chave
    data->regs[data->howmanyregs].key.data_type = data->reg_field.key.data_type;
    data->regs[data->howmanyregs].key.size = data->reg_field.key.size;
    if (data->regs[data->howmanyregs].key.data_type == INT){
        char *aux = strdup(index (keep, ' ')+1);
        data->regs[data->howmanyregs].key.type.i = atoi(aux);
        free(aux);
    }
    else if (data->regs[data->howmanyregs].key.data_type == FLOAT){
        char *aux = strdup(index (keep, ' ')+1);
        data->regs[data->howmanyregs].key.type.f = atof(aux);
        free(aux);
    }
    else if (data->regs[data->howmanyregs].key.data_type == DOUBLE){
        char *aux = strdup(index (keep, ' ')+1);
        data->regs[data->howmanyregs].key.type.d = (double) atof(aux);
        free(aux);
    }
    else if (data->regs[data->howmanyregs].key.data_type == CHAR){
        char *aux = strdup(index (keep, ' ')+1);
        data->regs[data->howmanyregs].key.type.str = strdup(aux);
        free(aux);
    }

    //Salvando o registro
    for (int i = 0; i < words; i++){
        //Salvando o tipo do registro
        data->regs[data->howmanyregs].fields[i].data_type = data->reg_field.fields[i].data_type;
        //Salvando o tamanho do campo
        data->regs[data->howmanyregs].fields[i].size = data->reg_field.fields[i].size;

        //Procurando o dado a ser salvo
        keep = strsep(&string, ",");
    
        //Tirando possíveis aspas
        if (keep[1] == '\"'){
            str_aux = strdup(keep+2);
            str_aux[strlen(str_aux) - 1] = '\0';
        }
        else {
            str_aux = strdup(keep+1);
        }

        //Descobrindo o tipo do campo e salvando        
        if (data->reg_field.fields[i].data_type == INT){
            data->regs[data->howmanyregs].fields[i].type.i = atoi(str_aux);
        }
        else if (data->reg_field.fields[i].data_type == FLOAT){
            data->regs[data->howmanyregs].fields[i].type.f = atof(str_aux);
        }
        else if (data->reg_field.fields[i].data_type == DOUBLE){
            data->regs[data->howmanyregs].fields[i].type.d = (double) atof(str_aux);
        }
        else if (data->reg_field.fields[i].data_type == CHAR){
            data->regs[data->howmanyregs].fields[i].type.str = (char*) calloc
                (data->reg_field.fields[i].size, sizeof(char));
            strcat(data->regs[data->howmanyregs].fields[i].type.str, str_aux);
        }

        //Liberando a memória auxiliar
        free(str_aux);
    }

    //Criando o arquivo
    createRegArchive(data, count, regarchive);

    //Aumentando em +1 para o próximo registro
    data->howmanyregs++;    

    return data;
} 

//Função que cria o arquivo .idx
void createIdxArchive(DATABASE *data, int count, FILE* idxarchive){
    int size = 0;

    for (int i = 0; i < data->howmanyregs; i++){    
        if (data->regs[i].key.data_type == INT){
            fwrite(&data->regs[i].key.type.i, sizeof(int), 1, idxarchive);
            fwrite(&data->offset[i], sizeof(int), 1, idxarchive);
        }
        else if (data->regs[i].key.data_type == FLOAT){
            fwrite(&data->regs[i].key.type.i, sizeof(float), 1, idxarchive);
            fwrite(&data->offset[i], sizeof(int), 1, idxarchive);            
        }
        else if (data->regs[i].key.data_type == DOUBLE){
            fwrite(&data->regs[i].key.type.i, sizeof(double), 1, idxarchive);
            fwrite(&data->offset[i], sizeof(int), 1, idxarchive);
        }
        else if (data->regs[i].key.data_type == CHAR){
            size = data->regs[i].key.size;
            fwrite(&data->regs[i].key.type.i, sizeof(char), size, idxarchive);
            fwrite(&data->offset[i], sizeof(int), 1, idxarchive);
        }
    }
}

//Função que calcula o offset padrão
DATABASE* patternOffset(DATABASE *data, int count){
    data->patternoffset = data->reg_field.key.size;
    
    for (int i = 0; i < (count - 3) / 2; i++){
        data->patternoffset += data->reg_field.fields[i].size;
    }
    
    data->offset = (int*) realloc (data->offset, (data->howmanyregs + 1) * sizeof(int));
    memset(&data->offset[data->howmanyregs], 0, sizeof(int));

    //Criando o vetor de offsets
    for (int i = 0; i < data->howmanyregs; i++){
        data->offset[i] = data->patternoffset * i;
    }

    return data;
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

//Função que printa o resultado da busca
void printResult(DATABASE *data, int result, int count){
    if (result != -1){
        for (int i = 0; i < (count - 3) / 2; i++){
            if (data->regs[result].fields[i].data_type == INT){
                printf("%s: %d\n", data->reg_field.fields[i].type.str, data->regs[result].fields[i].type.i);
            }
            else if (data->regs[result].fields[i].data_type == FLOAT){
                printf("%s: %.2f\n", data->reg_field.fields[i].type.str, data->regs[result].fields[i].type.f);
            }
            else if (data->regs[result].fields[i].data_type == DOUBLE){
                printf("%s: %.2lf\n", data->reg_field.fields[i].type.str, data->regs[result].fields[i].type.d);
            }
            else if (data->regs[result].fields[i].data_type == CHAR){
                printf("%s: %s\n", data->reg_field.fields[i].type.str, data->regs[result].fields[i].type.str);
            }
        }
        printf("\n");   
    }
}

//Função que faz a busca a partir de uma chave inteira
void intSearchArchive(DATABASE *data, int key, int count){
    //Ordenando os registros baseado na chave inteira
    qsort(data->regs, data->howmanyregs, sizeof(REGISTER), intCompare);

    //Criando um vetor auxiliar de ints para a busca
    int *key_aux = (int*) calloc (data->howmanyregs, sizeof(int));
    for (int i = 0; i < data->howmanyregs; i++){
        key_aux[i] = data->regs[i].key.type.i;
    }    

    //Fazendo a busca binária
    int result = intBinarySearch(key_aux, 0, data->howmanyregs - 1, key);
    printf("%s: %d\n", data->reg_field.key.type.str, key);
    printResult(data, result, count);
    free(key_aux);
}

//Função que faz a busca a partir de uma chave float
void floatSearchArchive(DATABASE *data, float key, int count){
    //Ordenando os registros baseado na chave float
    qsort(data->regs, data->howmanyregs, sizeof(REGISTER), fCompare);

    //Criando um vetor auxiliar de floats para a busca
    float *key_aux = (float*) calloc (data->howmanyregs, sizeof(float));
    for (int i = 0; i < data->howmanyregs; i++){
        key_aux[i] = data->regs[i].key.type.f;
    }    

    //Fazendo a busca binária em float
    int result = floatBinarySearch(key_aux, 0, data->howmanyregs - 1, key);
    printf("%s: %.2f\n", data->reg_field.key.type.str, key);
    printResult(data, result, count);
    free(key_aux);
}

//Função que faz a busca a partir de uma chave double
void doubleSearchArchive(DATABASE *data, double key, int count){
    //Ordenando os registros baseado na chave double
    qsort(data->regs, data->howmanyregs, sizeof(REGISTER), dCompare);

    //Criando um vetor auxiliar de doubles para a busca
    double *key_aux = (double*) calloc (data->howmanyregs, sizeof(double));
    for (int i = 0; i < data->howmanyregs; i++){
        key_aux[i] = data->regs[i].key.type.d;
    }    

    //Fazendo a busca binária em double
    int result = doubleBinarySearch(key_aux, 0, data->howmanyregs - 1, key);
    printf("%s: %.2lf\n", data->reg_field.key.type.str, key);
    printResult(data, result, count);
    free(key_aux);
}

//Funçao que faz a busca a partir de uma chave string
void stringSearchArchive(DATABASE *data, char *key, int count){
    //Ordenando os registros baseado na chave string
    qsort(data->regs, data->howmanyregs, sizeof(REGISTER), strCompare);

    //Criando um vetor auxiliar de strings para a busca
    char **key_aux = (char**) calloc (data->howmanyregs, sizeof(char*));
    for (int i = 0; i < data->howmanyregs; i++){
        key_aux[i] = strdup(data->regs[i].key.type.str);
    }

    //Fazendo a busca binária em string
    int result = stringBinarySearch(key_aux, 0, data->howmanyregs - 1, key);
    printf("%s: %s\n", data->reg_field.key.type.str, key);
    printResult(data, result, count);

    for (int i = 0; i < data->howmanyregs; i++){
        free(key_aux[i]);
    }
    free(key_aux);
}

//Função das operações
DATABASE* operations(DATABASE *data, int count, FILE* regarchive, FILE* idxarchive){
    //Criando a matrix de srtings auxiliares devido aos inserts
    char **aux2 = NULL;
    int counter = 0, aux2_null_line = 0;
    data->howmanyregs = 0;
    int has_idx = FALSE;

    //Alocando inicialmente os registros
    data->regs = NULL;

    //Lendo a entrada do stdin
    do {
        aux2 = (char**) realloc (aux2, (counter + 1) * sizeof(char*));
        aux2[counter] = readLine(stdin);

        //Descobrindo se é insert
        if (!strncmp(aux2[counter], "insert", strlen("insert"))){
            //Chamar a função de insert com a linha referente a esse insert
            data = insertData(data, aux2[counter], count, regarchive);
        }
        
        data = patternOffset(data, count);
        
        //Descobrindo se é uma busca
        if (!strncmp(aux2[counter], "search",strlen("search"))){
            if(!has_idx){
                createIdxArchive(data, count, idxarchive);
                has_idx = TRUE;
            }

            //if key == int
            if (data->reg_field.key.data_type == INT){
                char *str = index(aux2[counter], ' ');
                int key = atoi(str+1);
                intSearchArchive(data, key, count);
            }
            //if key == float
            else if (data->reg_field.key.data_type == FLOAT){
                char *str = index(aux2[counter], ' ');
                float key = atof(str+1);
                floatSearchArchive(data, key, count);
            }
            //if key == double
            else if (data->reg_field.key.data_type == DOUBLE){
                char *str = index(aux2[counter], ' ');
                double key = (double) atof(str+1);
                doubleSearchArchive(data, key, count);
            }
            //if key == str
            else if (data->reg_field.key.data_type == CHAR){
                char *key = strdup(index(aux2[counter], ' ')+1);
                stringSearchArchive(data, key, count);
                free(key);
            }
        } 

        if (!strncmp(aux2[counter], "index", strlen("index"))){
            createIdxArchive(data, count, idxarchive);
            has_idx = TRUE;
        }

        //Conta quantidade de linhas e linhas vazias
        if (strcmp(aux2[counter], "")) counter++;
        else if (!strcmp(aux2[counter], "")) aux2_null_line++;

    } while (strncmp(aux2[counter-1], "exit", strlen("exit")));

    //Liberando a matrix de strings auxiliar
    for (int i = 0; i < counter + aux2_null_line; i++){
        free(aux2[i]);
    }
    free(aux2);

    return data;
}

//Função que libera a memória heap
void freeData(DATABASE *data, char **aux, int count, int aux_null_line){
    for (int i = 0; i < count + aux_null_line; i++){
        free(aux[i]);
    }
    free(aux);
    for (int i = 0; i < (count - 3) / 2; i++){
        free(data->reg_field.fields[i].type.str);
    }
    for (int i = 0; i < data->howmanyregs; i++){
        for (int j = 0; j < (count - 3) / 2; j++){
            if (data->regs[i].fields[j].data_type == CHAR) free(data->regs[i].fields[j].type.str);
        }
    }
    for (int i = 0; i < data->howmanyregs; i++){
        if (data->regs[i].key.data_type == CHAR) free(data->regs[i].key.type.str);   
        free(data->regs[i].fields);
    }
    free(data->regs);
    free(data->reg_field.fields);
    free(data->reg_field.key.type.str);
    free(data->offset);
    free(data->datname);
    free(data->regname);
    free(data->regidx);
    free(data);
}

int main(){
    DATABASE *data;
    data = (DATABASE*) calloc (1, sizeof(DATABASE));

    //Criando a matriz de strings auxiliar
    char **aux = NULL;
    int count = 0, aux_null_line = 0;

    //Lendo o arquivo .dat
    aux = readDat(data, aux, &count, &aux_null_line);

    //Salvando o nome do registro que está na linha 0 da matriz
    regName(data, aux[0]);

    //Função que cria a struct onde serão salvos os dados
    data = createRegFields(data, aux, count);

    //Criando o ponteiro para o arquivo
    FILE *regarchive;
    regarchive = fopen(data->regname, "wb");

    FILE *idxarchive;
    idxarchive = fopen(data->regidx, "wb");

    //Função das operações
    data = operations(data, count, regarchive, idxarchive);

    //Liberando a memória heap
    freeData(data, aux, count, aux_null_line);

    //Fechando os arquivos
    fclose(regarchive);
    fclose(idxarchive);

    return 0;
}