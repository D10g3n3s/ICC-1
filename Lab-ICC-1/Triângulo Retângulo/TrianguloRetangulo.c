#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(){
    double a, b, c, teste;

        scanf("%lf %lf %lf", &a, &b, &c);
        if (a == 0 || b == 0 || c == 0){    
            printf("NAO\n");
        }
        else { 
            if (a > b && a > c){
                teste = sqrt (pow (b,2) + pow (c,2));
                if (a == teste){
                printf("SIM\n");
                }
                else {
                    printf("NAO\n");
                }
            }

            else if (b > a && b > c){
                teste = sqrt (pow (a,2) + pow (c,2));
                if (b == teste){
                    printf("SIM\n");
                }
                else {
                    printf("NAO\n");
                }
            }
            else if (c > a && c > b) {
                teste = sqrt (pow (a,2) + pow (b,2));
                if (c == teste){
                    printf("SIM\n");
                }
                else {
                    printf("NAO\n");
                }
            }
            else if (c == a && c == b){
                teste = sqrt (pow (a,2) + pow (b,2));
                if (c == teste){
                    printf("SIM\n");
                }
                else {
                    printf("NAO\n");
                }
            }
        }
            return 0;
}