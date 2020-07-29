#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main (){
	
	float a, b, c;
	scanf("%f", &a);
	scanf ("%f", &b);

	c = pow (a,b);
	
	printf("%.4f\n", c);

	return 0;
}
