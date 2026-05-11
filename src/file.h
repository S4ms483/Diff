#ifndef FILE_H_
#define FILE_H_

#include <stdio.h>

char* FileRead(const char* fileName);
char* CreateBuffer(const char* file);

const char* const calcFile = "calc.txt";

#endif //FILE_H_