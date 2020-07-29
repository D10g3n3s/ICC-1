#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(){

    double a, b, soma, subt, mult, div, porct;
    char op;

    scanf("%lf %c %lf", &a, &op, &b);

    switch (op) {
        case '+' :
            soma = a + b;
            printf ("%lf\n", soma);
        break;    

        case '-' :
            subt = a - b;
            printf ("%lf\n", subt);
        break;
    
        case '*' :
            mult = a * b;
            printf ("%lf\n", mult);
        break;
    
        case '/' :
            div = a / b;
            printf ("%lf\n", div);
        break;

        case '%' :
            porct = (a/b) * 100;
            printf ("%lf\n", porct);
        break;
  }

    return 0;

}