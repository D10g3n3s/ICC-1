#ifndef _UTILS_H_
#define _UTILS_H_

char *readLine(FILE *);

int intCompare(const void*, const void*);

int fCompare(const void*, const void*);

int dCompare(const void*, const void*);

int strCompare(const void*, const void*);

int intBinarySearch(int*, int, int, int);

int floatBinarySearch(float*, int, int, float);

int doubleBinarySearch(double*, int, int, double);

int stringBinarySearch(char**, int, int, char*);

#endif