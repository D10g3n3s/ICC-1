#include <stdio.h>
#include <stdlib.h>

int main (){

        long int a1, r, n, an, s;

        scanf("%ld", &a1);
        scanf("%ld", &r);
        scanf("%ld", &n);

        an = a1 + ((n-1)*r);

        s = ((a1 + an)*n)/2;

        printf("%ld\n", an);
        printf("%ld\n", s);

        return 0;
}

