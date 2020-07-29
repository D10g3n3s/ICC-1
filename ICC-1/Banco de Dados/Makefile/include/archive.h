#ifndef _ARCHIVE_H_
#define _ARCHIVE_H_

char** readDat(DATABASE*, char**, int*, int*);

void regName(DATABASE*, char*);

DATABASE* createRegFields(DATABASE*, char**, int);

void createIdxArchive(DATABASE*, int, FILE*);

DATABASE* patternOffset(DATABASE*, int);

void printResult(DATABASE*, int, int);

void intSearchArchive(DATABASE*, int, int);

void floatSearchArchive(DATABASE*, float, int);

void doubleSearchArchive(DATABASE*, double, int);

void stringSearchArchive(DATABASE*, char*, int);

DATABASE* operations(DATABASE*, int, FILE*, FILE*);

void freeData(DATABASE*, char**, int, int);

#endif