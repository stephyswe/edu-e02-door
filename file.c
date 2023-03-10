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

void viewFileData(char *fileName)
{
    // Read file
    FileData fdata = useFile(fileName, "r");

    // Loop through file
    while (fgets(fdata.file_row, 60, fdata.file_ptr) != NULL)
    {
        // Print file row
        printf("%s", fdata.file_row);
    }

    // Close file
    fclose(fdata.file_ptr);
};

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

void modifyRow(int rowNumber, char *newRow)
{
    // store the filename and temp filename
    char temp_filename[FILE_SIZE];

    // create a temporary filename
    // snprintf will write the string "temp____" followed by the filename to
    // ensures that the destination buffer is not overflowed
    time_t t = time(NULL);
    snprintf(temp_filename, FILE_SIZE, "temp_%ld.txt", t);

    // open the original file for reading, and the temp file for writing
    FileData file = useFile(FILE_DOOR, "r");
    FileData temp = useFile(temp_filename, "w");

    char line[100];
    int current_line = 1;

    // loop through the original file, copying each line to the temp file
    while (fgets(file.file_row, sizeof(line), file.file_ptr) != NULL)
    {
        // if we are at the line we want to modify, write the new row to the temp file
        if (current_line == rowNumber)
        {
            // write the new row to the temp file
            fputs(newRow, temp.file_ptr);

            // if we are not at the end of the file, add a newline character
            if (!feof(file.file_ptr))
                fputc('\n', temp.file_ptr);
        }

        // otherwise, just copy the current line to the temp file
        else
            fputs(file.file_row, temp.file_ptr);

        current_line++;
    }

    // close our access to both files as we are done with them
    fclose(file.file_ptr);
    fclose(temp.file_ptr);

    // delete the original file, rename temp file to the original file's name
    remove(FILE_DOOR);
    rename(temp_filename, FILE_DOOR);
}

// Helper function to extract the card number from a row
int getCardNumber(char *row)
{
    int number;
    sscanf(row, "%d %*s %*s", &number);
    return number;
}

// Helper function to check if a row indicates the card has no access
bool hasNoAccess(char *row)
{
    return (strstr(row, "No") != NULL);
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

// Function: appendLine
// Description: Append a line to a file
// Parameters: file_path - the path to the file
//             rowLine - the line number to append the line to
//             text - the text to append to the file
void appendLine(char *file_path, int rowLine, char *text)
{
    // Read the file into struct FileAppend
    FileAppend fileAppend = readFile(file_path, FILE_SIZE, rowLine, text);

    // Write the file at the specified line
    writeFile(file_path, fileAppend, rowLine, text);

    // Free memory
    freeLines(fileAppend);
}

FileStatusCard getStatusCard(int cardNumber)
{
    // Open file for reading
    FileData fdata = useFile(FILE_DOOR, "r");

    // Initialize variables
    int row = 1;
    bool endOfFile = false;
    bool hasAccess = false;
    bool cardExists = false;
    char *date = malloc(sizeof(char) * 20);
    char newRow[MAX_ROW_LENGTH];

    // Iterate through the file to find the row corresponding to the card number
    while (fgets(fdata.file_row, MAX_ROW_LENGTH, fdata.file_ptr) != NULL && cardNumber >= getCardNumber(fdata.file_row))
    {
        if (cardNumber == getCardNumber(fdata.file_row))
        {
            cardExists = true;
            hasAccess = !hasNoAccess(fdata.file_row);
            date = getCardDate(fdata.file_row);
            break;
        }
        row++;
    }

    // Check if end of file is reached
    endOfFile = feof(fdata.file_ptr);

    fclose(fdata.file_ptr);

    return (FileStatusCard){
        .date = date,
        .row = row,
        .hasAccess = hasAccess,
        .cardExists = cardExists,
        .endOfFile = endOfFile,
    };
}

FileCard AppendCardIfNotExist(FileStatusCard fileStatusCard, int cardNumber)
{
    // variable
    char text[MAX_ROW_LENGTH];
    char *defaultText = "No access Added to system:";

    // Append the new card to the file if it doesn't exist
    if (!fileStatusCard.cardExists)
    {
        // text format based on row position
        const char *textFormat = fileStatusCard.endOfFile ? "\n%d %s %s" : "%d %s %s\n";

        // current date
        fileStatusCard.date = getCurrentDate("%Y-%m-%d");

        // text
        snprintf(text, MAX_ROW_LENGTH, textFormat, cardNumber, defaultText, fileStatusCard.date);

        // append to file at selected row
        appendLine(FILE_DOOR, fileStatusCard.row, text);
    }

    // return card information
    return (FileCard){.date = fileStatusCard.date, .row = fileStatusCard.row, .hasAccess = fileStatusCard.hasAccess};
}

bool getFakeCardStatus(int cardNumber)
{
    FileData fdata = useFile(FILE_DOOR, "r");

    int number;
    bool cardAccess = false;

    // Iterate through the file to find the row corresponding to the card number
    while (fgets(fdata.file_row, 60, fdata.file_ptr) != NULL)
    {
        //
        if (sscanf(fdata.file_row, "%d", &number) == 1 && cardNumber == number)
        {
            // Check if the card has access
            if (strstr(fdata.file_row, "No") == NULL)

                // Set card access to true
                cardAccess = true;
            break;
        }
    }

    fclose(fdata.file_ptr);
    return cardAccess;
};