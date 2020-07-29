#include <stdio.h>
#include <stdlib.h>

int main(){

    int a, b, and, or, exor, compla, complb, right, left;

    scanf("%d %d", &a, &b);

    and = a & b;

    or = a | b;

    exor = a ^ b;

    compla = ~a;

    complb = ~b;
    
    right = a >> 2;

    left = b << 2;

    printf("%d\n", and);
    printf("%d\n", or);
    printf("%d\n", exor);
    printf("%d\n", compla);
    printf("%d\n", complb);
    printf("%d\n", right);
    printf("%d\n", left);

    return 0;
}