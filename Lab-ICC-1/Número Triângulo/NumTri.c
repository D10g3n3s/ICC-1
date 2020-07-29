#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(){

    int numtri, n = 0, base = 0, n2 = 0, n3 = 0, mult;

    scanf("%d", &numtri);

    for (n = 0; n < numtri;){
        n = n + 1 + base;
        base++;
    }

    if (n == numtri){
        printf("SIM\n");
    }
    else {
        printf("NAO\n");
        return 0;
    }

    n2 = n + 1 + base;

    printf("%d\n", n2);

    n3 = n2 + n;

    for(int i = 0; i <= sqrt(n3); i++){
        mult = i * i;
    }   
    
    if(mult == n3){
        printf("SIM\n");
    }
    else {
        printf("NAO\n");
    }

    return 0;
}