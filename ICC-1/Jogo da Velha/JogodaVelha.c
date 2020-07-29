/*
    ICMC USP - Diógenes Silva Pedro - BCC 020
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Função para printar na tela para o usuário o estado atual do jogo
void Tabela(char *jv){
    printf("%c   |%c   |%c   |", jv[0], jv[1], jv[2]);
    printf("\n----+----+-----");
    printf("\n%c   |%c   |%c   |", jv[3], jv[4], jv[5]);
    printf("\n----+----+-----");
    printf("\n%c   |%c   |%c   |", jv[6], jv[7], jv[8]);
    printf("\n----+----+-----\n");
}

//Função que printará qual o jogador da vez
void Jogador(int player){
    
    player = (player % 2) ? 1 : 2; //Testando qual é o jogador

    if (player  == 1)
        printf("Escolha um número para jogar, jogador X!\n");   
    else 
        printf("Escolha um número para jogar, jogador O!\n");
}

//Função para receber as entradas dos jogadores
void Jogo(int player, char *jv){
    
    //Variáveis para fazer o teste de validade da jogada do jogador
    char marca, escolha;
    int teste = 0, aux = 0;

    //Loop para testar a validade da jogada do jogador
    do {
        //Lendo a escolha do jogador
        scanf(" %c", &escolha);
        
        //Definindo qual será o marcador do jogador
        marca = (player == 1) ? 'X' : 'O';

        //Testando para caso algum dos valores do vetor seja igual ao valor escolhido pelo usuário, se sim, o marcador é trocado pelo número daquela casa
        for (int i = 0; i < 9; i++){
            if (escolha == jv[i]){
                jv[i] = marca; //Recebendo o caracter que entrará no lugar do númerod desejado
                teste = 1; //Trocando o valor da variável teste para demonstrar que o teste é valido e não foi selecionada nenhuma casa errada
                aux = 1; //Trocando o valor da variável auxiliar para viabilizar que a jogada foi válida
                }
            } 

        //Caso o loop não tenha achado nenhum valor, a variável aux continuará 0, demonstrando que a jogada foi inválida
        if (aux == 0)
            printf("Jogada inválida! Escolha outra casa.\n");

    } while (teste == 0);
    
}

//Função para testar se algum dos jogadores venceu o jogo
int testeVitoria (char *jv) {
    int temp = -1;

        if ((jv[0] == jv[1] && jv[1] == jv[2]) || (jv[3] == jv[4] && jv[4] == jv[5]) || (jv[6] == jv[7] && jv[7] == jv[8])) //Teste Horizontal
            temp = 1;
        else if ((jv[0] == jv[3] && jv[3] == jv[6]) || (jv[1] == jv[4] && jv[4] == jv[7]) || (jv[2] == jv[5] && jv[5] == jv[8])) //Teste Vertical
            temp = 1;
        else if ((jv[0] == jv[4] && jv[4] == jv[8]) || (jv[2] == jv[4] && jv[4] == jv[6])) //Teste diagonal
            temp = 1;
        else if (jv[0] != '1' && jv[1] != '2' && jv[2] != '3' && jv[3] != '4' && jv[4] != '5' && jv[5] != '6' && jv[6] != '7' && jv[7] != '8' && jv[8] != '9') //Testando se o jogo deu velha
            temp = 0;
        else //Caso nenhuma das condições de vitória ocorra o jogo continua
            temp = -1;
    
    //Retornamos o valor para a função main, especificamente para a variável wc.
    return temp; 
}

//Mostrando qual o resultado do jogo
void Ganhador(int wc, int player){
    char marca;
    marca = (player == 1) ? 'X' : 'O'; //Testando qual é o jogador, X ou O
    if (wc == 1)
        printf("Fim do jogo! O jogador %c venceu!\n", marca);
    else
        printf("Deu velha!\n");
}

//Função principal do programa
int main(){

    int wc, player = 1, count = 0;

    //Ponteiro, Jogo da Velha, que guardará os números/marcações(X ou O) do jogador
    char *jv;

    //Alocando os valores na memória Heap
    jv = (char *) malloc (9 * sizeof(char));

    //Definindo para o vetor os valores de 1 a 9, que serão exibidos na tabela do jogo
    for (int i = 0; i < 9; i++){
        jv[i] = i + 49;
    }
 
    /*
    Loop que executará o jogo, wc é a variável que controla se o jogo acabou ou não, enquanto ela for -1 o programa continuará rodando. A função testeVitoria é chamada a cada rodada
    para analisar caso algum jogador tenha ganho, caso sim wc terá o valor 1, terminando assim o laço de repetição. Se ninguém vencer, após o final de todas as jogadas a função
    testeVitoria verá que todas as casas foram preenchidas mas não ouve vencedor, logo, o jogo deu velha, para que o programa não rode infinitamente, wc receberá o valor 0, que demonstrará
    que o jogo acabou, pois o valor é diferente de -1.
    */
    do { 
        player = (player % 2) ? 1 : 2;
        Tabela(jv);
        if (count == 0) printf("Jogo da velha!\n");
        Jogador(player);
        Jogo(player, jv);
        player++;
        wc = testeVitoria(jv);
        count = 1;
    } while (wc == -1);

    /*
        Ao final do laço de repetição do jogo (o do acima), temos que subtrair 1 da variável jogador pois ela está sempre sempre acrescida de 1 dentro do laço, então se o jogador 1
        fizer com ue o jogo acabe a variável player estará armazenando o valor 2, como se o jogador 2 fosse o vencedor. Ao subtrairmos 1 podemos saber quem foi o jogador que venceu.
        Para o caso do jogador 2 a variável player estaria guardando o valor 3, então subtraimos o 1 para que ela volte a ser 2. Isso mantém a veracidade do resultado final aparecendo
        quem foi realmente o jogador vencedor
    */
    player--;
    //Printando na tela o resultado final do jogo, caso houve ganhador ou caso tenha sido empate.
    Tabela(jv);
    Ganhador(wc, player);

    //Liberando a memória heap
    free (jv);

    return 0;
}