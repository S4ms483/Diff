#include "file.h"

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <sys/stat.h>

char* FileRead(const char* fileName)
{
    assert(fileName != NULL);
    char* buffer = CreateBuffer(fileName);

    return buffer;
}


char* CreateBuffer(const char* file)
{
    assert(file != NULL);

    FILE* fp = fopen(file, "r+");
    assert(fp != NULL);

    int descriptor = fileno(fp);
    assert(descriptor != -1);

    struct stat statistics;
    fstat(descriptor, &statistics);
    assert(statistics.st_size != -1);

    long int size = statistics.st_size;
    char* buffer = (char*)calloc((size_t)size + 1, sizeof(char));

    fread(buffer, sizeof(char), (size_t)size, fp);

    return buffer;
}