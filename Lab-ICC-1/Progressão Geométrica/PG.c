#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(){

	float a1, q, n, an, s, temp1, temp2, temp3;

	scanf("%f", &a1);
	scanf("%f", &q);
	scanf("%f", &n);
		
	temp1 = n-1;
		
	temp2 = pow (q,temp1);
		
	temp3 = pow (q,n);

	an = a1*temp2;

	s = (a1*(1-temp3))/(1-q);

	printf("%.2f\n", an);
	printf("%.2f\n", s);

	return 0;
}
