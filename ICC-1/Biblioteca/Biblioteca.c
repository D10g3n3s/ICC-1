/*
    ICMC USP - Diógenes Silva Pedro - BCC 020
    Programa que cria uma Biblioteca
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Definindo macros
#define TRUE 1
#define FALSE 0
#define EMPTY -1

//Definindo structs que contém os dados dos livros e da biblioteca
typedef struct{
    char *book_name;
    int rent_days;
    int is_rented;
} Books;
 
typedef struct {
    Books *book;
    int how_many_books;
    int *order;
} Library;

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

    } while (str[pos-1] != '\r' && str[pos-1] != '\n' && !feof(stream));
    
    str[pos-1] = '\0';
    str = realloc (str, pos);

    return str;
}

//Função para alugar livros
Library rentBooks(Library lib){

    //Definindo uma string, que será lida na função readline, para buscar um livro na biblioteca
    //para ser alugado
    char *search;
    printf("Digite o livro que voce procura:\n");
    search = readline(stdin);

    //Descobrindo em qual posição está o livro procurado, essa posição será guardada na variável pos 
    //ela será usada para guardar a ordem em que os livros aparecem
    int i = 0, pos, isBook = FALSE;
    while (i < lib.how_many_books) {
        if(!strcmp (search, lib.book[i].book_name)){
             pos = i; 
             isBook = TRUE; //Definindo que o livro foi encontrado
             break;
        }
        i++;
    } 

    //Caso o livro não seja encontrado printaremos para que o usuário saiba
    if (isBook == FALSE){
        printf("Livro nao encontrado na biblioteca\n");        
    }

    //Porém caso o livro seja encontrado temos que testar quantos livros alugados ele tem
    else {
        //Caso ele tenha 10 livros alugados ele n poderá mais pegar livros
        if (lib.order[9] != EMPTY) printf("Voce ja tem 10 livros alugados\n");
        
        //Caso ele não tenha 10 livros o livro será alugado
        else {
            //Caso o usuário já tenha aquele livro alugado ele será avisado
            if (lib.book[pos].is_rented != FALSE) printf("Livro ja alugado\n");
            //Caso o usuário ainda não tenha o livro alugado salvaremos o livro no primeiro índice
            //do vetor order, guardando no índice a posição do livro, guardada na variável pos e
            //transformando a variável is_rented em TRUE, para dizer que o livro foi alugado e não
            //pode ser realugado
            else {
                i = 0;
                while (lib.order[i] != EMPTY) i++;
                lib.order[i] = pos;
                lib.book[pos].is_rented = TRUE; 
                printf("%s alugado com sucesso\n", search);           
            }
        }
    }

    //Liberando da memória heap a string que continha o livro a ser buscado
    free(search);
    return lib;
}

//Função que mostrará os livros alugados
void showBooks (Library lib){
    int i = 0, count;
    //Testando para ver caso a pessoa não tenha livro algum alugado
    if (lib.order[i] == EMPTY) printf("Voce nao tem livros alugados\n");

    //Caso a pessoa tenha algum livro alugado mostraremos esses livros e quntos são
    else {
        while (lib.order[i] != EMPTY && i < 10){
            count = i+1;
            i++;
        }
        printf("Voce tem %d livro(s) alugado(s)\n", count);
        //A ordem dos livros é definida pelos índices da variável order, onde cada índice guarda uma
        //posição, por exemplo em lib.order[0] poderemos ter o valor 3, que se refere ao livro na 3°
        //posição, ou seja, o 3° livro digitado, com isso procuraremos o lib.book[3], assim os temos
        //todos os livros sendo mostrados na ordem em que foram alugados
        for (int j = 0; j < count; j++){
            printf("Livro nome: %s\n", lib.book[lib.order[j]].book_name);
            printf("Devolve-lo daqui %d dias\n", lib.book[lib.order[j]].rent_days);
        }
    }
}

//Função que devolve os livros para a biblioteca
Library returnBooks (Library lib){

    //Definindo uma string que procurará o livro a ser devolvido dentro dos livros alugados
    char *search;
    printf("Digite o livro que deseja devolver:\n");
    search = readline(stdin);

    //Tentando achar o livro dentro dos livros alugados, caso encontrado o livro salvaremos qual a 
    //sua posição, assim como na função de aluguel
    int i = 0, pos, isRented = FALSE;
    while (lib.order[i] != EMPTY && i < 10) {
        if(!strcmp (search, lib.book[lib.order[i]].book_name)){
             pos = i; 
             isRented = TRUE;
             break;
        }
        i++;
    } 

    //Testando para ver se o livro está ou não alugado, o único jeito para o livro não estar alugado
    //e que o usuário não o pegou na biblioteca
    if (isRented == FALSE){
        printf("Voce nao possui esse livro\n");        
    }

    //Caso o livro esteja alugado devolveremos o livro a biblioteca e mudaremos a ordem dos livros
    //para que quando seja feita uma impressão dos livros eles continuam com a ordem certa baseada 
    //na ordem em que foram alugados 
    else {
        //Definindo que o livro não está mais alugado
        lib.book[lib.order[pos]].is_rented = FALSE;
        printf("Livro %s foi devolvido com sucesso\n", lib.book[lib.order[pos]].book_name);
        int new = 0, old = 0;
        //Trocando a variavel order para ter uma nova ordem de índices baseada apenas nos livros
        //restantes, como já desalugamos o livro, testaremos todos os livros ainda alugados e com os
        //indices dos livros antigos ainda alugados colocaremos eles em novos indicies, trocando 
        //assim a ordem da variavel order
        while (lib.order[old] != EMPTY && old < 10){
            if (lib.book[lib.order[old]].is_rented == TRUE){
                lib.order[new] = lib.order[old];
                new++;
            }
            old++;
        }
        lib.order[new] = EMPTY;
    }

    //Desalocando a memória da string usada para procurar o livro para devolver
    free(search);
    return lib;
}

//Função que desaloca memória e printa a mensagem final
void closeLib(Library lib){
    for (int i = 0; i < lib.how_many_books; i++){
        free(lib.book[i].book_name);
    }
    free(lib.book);
    free(lib.order);
    printf("Programa finalizado\n");
}

int main(){
    
    //Criando a variável do tipo Library definida pela struct
    Library lib;

    //Descobrindo a quantidade de livros a ser registrados na biblioteca
    scanf("%d\r\n", &lib.how_many_books);

    //Alocando memória para o ponteiro que receberá os nomes dos livros
    lib.book = (Books*) malloc (lib.how_many_books * sizeof(Books));
    //Definindo um tamanho de 10 inteiros para a variável order na heap
    lib.order = (int*) malloc (10 * sizeof(int)); 

    //Lendo os nomes dos livros e por quantos dias podem ser alugados, além de setar todos como não
    //alugados
    for (int i = 0; i < lib.how_many_books; i++){
        lib.book[i].book_name = readline(stdin);
        scanf("%d\r\n", &lib.book[i].rent_days);
        lib.book[i].is_rented = FALSE;
    }

    //Definindo como EMPTY toda a variável order
    for (int i = 0; i < 10; i++){
        lib.order[i] = EMPTY;
    }

    int operation = 0;

    //Loop onde funcionará a biblioteca
    do {       
        //Lendo qual operação o usuário deseja
        scanf("%d\r\n", &operation);

        //Chamando a função que alugará livros
        if (operation == 1) lib = rentBooks(lib);

        //Chamando a função que mostrará os livros alugados
        else if (operation == 2) showBooks(lib);

        //Chamando a função que devolverá os livros alugados
        else if (operation == 3) lib = returnBooks(lib);

    } while (operation != 4);

    //Desalocando a memória heap usada pela struct
    closeLib(lib);
    return 0;
}
