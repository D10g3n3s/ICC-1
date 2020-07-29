/*
	ICMC USP - Diógenes Silva Pedro - BCC 020
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    int op; //Definindo qual a opção (1-Encriptar e 2-Desencriptar)
    int chave; //Definindo qual será a chave do programa
    char mensagem[500] = {0}; //Definindo a string que receberá a mensagem  
    char resposta[500] = {0}; //Definindo a string que mostrará a mensagem encriptada ou descriptada
    int tm; //Definindo uma variável que guardará o tamanho da mensagem
    char teste; //Variável que testará qual a letra
    
    //Recebendo a operação e a chave do usuário
    scanf("%d", &op);
    scanf("%d", &chave);
    
    //Recebendo a mensagem do usuário
    scanf(" %[^\n]s", mensagem);
    
    tm = strlen(mensagem);

    //Invertendo o valor da chave pois assim o programa descriptografará 
    if (op == 2){
        chave = chave * -1; 
    }
    
    //Encriptografando se a chave for positiva ou Desincriptografando se a chave for negativa graças ao if de cima
    for (int i = 0; i < tm; i++){
            
            //A variável teste recebe o caracter da mensagem para encriptografá-la
            teste = mensagem[i];
            
            //Teste para descobrir as letras maiúsculas
            if (teste >= 'A' && teste <= 'Z'){
                resposta[i] = teste + chave;
                //Vendo se o caracter ainda está dentro dos caracteres minúsculos com base no seu valor na tabela ascii
                if (resposta[i] < 'A'){ 
                    //Enquanto o caracter não estiver na tabela ascii dos minúsculos o laço não para de se repetir
                    while (resposta[i] < 'A'){ 
                        resposta[i] += 26; //Somando 26 pois ao estar com o valor < 97 e somar 26 estariamos voltando desde z para descobrir qual essa letra
                    }
                }
                if (resposta[i] > 'Z'){
                    while (resposta[i] > 'Z'){
                        resposta[i] -= 26; //Subtraindo 26 pois ao estar com o valor > 122 e subtrair 26 estariamos voltando desde a para descobrir qual essa letra
                    }
                }
            }
            
            //Teste para descobrir as letras minúsculas
            else if (teste >= 'a' && teste <= 'z'){
                resposta[i] = teste + chave;
                //Vendo se o caracter ainda está dentro dos caracteres minúsculos com base no seu valor na tabela ascii
                if (resposta[i] < 'a'){ 
                    //Enquanto o caracter não estiver na tabela ascii dos minúsculos o laço não para de se repetir
                    while (resposta[i] < 'a'){ 
                        resposta[i] += 26; //Somando 26 pois ao estar com o valor < 97 e somar 26 estariamos voltando desde z para descobrir qual essa letra
                    }
                }
                if (resposta[i] > 'z'){
                    while (resposta[i] > 'z'){
                        resposta[i] -= 26; //Subtraindo 26 pois ao estar com o valor > 122 e subtrair 26 estariamos voltando desde a para descobrir qual essa letra
                    }
                }
            }
            
            //Caso a variável não seja letra, ela será caracter especial e não será adicionada de chave
            else {
                resposta[i] = teste;
            }
        }

    printf("%s", resposta);

    return 0;
}