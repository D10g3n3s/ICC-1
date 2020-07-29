#ifndef _DEFINE_H_
#define _DEFINE_H_

#define TRUE 1;
#define FALSE 0;

typedef union {
    int i;
    float f;
    double d;
    char *str;
} TYPE;

typedef enum {INT = 1, FLOAT, DOUBLE, CHAR} DATA_TYPE;

typedef struct {
    TYPE type;
    DATA_TYPE data_type;
    int size;
} KEY;

typedef struct {
    TYPE type;
    DATA_TYPE data_type;
    int size;
} FIELDS;

typedef struct {
    FIELDS *fields;
    KEY key;
} REGISTER;

typedef struct {
    REGISTER reg_field;
    REGISTER *regs;
    int howmanyregs;
    char *datname;
    char *regname;
    char *regidx;
    int *offset;
    int patternoffset;
} DATABASE;

#endif