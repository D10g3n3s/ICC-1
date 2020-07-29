#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(){
    int numpontos;

    scanf("%d", &numpontos);

    double x[numpontos], y[numpontos];

    for (int i = 0; i < numpontos; i++){
        
        scanf("%lf", &x[i]);
        scanf("%lf", &y[i]);

    }

    double distancia = 0;

    for (int i1 = 0; i1 < numpontos - 1; i1++){

        distancia += sqrt (pow((x[i1] - x[i1+1]), 2) + pow(y[i1] - y[i1+1],2));

    }

    printf("%0.4lf\n", distancia);

    return 0;
}