#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include <string.h>
#include <unistd.h>

// define file
#include "Define.h"

// struct files
#include "FileData.h"

// header files
#include "file.h"
#include "common.h"

void createFileWithEmptyRow(char *filename)
{
    // check if file exists
    if (access(filename, F_OK) == -1)
    {
        // create file
        FILE *file_ptr = fopen(filename, "w");

        // check if file is created
        if (file_ptr == NULL)
        {
            printf("Error creating file");
            exit(1);
        }

        // close file
        fclose(file_ptr);
    }
}

FileData useFile(char *fileName, char *mode)
{
    // Read file
    FileData fdata;

    // check if file exists
    createFileWithEmptyRow(fileName);

    // Open file
    fdata.file_ptr = fopen(fileName, mode);

    // Return file data
    return fdata;
}

// Helper function to show file data
void viewFileData(char *fileName)
{
    FileData fdata = useFile(fileName, "r");
    // Loop through the file and print the data
    while (fgets(fdata.file_row, 60, fdata.file_ptr) != NULL)
    {
        printf("%s", fdata.file_row);
    }
    fclose(fdata.file_ptr);
};

bool isAccessInFile(char *row)
{
    return (strstr(row, "No") == NULL);
}

void generateTempFileName(char *tempFileName)
{
    // create a temporary file name based on current time
    time_t currentTime = time(NULL);
    snprintf(tempFileName, FILE_SIZE, "temp_%ld.txt", currentTime);
}

void copyAndModifyFile(int rowNumber, char *newRow, char *tempFileName)
{
    // open original file for reading, and temp file for writing
    FileData file = useFile(FILE_DOOR, "r");
    FileData temp = useFile(tempFileName, "w");

    int currentLine = 1;

    // loop through file, copying each line to temp file and modifying the specified row
    while (fgets(file.file_row, MAX_ROW_LENGTH, file.file_ptr) != NULL)
    {
        if (currentLine == rowNumber)
        {
            // write the new row to the temp file
            fputs(newRow, temp.file_ptr);

            // if we are not at the end of the file, add a newline character
            if (!feof(file.file_ptr))
                fputc('\n', temp.file_ptr);
        }
        else
        {
            // copy the current line to the temp file
            fputs(file.file_row, temp.file_ptr);
        }
        currentLine++;
    }

    // close file pointers
    fclose(file.file_ptr);
    fclose(temp.file_ptr);
}

void replaceOriginalFileWithTempFile(char *tempFileName)
{
    // delete original file, rename temp file to original file name
    remove(FILE_DOOR);
    rename(tempFileName, FILE_DOOR);
}

void updateDataToFile(int rowNumber, char *newRow)
{
    // create a temporary file name
    char tempFileName[FILE_SIZE];
    generateTempFileName(tempFileName);

    // copy file contents to temp file, modifying the specified row
    copyAndModifyFile(rowNumber, newRow, tempFileName);

    // replace original file with modified temp file
    replaceOriginalFileWithTempFile(tempFileName);
}

FileAppend readFile(char *file_path, int num_lines, int line_number, char *text)
{
    FILE *file = fopen(file_path, "r");
    char **lines = malloc(sizeof(char *) * 1000);

    int i = 0;
    char buffer[1000];

    // Loop through the file until we reach the line we want to insert
    while (fgets(buffer, sizeof(buffer), file))
    {
        size_t len = strlen(buffer);
        lines[i] = malloc(sizeof(char) * (len + 1));

        strcpy(lines[i], buffer);
        i++;
    }

    fclose(file);

    return (FileAppend){.lines = lines, .row_insert = i};
}

void writeFile(char *file_path, FileAppend fileAppend, int rowLine, char *text)
{
    FILE *file = fopen(file_path, "w");

    // Loop through the file until we reach the line we want to insert
    for (int j = 0; j < rowLine - 1 && j < fileAppend.row_insert; j++)
    {
        // Write the line to the file
        fputs(fileAppend.lines[j], file);
    }

    // Insert the new line
    fputs(text, file);

    // Loop through the rest of the file
    for (int j = rowLine - 1; j < fileAppend.row_insert; j++)
    {
        // Write the line to the file
        fputs(fileAppend.lines[j], file);
    }

    fclose(file);
}

// Helper function to free memory allocated for an array of strings
void freeLines(FileAppend fileAppend)
{
    for (int j = 0; j < fileAppend.row_insert; j++)
    {
        free(fileAppend.lines[j]);
    }
    free(fileAppend.lines);
}

void addDataToFile(char *file_path, int rowLine, char *text)
{
    // Read the file into struct FileAppend
    FileAppend fileAppend = readFile(file_path, FILE_SIZE, rowLine, text);

    // Write the file at the specified line
    writeFile(file_path, fileAppend, rowLine, text);

    // Free memory
    freeLines(fileAppend);
}
