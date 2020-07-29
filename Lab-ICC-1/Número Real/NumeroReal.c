#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main (){

    float a;

    scanf("%f", &a);

    printf("%d\n", (int) a);
    printf("%.4f\n", a - (int) a);
    printf("%.0f\n", round (a));

    return 0;
}