/*
    ICMC USP - Diógenes Silva Pedro - BCC 020
*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <ctype.h>

//Criando a função que comparará as palavras
void Compara(int op, char pal1[15], char pal2[15]){
    
    /*
    Casos possíveis:
        1 - Qual palavra tem maior tamanho
        2 - Ordem Alfabética
        3 - Qual palavra apresenta maior soma dos valores das letras (A = 0 até Z = 25)
        4 - Qual das palavras tem mais repetições de uma determinada letra
        5 - Em qual das palavras uma determinada letra aparece primeiro (se a letra procurada for a segunda da palavra 1 e a terceira da palavra 2, a palavra 1 ganhou a comparação)
    */

    //Definindo a variável que mostrará qual palavra venceu a comparação, na forma de número inteiro
    int resultado;

    //Definindo variáveis que adquirão o tamanho das palavras, para o caso 1
    int tp1, tp2;

    tp1 = strlen (pal1);
    tp2 = strlen (pal2);

    //Caso 1: usarei strlen para comparar o tamanho das palavras, caso a primeira palavra seja maior o programa aprensentará 1, caso a palavra 2 seja maior 2 e se tiverem o mesmo tamanho 0
    if (op == 1){
        if (tp1 > tp2){ //Palavra 1 maior que palavra 2
            resultado = 1;
        }
        else if(tp1 < tp2){ //Palavra 2 maior que palavra 1
            resultado = 2;
        }
        else { //Palavras tendo o mesmo tamanho
            resultado = 0;
        }

        //Mostrando para o usuário a saida esperada
        printf("%d\n", resultado);
    }

    //Caso 2
    else if (op == 2){ 

        //Comparando qual palavra virá primeiro na ordem alfabética
        if (strcasecmp(pal1,pal2) < 0){ 
            resultado = 1;
        }
        else if (strcasecmp(pal2,pal1) < 0){
            resultado = 2;
        }
        else {
            resultado = 0;
        }

        //Printando o resultado para o usuário
        printf("%d\n", resultado);    
    }

    //Caso 3
    else if (op == 3){
        
        //Definindo a variável que armazenará a diferença entre os tamanhos das strings
        int resultado; 

        //Criando variáveis que receberão o valor de cada caracter da palavra
        char p1, p2;

        //Criando variáveis que armazenaram o tamanho da string
        int s1 = 0, s2 = 0;

        //Fazendo um loop para descobrir o quanto vale cada palavra        
        for (int i = 0; i < strlen(pal1); i++){
            p1 = toascii(tolower (pal1[i])) - 97;
            s1 = s1 + p1;
        }

        for (int i = 0; i < strlen(pal2); i++){
            p2 = toascii(tolower (pal2[i])) - 97;
            s2 = s2 + p2;
        }
        
        //Testando qual das palavras apresenta a maior soma
        if (s1 > s2) { 
            resultado = 1;
        }
        else if (s1 == s2) {
            resultado = 0;            
        }
        else {
            resultado = 2;
        }

        //Printando a string com maior soma
        printf("%d\n", resultado);
    }

    //Caso 4
    else if (op == 4){

        //Definindo variáveis auxiliares para testar qual palavra terá mais letras repetidas 
        char p1, p2; //Caractere que receberá o caracter da string dentro de um laço de repetição
        int n1 = 0, n2 = 0; //Variável que guardará quantas vezes o caracter se repetiu em cada palavra
        int t1, t2; //Variáveis inteiras que guardarão o valor do tamanho da string
        char letra, letram; //Letra receberá a letra especificada pelo usuário e letram guardará a a mesma letra em formato minúsculo

        scanf(" %c", &letra); //O espaço antes do %c evita com que seja salva na variável letra o \n, que provem de apertar enter após o usuário digitar as palavras a serem comparadas 
        letram = tolower(letra); 

        t1 = strlen(pal1);
        t2 = strlen(pal2);
            
        //Laço de repetição para testar todos os caracteres da palavra 1
        for (int i = 0; i < t1; i++){
            p1 = tolower(pal1[i]);
            //Caso o caracter seja igual a letra escolhida pelo usuário a variável adiciona 1 a contagem
            if (p1 == letram){
                n1 += + 1;
            }
        }
        
        //Laço de repetição para testar todos os caracteres da palvra 2
        for (int i = 0; i < t2; i++){
            p2 = tolower(pal2[i]);
            //Caso o caracter seja igual a letra escolhida pelo usuário a variável adiciona 1 a contagem
            if (p2 == letram){
                n2 += + 1;
            }
        }

        //Testando qual das palavras teve a maior quantidades da letra escohida
        if (n1 > n2){
            resultado = 1;
        }
        else if (n1 == n2){
            resultado = 0;
        }
        else {
            resultado = 2;
        }

        //Printando na tela qual foi a palavra que teve mais repetições da letra escolhida
        printf("%d\n", resultado);
    }

    //Caso 5
    else {

        //Definindo variáveis auxiliares para ajudar no teste de qual letra vem primeiro
        char p1, p2; //Caractere que receberá os caracteres da palavra dita pelo usuário para comparar com a letra escrita pelo usuário 
        int t1, t2; //Variável inteira que guardará o tamanho da palavra que definirá quantas vezes o laço de repetição tem que testar a palavra, procurando a letra esepcificada
        int n1 = 0, n2 = 0; //Variável que guardará a posição da letra especificada pelo usuário
        char letra; //Letra receberá a letra especificada pelo usuário e letram guardará a a mesma letra em formato minúsculo
        
        scanf(" %c", &letra); //Recebendo a letra especificada pelo usuário

        //Definindo o tamanho da palavra
        t1 = strlen(pal1);
        t2 = strlen(pal2);

        //Laço de repetição para testar todos os caracteres da palvra 2
        for (int i = 0; i < t1; i++){
            p1 = tolower(pal1[i]);
            //Caso o caracter seja igual a letra escolhida pelo usuário a variável guardará em qual posição esse caso foi verdadeiro 
            if ((int) p1 == tolower(letra)){
                n1 = i;
                break;
            }
        }

        //Laço de repetição para testar todos os caracteres da palvra 2
        for (int i = 0; i < t2; i++){
            p2 = tolower(pal2[i]);
            //Caso o caracter seja igual a letra escolhida pelo usuário a variável guardará em qual posição esse caso foi verdadeiro
            if ((int) p2 == tolower(letra)){
                n2 = i;
                break;
            }
        }
        
        //Testando qual das letras vem primeiro
        if (n1 < n2){
            resultado = 1;
        }
        else if (n1 == n2){
            resultado = 0;
        }
        else {
            resultado = 2;
        }

        //Mostrando para o usuário qual foi a palavra vencedora
        printf("%d\n", resultado);
    }

}

int main(){

    //Definindo a variável que será utilizada para escolher a opção
    int op;

    //Definindo as variáveis que armazenaram as palavras
    char pal1[15], pal2[15];

    //Descobrindo qual opção o usuário selecionou
    scanf("%d", &op);   
    
    //Descobrindo as palavras que o usuário 
    scanf("%s", pal1);
    scanf("%s", pal2);

    Compara (op, pal1, pal2);

    return 0;
}    