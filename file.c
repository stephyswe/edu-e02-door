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

void scoreToFile(int insertion_line, int tries)
{
    // create a Player
    Player player = playerAdd(tries);

    // store the filename and temp filename
    char temp_filename[FILENAME_SIZE];

    // newline will store the new line of text to be written to the file
    char player_line[MAX_LINE];

    // cast integer player_value to string newline
    // ensures that the destination buffer is not overflowed
    snprintf(player_line, MAX_LINE, "%s %s %d", player.date, player.name, player.points);

    // create a temporary filename
    // snprintf will write the string "temp____" followed by the filename to
    // ensures that the destination buffer is not overflowed
    time_t t = time(NULL);
    snprintf(temp_filename, FILENAME_SIZE, "temp_%ld.txt", t);

    // open the original file for reading, and the temp file for writing
    FileData file = useFile(FILE_SCORE, "r");
    FileData temp = useFile(temp_filename, "w");

    // keep track of the current line number we are reading from the file
    int current_line = 1;

    // loop through each line in the file
    while (fgets(file.file_row, MAX_LINE, file.file_ptr) != NULL && current_line < MAX_LINES)
    {
        if (current_line == insertion_line)
        {
            fprintf(temp.file_ptr, "%s\n%s", player_line, file.file_row);
        }
        else
        {
            fputs(file.file_row, temp.file_ptr);
        }
        current_line++;
    }

    // only runs if file is empty
    if (current_line == insertion_line)
    {
        fprintf(temp.file_ptr, "%s\n", player_line);
    }

    // close our access to both files as we are done with them
    fclose(file.file_ptr);
    fclose(temp.file_ptr);

    // delete the original file, rename temp file to the original file's name
    remove(FILE_SCORE);
    rename(temp_filename, FILE_SCORE);
}
