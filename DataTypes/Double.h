#ifndef DOUBLE_H 
#define DOUBLE_H  

#include "stdio.h"

#include "StringAlgorithm.h"
#include "Base.h"

#define TYPE_NAME_DOUBLE "Double"

typedef struct Double {
    Base base;
    double data;
} Double;

void freeDouble(Double* real);

Double* createDouble(double data);

#endif