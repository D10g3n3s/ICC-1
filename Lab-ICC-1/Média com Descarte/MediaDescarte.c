#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(){
	
	double a, b, c, d, media;
		
	scanf("%lf %lf %lf %lf", &a, &b, &c, &d);

	if (a <= b && a <= c && a <= d){
		media = (b + c + d)/3;
		printf ("%.4lf\n", media);
	}
	else if (b <= a && b <= c && b <= d){
		media = (a + c + d)/3;
		printf("%.4lf\n", media);
	}
	else if (c <= a && c <= b && c <= d){
		media = (a + b + d)/3;
		printf("%.4lf\n", media);
	}
	else {
		media = (a + b + c)/3;
		printf("%.4lf\n", media);
	}

	return 0;
}
