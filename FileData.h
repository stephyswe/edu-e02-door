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
// Description: date, row and access
typedef struct
{
    char **lines;
    int row_insert;
} FileAppend;

// Struct: FileCard
// Description: date, row and access
typedef struct
{
    char *date;
    int row;
    bool hasAccess;
} FileCard;

// Struct: FileStatusCard
// Description: date, row and access
typedef struct
{
    char *date;
    int row;
    bool hasAccess;
    bool cardExists;
    bool endOfFile;
} FileStatusCard;

#endif /* FILEDATA_H */