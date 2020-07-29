#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <define.h>
#include <archive.h>
#include <utils.h>

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