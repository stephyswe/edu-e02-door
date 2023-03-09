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

// Struct: FileCard
// Description: date, row and access
typedef struct
{
    char *date;
    int row;
    bool hasAccess;
} FileCard;

#endif /* FILEDATA_H */