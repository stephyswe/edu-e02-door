#include <stdio.h>

#ifndef FILEDATA_H
#define FILEDATA_H

// Struct: FileData
// Description: file pointer and file row
typedef struct
{
    FILE *file_ptr;
    char file_row[256];
} FileData;

#endif