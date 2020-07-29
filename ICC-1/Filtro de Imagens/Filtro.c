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
|    | Programa que faz um filtro de fotos com 2 filtros |    |
|    |___________________________________________________|    |
|_____________________________________________________________|
       |_______________________________________________|       
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Struct do cabeçalho do arquivo
typedef struct{
    char signature[2]; //Assinatura do arquivo, deve ser BM
    int file_size; //Tamanho do aquivo em bytes
    int reserved_field; //Deve ser 0
    int displacement; //Especifica o deslocamento até a área da imagem
} FILE_HEADER;

//Struct do mapa de bits
typedef struct{
    int header_size; //Tamanho desse cabeçalho
    int image_lenght; //Largura da imagem em pixels
    int image_height; //Altura da imagem em pixels
    short plan_number; //Deve ser 1
    short bits_per_pixel; //Será 8
    int compression; //Deve ser 0 pois não usaremos nenhuma compressão
    int image_size; //Tamanho dos dados da imagem, será do tamanho do arquivo
    int horizontal_pixel; //Resolução em pixel por metro na horizontal
    int vertical_pixel; //Resolução em pixel por metro na vertical
    int number_of_colors; //Se for 0 indica que o máx de cores é 2^bits_per_pixel
    int important_color_number; //Qnd 0 todas as cores são importantes
} BITMAP_HEADER;

//Struct da paleta de cores
typedef struct {
    int blue; //Intensidade de azul da imagem
    int green; //Intensidade de verde da imagem
    int red; //Intensidade de vermelho da imagem
    int opacity; //Deve ser sempre 0, pois é a opacidade da imagem, 0 = 100% visível
} COLOR_PALLET;

//Struct da Imagem
typedef struct{
    char *name; //Nome do arquivo
    int **image_matrix; //Matriz da imagem
    FILE_HEADER file_header; //Cabeçalho do arquivo
    BITMAP_HEADER bitmap_header; //Cabeçalho de bits
    COLOR_PALLET *pallet; //Paleta de cores
} IMAGE;

//Struct do filtro de imagens
typedef struct {
    IMAGE *image; //Struct da imagem original
    IMAGE *newimage; //Struct da imagem filtrada
    char *filename; //Nome do arquivo a ser aberto
    int filter_type; //Tipo do filtro
    long long int *lines_value; //Vetor que guarda o valor de cada linha
} FILTER;

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

//Função que sai do programa desalocando a memória necessária
void exitProgram(int flag, FILTER *filter){
    //Arquivo não existente
    if (flag == 1){
        free(filter->filename);
        free(filter);
        exit(1);
    }
    //Nome do arquivo não é .bmp
    else if (flag == 2){
        free(filter->filename);
        free(filter);
        exit(1);
    }
    //Cabeçalho diferente de BM
    else if (flag == 3){
        free(filter->image);
        free(filter->filename);
        free(filter);
        exit(1);
    }
}

//Função que testa se o arquivo é do tipo bmp
void checkBMP(FILTER *filter){
    char *aux = NULL;
    aux = rindex(filter->filename, '.');
    if (strcmp(aux, ".bmp") != 0){
        printf("Arquivo nao eh do formato BMP\n");
        exitProgram(2, filter);
    }
}

//Função que testa a assinatura do arquivo
FILTER* checkSignature(FILTER *filter, FILE* archive){
    //Setando inicialmente 0 na memória
    memset(&filter->image->file_header.signature, 0, sizeof(int));
    //Lendo o cabeçalho do arquivo
    fread(&filter->image->file_header.signature, 2, sizeof(char), archive);
    
    //Checando se o arquivo é BMP
    if (strcmp(filter->image->file_header.signature, "BM") != 0){
        printf("Arquivo nao eh do formato BMP\n");
        exitProgram(3, filter);
    }

    return filter;
}

//Função que le o cabeçalho e salva na struct
FILTER* readHeader(FILTER *filter, FILE* archive){
    //Salvando o cabeçalho para a struct
    fread(&filter->image->file_header.file_size, sizeof(int), 1, archive);
    fread(&filter->image->file_header.reserved_field, sizeof(int), 1, archive);
    fread(&filter->image->file_header.displacement, sizeof(int), 1, archive);

    return filter;
}

//Função que le o cabeçalho de bits
FILTER* readBitHeader(FILTER *filter, FILE* archive){
    //Salvando o cabeçalho de bits para a struct
    fread(&filter->image->bitmap_header.header_size, sizeof(int), 1, archive);
    fread(&filter->image->bitmap_header.image_lenght, sizeof(int), 1, archive);
    fread(&filter->image->bitmap_header.image_height, sizeof(int), 1, archive);
    fread(&filter->image->bitmap_header.plan_number, sizeof(short), 1, archive);
    fread(&filter->image->bitmap_header.bits_per_pixel, sizeof(short), 1, archive);
    fread(&filter->image->bitmap_header.compression, sizeof(int), 1, archive);
    fread(&filter->image->bitmap_header.image_size, sizeof(int), 1, archive);
    fread(&filter->image->bitmap_header.horizontal_pixel, sizeof(int), 1, archive);
    fread(&filter->image->bitmap_header.vertical_pixel, sizeof(int), 1, archive);
    fread(&filter->image->bitmap_header.number_of_colors, sizeof(int), 1, archive);
    fread(&filter->image->bitmap_header.important_color_number, sizeof(int), 1, archive);    

    return filter;
}

//Função que le a paleta de cores
FILTER* readPallete(FILTER *filter, FILE* archive){
    //Alocando a memória necessária para a paleta de cores
    filter->image->pallet = (COLOR_PALLET*) calloc (256, sizeof(COLOR_PALLET));

    //Salvando a paleta de cores na struct, por estamos trabalhos com imagens BMP, sempre teremos 
    //256 cores na paleta
    for (int i = 0; i < 256; i++){
        fread(&filter->image->pallet[i].blue, sizeof(char), 1, archive);
        fread(&filter->image->pallet[i].green, sizeof(char), 1, archive);
        fread(&filter->image->pallet[i].red, sizeof(char), 1, archive);
        fread(&filter->image->pallet[i].opacity, sizeof(char), 1, archive);
    }

    return filter;
}

//Função que le a imagem
FILTER* readImage(FILTER *filter, FILE* archive, int *aux_height, int *aux_lenght){
    int aux = 0;
    *aux_height = filter->image->bitmap_header.image_height;
    *aux_lenght = filter->image->bitmap_header.image_lenght;

    //Testando se há padding, caso hava deixando a linha múltipla de quatro
    aux = (*aux_lenght % 4);
    if (aux != 0){
        *aux_lenght = *aux_lenght + (4 - aux);   
    }

    //Alocando a matriz da imagem
    filter->image->image_matrix = (int**) calloc (*aux_height, sizeof(int*));
    for (int i = 0; i < *aux_height; i++){
        filter->image->image_matrix[i] = (int*) calloc (*aux_lenght, sizeof(int));
    }

    //Lendo a matriz e salvando a posição da cor na paleta
    for (int i = *aux_height - 1; i >= 0; i--){
        for (int j = 0; j < *aux_lenght; j++){
            fread(&filter->image->image_matrix[i][j], sizeof(char), 1, archive);
            //Para as linhas que contém lixo o valor está sendo trocado para 256, fora da paleta com
            //o intuito de facilitar na soma das linha, estamos procurando por linhas com valores 
            //menores que 0 pois estamos subtraindo o valor inicial da imagem pelo j, por exemplo,
            //422 - 423, nesse caso temos a última posíção de uma imagem com padding e valores <= 0,
            //são os valores onde terá lixo 
            if ((filter->image->bitmap_header.image_lenght - j) <= 0){
                filter->image->image_matrix[i][j] = 256;
            }
        }
    }

    return filter;
}

//Função que descobre o valor de cada linha
FILTER* calculateLine(FILTER *filter, int height, int lenght){
    filter->lines_value = (long long int*) calloc (height, sizeof(long long int));
    for (int i = 0; i < height; i++){
        for (int j = 0; j < lenght; j++){
            if (filter->image->image_matrix[i][j] >= 0 && filter->image->image_matrix[i][j] <= 255){
                filter->lines_value[i] += filter->image->image_matrix[i][j];
            }
            if (filter->image->image_matrix[i][j] == 256){
                filter->lines_value[i] -= 1;
            }
        }
    }

    return filter;
}

//Função que cria a paleta de cores negativas
FILTER* negativePallete(FILTER *filter){
    //Calculando as novas cores da paleta da nova imagem
    for (int i = 0; i < 256; i++){
        filter->newimage->pallet[i].blue = (255 - filter->image->pallet[i].blue);
        filter->newimage->pallet[i].green = (255 - filter->image->pallet[i].green);
        filter->newimage->pallet[i].red = (255 - filter->image->pallet[i].red);
        filter->newimage->pallet[i].opacity = 0;
    }

    return filter;
}

//Função que cria a paleta de cores preto e branco
FILTER* blackwhitePallete(FILTER *filter){
    int aux = 0;
    //Calculando as novas cores da paleta da nova imagem
    for (int i = 0; i < 256; i++){
        //Como a opacidade sempre será 0 não levaremos em conta na conta da escala de cinza
        aux = (filter->image->pallet[i].red + filter->image->pallet[i].green + filter->image->pallet[i].blue)/3;
        filter->newimage->pallet[i].red = aux;
        filter->newimage->pallet[i].green = aux;
        filter->newimage->pallet[i].blue = aux;
        filter->newimage->pallet[i].opacity = aux;
    }

    return filter;
}

//Função que guarda ou nomeia o nome da imagem, dependendo de qual seja
FILTER* nameImage(FILTER *filter){
    //Guardando o nome da imagem na struct da imagem
    filter->image->name = strdup(filter->filename);

    //Guardando apenas o nome antes do bmp em variável auxiliar
    char *aux = rindex(filter->filename, '.');
    int size = strlen(filter->filename) - strlen(aux);

    //Descobrindo qual o nome da imagem alterada, caso 1 Negativo, caso 2 PretoBranco
    if (filter->filter_type == 1){
        int size2 = size + strlen("Negativo.bmp");
        filter->newimage->name = (char*) calloc ((size2+1), sizeof(char)); //Alocando a memória
        memcpy(filter->newimage->name, filter->filename, size); //Copiando o nome original
        strcat(filter->newimage->name, "Negativo.bmp"); //Adicionando o nome do filtro
        filter->newimage->name[size2] = '\0'; //Setando \0 no fim para transformar em string
    }
    if (filter->filter_type == 2){
        int size2 = size + strlen("PretoBranco.bmp");
        filter->newimage->name = (char*) calloc ((size2+1), sizeof(char)); //Alocando a memória
        memcpy(filter->newimage->name, filter->filename, size); //Copiando o nome original
        strcat(filter->newimage->name, "PretoBranco.bmp"); //Adicionando o nome do filtro
        filter->newimage->name[size2] = '\0'; //Setando \0 no fim para transformar em string
    }

    return filter;
}

//Função que copia os cabeçalhos para a nova imagem
FILTER* copyHeaders(FILTER *filter){
    //Copiando o cabeçalho inicial
    filter->newimage->file_header.signature[0] = filter->image->file_header.signature[0];
    filter->newimage->file_header.signature[1] = filter->image->file_header.signature[1];
    filter->newimage->file_header.file_size = filter->image->file_header.file_size;
    filter->newimage->file_header.reserved_field = filter->image->file_header.reserved_field;
    filter->newimage->file_header.displacement = filter->image->file_header.displacement;

    //Copiando o cabeçalho de bytes
    filter->newimage->bitmap_header.header_size = filter->image->bitmap_header.header_size;
    filter->newimage->bitmap_header.image_lenght = filter->image->bitmap_header.image_lenght;
    filter->newimage->bitmap_header.image_height = filter->image->bitmap_header.image_height;
    filter->newimage->bitmap_header.plan_number = filter->image->bitmap_header.plan_number;
    filter->newimage->bitmap_header.bits_per_pixel = filter->image->bitmap_header.bits_per_pixel;
    filter->newimage->bitmap_header.compression = filter->image->bitmap_header.compression;
    filter->newimage->bitmap_header.image_size = filter->image->bitmap_header.image_size;
    filter->newimage->bitmap_header.horizontal_pixel = filter->image->bitmap_header.horizontal_pixel;
    filter->newimage->bitmap_header.vertical_pixel = filter->image->bitmap_header.vertical_pixel;
    filter->newimage->bitmap_header.number_of_colors = filter->image->bitmap_header.number_of_colors;
    filter->newimage->bitmap_header.important_color_number = filter->image->bitmap_header.important_color_number;

    return filter;
}

//Função que copia os valores da imagem original para a nova imagem
FILTER* newImageMatrix(FILTER* filter, int height, int lenght){
    //Alocando a matriz da nova imagem
    filter->newimage->image_matrix = (int**) calloc (height, sizeof(int*));
    for (int i = 0; i < height; i++){
        filter->newimage->image_matrix[i] = (int*) calloc (lenght, sizeof(int));
    }
    
    //Salvando os valores na matriz da nova imagem igualmente lida no arquivo
    for (int i = height - 1; i >= 0; i--){
        for (int j = 0; j < lenght; j++){
            filter->newimage->image_matrix[i][j] = filter->image->image_matrix[i][j];
        }
    }

    return filter;
}

//Função que cria o arquivo
void createImage(FILTER *filter, FILE* newimage, int height, int lenght){

    //Criando a nova imagem
    fwrite(&filter->newimage->file_header.signature, sizeof(char), 2, newimage);
    fwrite(&filter->newimage->file_header.file_size, sizeof(int), 1, newimage);
    fwrite(&filter->newimage->file_header.reserved_field, sizeof(int), 1, newimage);
    fwrite(&filter->newimage->file_header.displacement, sizeof(int), 1, newimage);
    fwrite(&filter->newimage->bitmap_header.header_size, sizeof(int), 1, newimage);
    fwrite(&filter->newimage->bitmap_header.image_lenght, sizeof(int), 1, newimage);
    fwrite(&filter->newimage->bitmap_header.image_height, sizeof(int), 1, newimage);
    fwrite(&filter->newimage->bitmap_header.plan_number, sizeof(short), 1, newimage);
    fwrite(&filter->newimage->bitmap_header.bits_per_pixel, sizeof(short), 1, newimage);
    fwrite(&filter->newimage->bitmap_header.compression, sizeof(int), 1, newimage);
    fwrite(&filter->newimage->bitmap_header.image_size, sizeof(int), 1, newimage);
    fwrite(&filter->newimage->bitmap_header.horizontal_pixel, sizeof(int), 1, newimage);
    fwrite(&filter->newimage->bitmap_header.vertical_pixel, sizeof(int), 1, newimage);
    fwrite(&filter->newimage->bitmap_header.number_of_colors, sizeof(int), 1, newimage);
    fwrite(&filter->newimage->bitmap_header.important_color_number, sizeof(int), 1, newimage);
    for (int i = 0; i < 256; i++){
        fwrite(&filter->newimage->pallet[i].blue, sizeof(char), 1, newimage);
        fwrite(&filter->newimage->pallet[i].green, sizeof(char), 1, newimage);
        fwrite(&filter->newimage->pallet[i].red, sizeof(char), 1, newimage);
        fwrite(&filter->newimage->pallet[i].opacity, sizeof(char), 1, newimage);
    }
    for (int i = height -1; i >= 0; i--){
        for (int j = 0; j < lenght; j++){
            fwrite(&filter->newimage->image_matrix[i][j], sizeof(char), 1, newimage);
        }
    }
}

//Função que printa as saídas
void printResults(FILTER *filter){
    printf("CABECALHO:\n");
    printf("Iniciais: %s\n", filter->image->file_header.signature);
    printf("Tamanho do arquivo: %d\n", filter->image->file_header.file_size);
    printf("Reservado: %d\n", filter->image->file_header.reserved_field);
    printf("Deslocamento, em bytes, para o inicio da area de dados: %d\n", 
        filter->image->file_header.displacement);
    printf("Tamanho em bytes do segundo cabecalho: %d\n", filter->image->bitmap_header.header_size);
    printf("Resolucao: %d x %d\n", filter->image->bitmap_header.image_lenght, 
        filter->image->bitmap_header.image_height);
    printf("Numero de planos: %d\n", filter->image->bitmap_header.plan_number);
    printf("Bits por pixel: %d\n", filter->image->bitmap_header.bits_per_pixel);
    printf("Compressao usada: %d\n", filter->image->bitmap_header.compression);
    printf("Tamanho imagem: %d\n", filter->image->bitmap_header.image_size);
    printf("Resolucao horizontal: %d pixel por metro\n", filter->image->bitmap_header.horizontal_pixel);
    printf("Resolucao Vertical: %d pixel por metro\n", filter->image->bitmap_header.vertical_pixel);
    printf("Numero de cores usadas: %d\n", filter->image->bitmap_header.number_of_colors);
    printf("Numero de cores importantes: %d\n", filter->image->bitmap_header.important_color_number);
    printf("PALETA ORIGINAL:\n");
    for (int i = 0; i < 256; i++){
        printf("Paleta[%d]: ", i);
        printf("R:%d ", filter->image->pallet[i].red);
        printf("G:%d ", filter->image->pallet[i].green);
        printf("B:%d\n", filter->image->pallet[i].blue);
    }
    printf("PALETA NOVA:\n");
    for (int i = 0; i < 256; i++){
        printf("Paleta[%d]: ", i);
        printf("R:%d ", filter->newimage->pallet[i].red);
        printf("G:%d ", filter->newimage->pallet[i].green);
        printf("B:%d\n", filter->newimage->pallet[i].blue);
    }

    for (int i = 0; i < filter->image->bitmap_header.image_height; i++){
        printf("Soma linha %d: %lld\n", i, filter->lines_value[i]);        
    }
    printf("%s\n", filter->newimage->name);
}

//Função que desaloca a memória heap
void desalocateHeap(FILTER *filter){
    for (int i = 0; i < filter->image->bitmap_header.image_height; i++){
        free(filter->image->image_matrix[i]);
    }
    free(filter->image->image_matrix);
    for (int i = 0; i < filter->newimage->bitmap_header.image_height; i++){
        free(filter->newimage->image_matrix[i]);
    }
    free(filter->newimage->image_matrix);
    free(filter->lines_value);
    free(filter->image->name);
    free(filter->image->pallet);
    free(filter->image);
    free(filter->newimage->name);
    free(filter->newimage->pallet);   
    free(filter->newimage);
    free(filter->filename); 
    free(filter);
}

int main (){
    //Criando a struct que armazenará os dados e allocando na memória heap
    FILTER *filter;
    filter = (FILTER*) malloc (1 * sizeof(FILTER));

    //Lendo o nome do arquivo e o tipo de filtro
    filter->filename = readLine(stdin);
    scanf("%d", &filter->filter_type); //1 = foto negativa, 2 = foto preta e branca
    
    //Checando se o arquivo é do tipo .bmp
    checkBMP(filter);

    //Criando um ponteiro do tipo FILE para mexer com o arquivo
    FILE *archive;
    archive = fopen(filter->filename, "rb"); //Abrindo para leitura binária
    
    //Testando a existência do arquivo
    if (archive == NULL){
        printf("Erro no arquivo\n");
        exitProgram(1, filter);
    }

    //Allocando a struct IMAGE para a imagem original
    filter->image = (IMAGE*) malloc (1 * sizeof(IMAGE));
    
    //Testando a assinatura do arquivo
    filter = checkSignature(filter, archive);

    //Lendo o cabeçalho da imagem
    filter = readHeader(filter, archive);
    
    //Lendo o cabeçalho de bits
    filter = readBitHeader(filter, archive);

    //Ler a paleta de cores
    filter = readPallete(filter, archive);

    //Variaveis auxiliares para ajudar em caso de padding
    int aux_height, aux_lenght;

    //Ler a imagem
    filter = readImage(filter, archive, &aux_height, &aux_lenght);

    //Após ler e salvar toda a imagem podemos fechar seu arquivo
    fclose(archive);

    //Calcula o valor das linhas
    filter = calculateLine(filter, aux_height, aux_lenght);

    //Alocando a nova imagem
    filter->newimage = (IMAGE*) malloc (1 * sizeof(IMAGE));
    filter->newimage->pallet = (COLOR_PALLET*) calloc (256, sizeof(COLOR_PALLET));

    //Criando a nova paleta
    if (filter->filter_type == 1){
        filter = negativePallete(filter);
    }
    else if(filter->filter_type == 2){
        filter = blackwhitePallete(filter);
    }

    //Definindo os nomes do arquivos, na struct, para as imagens
    filter = nameImage(filter);

    //Copiando os cabeçalhos da imagem original para a nova imagem
    filter = copyHeaders(filter);

    //Copiando a imagem para a struct da nova imagem
    filter = newImageMatrix(filter, aux_height, aux_lenght);

    //Função que printa as saídas
    printResults(filter);

    //Criando um novo ponteiro do tipo file para criar o novo arquivo
    FILE* newimage;
    newimage = fopen(filter->newimage->name, "wb");

    //Criando o novo arquivo
    createImage(filter, newimage, aux_height, aux_lenght);
    
    //Fechando o novo arquivo
    fclose(newimage);

    //Desalocando a memória heap
    desalocateHeap(filter);

    return 0;
}
