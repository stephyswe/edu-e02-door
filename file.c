#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include <errno.h>
#include <unistd.h>

// define file
#include "Define.h"

// struct files
#include "FileData.h"
#include "Player.h"

// header files
#include "file.h"
#include "input.h"

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

// Helper function to extract the date from a row
void getDate(char *row, char *iDate)
{
    char *date_start = strstr(row, ": ") + 2;
    strncpy(iDate, date_start, 10);
    iDate[10] = '\0'; // add a null terminator at the end
}

// Helper function to check if a row indicates the card has no access
bool hasNoAccess(char *row)
{
    return (strstr(row, "No") != NULL);
}

// Helper function to prompt the user for input and return it
int getUserInput()
{
    int input;
    printf("Enter 1 for access, 2 for no access.\n");
    scanf("%d", &input);
    return input;
}

void viewStatusCards(int cardNumber)
{
    const int MAX_ROW_LENGTH = 60;
    FileData fdata = useFile(FILE_DOOR, "r");
    int row_line = 1;
    bool hasAccess = false;
    char new_row[MAX_ROW_LENGTH];
    char iDate[20];

    while (fgets(fdata.file_row, MAX_ROW_LENGTH, fdata.file_ptr) != NULL)
    {
        if (cardNumber == getCardNumber(fdata.file_row))
        {
            hasAccess = !hasNoAccess(fdata.file_row);
            break;
        }
        row_line++;
    }

    fclose(fdata.file_ptr);

    printf("This card %s.\n", hasAccess ? "has access" : "has no access");

    int input = getUserInput();

    getDate(fdata.file_row, iDate);

    if ((input == 1 && !hasAccess) || (input == 2 && hasAccess))
    {
        const char *action = input == 1 ? "Access added to system:" : "No access added to system:";
        snprintf(new_row, MAX_ROW_LENGTH, "%d %s %s", cardNumber, action, iDate);
        modifyRow(row_line, new_row);
    }
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