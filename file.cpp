#include "file.h"

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <sys/stat.h>

char* FileRead(const char* fileName)
{
    assert(fileName != NULL);

    size_t buffersize = 0;
    char* buffer = CreateBuffer(&buffersize, fileName);

    return buffer;
}


char* CreateBuffer(size_t* buffersize, const char* file)
{
    assert(buffersize != NULL);
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

    *buffersize = fread(buffer, sizeof(char), (size_t)size, fp);

    return buffer;
}