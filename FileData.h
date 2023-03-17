#include <stdio.h>
#include <stdbool.h>

#ifndef FILEDATA_H
#define FILEDATA_H

typedef struct
{
    int id;
    char *access;
    char *date;
} Data;

typedef struct
{
    Data *data;
    int size;
} ArrayData;

typedef struct
{
    int row;
    bool hasAccess;
    char *date;
    bool endOfFile;
} CardStatus;

#endif /* FILEDATA_H */