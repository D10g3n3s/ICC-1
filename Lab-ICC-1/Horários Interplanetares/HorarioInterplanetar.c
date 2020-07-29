/*
    ICMC USP - Diógenes Silva Pedro - BCC 020
    Programa que cálcula horários interplanetares
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
    Planetas e quantos dias duram cada dia nesse mesmo respectivo planeta
        Vamos arredondar o dia terrestre para 24h
        O dia em Vênus equivale a 243 dias terrestres.
        O dia em Mercúrio equivale a 58 dias e 16 horas terrestes.
        O dia em Júpiter equivale a 9 horas e 56 minutos terrestres
*/

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

//Função que calcula o horário interplanetar
void interplanetarTime (unsigned long long time, unsigned long long *r, char *planet){
    

    if (strcmp(planet, "Terra") == 0){
        //Pegando o resto dos segundos / 60, pois teremos assim apenas a parte em segundos realmente
        r[0] = time % 60; 
        //Pegando o tempo (em segs) / 60, para achar os minutos e pegando o resto dessa divisão para
        //termos apenas a parte em minutos realmente
        r[1] = (time / 60) % 60;
        //Pegando o tempo e transformando em horas e achando o resto dessa divisão para termos 
        //apenas a parte em horas realmente
        r[2] = ((time / 60) / 60) % 24; 
        //Pegando o tempo e transformando em horas e dividindo por 24, para saber quantos dias 
        //completos temos nesse tempo total
        r[3] = ((time / 60) / 60) / 24; 
    }

    else if (strcmp(planet, "Venus") == 0){
        //Pegando o resto dos segundos / 60, pois teremos assim apenas a parte em segundos realmente
        r[0] = time % 60; 
        //Pegando o tempo (em segs) / 60, para achar os minutos e pegando o resto dessa divisão para
        //termos apenas a parte em minutos realmente
        r[1] = (time / 60) % 60;
        //Pegando o tempo e transformando em horas e achando o resto dessa divisão para termos 
        //apenas a parte em horas realmente
        r[2] = ((time / 60) / 60) % 5832; 
        //Pegando o tempo e transformando em horas e dividindo por 5832, para saber quantos dias 
        //completos temos nesse tempo total
        r[3] = ((time / 60) / 60) / 5832;
    }

    //1 Hora terraquia equivale a 58h mercurianas
    else if (strcmp(planet, "Mercurio") == 0){
        //Pegando o resto dos segundos / 60, pois teremos assim apenas a parte em segundos realmente
        r[0] = time % 60; 
        //Pegando o tempo (em segs) / 60, para achar os minutos e pegando o resto dessa divisão para
        //termos apenas a parte em minutos realmente
        r[1] = (time / 60) % 60;
        //Pegando o tempo e transformando em horas e achando o resto dessa divisão para termos 
        //apenas a parte em horas realmente
        r[2] = ((time / 60) / 60) % 1408; 
        //Pegando o tempo e transformando em horas e dividindo por 1408, para saber quantos dias 
        //completos temos nesse tempo total
        r[3] = ((time / 60) / 60) / 1408;
    }

    else if (strcmp(planet, "Jupiter") == 0){
        int jupday = ((9 * 60) + 56) * 60;
        //Pegando o resto dos segundos / 60, pois teremos assim apenas a parte em segundos realmente
        r[0] = time % 60; 
        //Achando o tempo em minutos, achando quantos segundos faltam naquele dia, pegando módulo de
        //jupday, que resulta num tempo em segundos, transformando em minutos e achando o resto, 
        //assim achamos o tempo em minutos exato
        r[1] = ((time % jupday) / 60) % 60;
        //Achando o tempo em horas
        r[2] = ((time % jupday) / 3600) % 10; 
        //Pegando o tempo e transformando em horas e dividindo por jupday para saber quantos dias 
        //completos temos nesse tempo total
        r[3] = time / jupday;
    }

}

int main(){

    //Criando variáveis
    unsigned long long time, *r;
    char *planet;
    r = (unsigned long long*) calloc (4, sizeof(unsigned long long));
    
    scanf("%llu\n", &time);
    
    planet = readLine(stdin);

    printf("%llu segundos no planeta %s equivalem a:\n", time, planet);
    interplanetarTime(time, r, planet);
    //r[0] = sec, r[1] = min, r[2] = hours, r[3] = days
    printf("%llu dias, %llu horas, %llu minutos e %llu segundos\n", r[3], r[2], r[1], r[0]);

    free(r);
    free(planet);

    return 0;
}