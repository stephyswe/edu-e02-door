#include <stdio.h>
#include <stdbool.h>

#ifndef FILEDATA_H
#define FILEDATA_H

// Struct: FileData
// Description: file pointer and file row
typedef struct
{
    FILE *file_ptr;
    char file_row[256];
} FileData;

// Struct: FileAppend
// Description: lines & row_insert
typedef struct
{
    char **lines;
    int row_insert;
} FileAppend;

typedef struct {
    int row;
    bool isAccess;
    char *date;
    bool endOfFile;
} Card;


#endif /* FILEDATA_H */