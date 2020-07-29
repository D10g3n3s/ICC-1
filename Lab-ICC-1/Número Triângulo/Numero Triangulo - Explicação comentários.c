#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(){

    int numtri, n = 0, base = 0, n2 = 0, n3 = 0, x = 0, mult;

    scanf("%d", &numtri);

    for (n = 0; n < numtri;){
        // f(n) = f(n-1) + n;
        n = n + 1 + base;
        base++;
        // printf("%d\n", n);
    }

    // printf("%d -> n\n%d -> base\n%d -> numtri\n", n, base, numtri);

    if (n == numtri){
        printf("SIM\n   ");
    }
    else {
        printf("NAO\n");
    }

    n2 = n + 1 + base;
    // n2 = (numtri * (numtri + 1))/2;

    n3 = n2 + n;

    // x = sqrt (n3);
    // r10 = 3,16
    /* 0
        1
        2
        3
        4
     */
    for(int i = 0; i <= sqrt(n3); i++){

        mult = i * i;
        printf("%d\n", mult);
    }   
    
    printf("n2 -> %d\nn3 ->%d\n", n2, n3);
    
    if(mult == n3){
        printf("quadrado\n");
    }


    return 0;
}