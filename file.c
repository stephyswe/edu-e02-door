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

// Function: viewAllCards
// Description: View all cards
void viewAllCards()
{
    // Read file
    FileData fdata = useFile(FILE_DOOR, "r");

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

FileData useFile(char *filename, char *mode)
{
    // Read file
    FileData fdata;

    // check if file exists
    createFileWithEmptyRow(filename);

    // Open file
    fdata.file_ptr = fopen(filename, mode);

    // Return file data
    return fdata;
}

void modifyRow(int row_number, char *new_row)
{
    // store the filename and temp filename
    char temp_filename[FILENAME_SIZE];

    // create a temporary filename
    // snprintf will write the string "temp____" followed by the filename to
    // ensures that the destination buffer is not overflowed
    time_t t = time(NULL);
    snprintf(temp_filename, FILENAME_SIZE, "temp_%ld.txt", t);

    // open the original file for reading, and the temp file for writing
    FileData file = useFile(FILE_DOOR, "r");
    FileData temp = useFile(temp_filename, "w");

    char line[100];
    int current_line = 1;

    // loop through the original file, copying each line to the temp file
    while (fgets(file.file_row, sizeof(line), file.file_ptr) != NULL)
    {
        // if we are at the line we want to modify, write the new row to the temp file
        if (current_line == row_number)
        {
            // write the new row to the temp file
            fputs(new_row, temp.file_ptr);

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

// Helper function to append a line to a file at a given line number
void appendLine(char *file_path, int line_number, char *text)
{
    FILE *file = fopen(file_path, "r");
    char **lines = malloc(sizeof(char *) * 1000);
    if (!lines)
    {
        printf("Error: Unable to allocate memory.\n");
        fclose(file);
        return;
    }

    int i = 0;
    char buffer[1000];
    while (fgets(buffer, sizeof(buffer), file))
    {
        size_t len = strlen(buffer);
        lines[i] = malloc(sizeof(char) * (len + 1));
        if (!lines[i])
        {
            printf("Error: Unable to allocate memory.\n");
            fclose(file);
            return;
        }
        strcpy(lines[i], buffer);
        i++;
    }

    fclose(file);

    file = fopen(file_path, "w");
    for (int j = 0; j < line_number - 1 && j < i; j++)
    {
        fputs(lines[j], file);
    }

    fputs(text, file);

    for (int j = line_number - 1; j < i; j++)
    {
        fputs(lines[j], file);
    }

    fclose(file);

    for (int j = 0; j < i; j++)
    {
        free(lines[j]);
    }
    free(lines);
}

FileCard viewStatusCards(int cardNumber)
{
    // Open file for reading
    FileData fdata = useFile(FILE_DOOR, "r");

    // Initialize variables
    int rowLine = 1;
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
        rowLine++;
    }

    // Check if end of file is reached
    endOfFile = feof(fdata.file_ptr);

    fclose(fdata.file_ptr);

    // Append the new card to the file if it doesn't exist
    if (!cardExists)
    {
        const char *newRowFormat = endOfFile ? "\n%d %s %s" : "%d %s %s\n";
        date = getCurrentDate("%Y-%m-%d");
        snprintf(newRow, MAX_ROW_LENGTH, newRowFormat, cardNumber, "No access Added to system:", date);
        appendLine(FILE_DOOR, rowLine, newRow);
    }

    // Return card information
    return (FileCard){.date = date, .row = rowLine, .hasAccess = hasAccess};
}

bool getFakeCardStatus(int cardNumber)
{
    FileData fdata = useFile(FILE_DOOR, "r");

    int number;
    bool cardAccess = false;

    while (fgets(fdata.file_row, 60, fdata.file_ptr) != NULL)
    {
        if (sscanf(fdata.file_row, "%d", &number) == 1 && cardNumber == number)
        {
            if (strstr(fdata.file_row, "No") == NULL)
                cardAccess = true;
            break;
        }
    }

    fclose(fdata.file_ptr);
    return cardAccess;
};