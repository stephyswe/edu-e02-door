#include <stdio.h>
#include <stdbool.h>
#include <string.h>

// define file
#include "Define.h"

// struct files
#include "Score.h"
#include "FileData.h"

// header files
#include "file.h"
#include "common.h"

Player playerAdd(int tries)
{
    // Prompt the user for their name
    printf("Ange ditt namn: ");
    fflush(stdout);

    // Get the player's name from user input
    char name[MAX_NAME];
    fgets(name, sizeof(name), stdin);

    // Remove newline character from input
    name[strcspn(name, "\n")] = '\0';

    // Create player struct and set its fields
    Player player;
    strcpy(player.name, name);
    strcpy(player.date, getCurrentDate());
    player.points = tries;

    // Return the player
    return player;
}

Score scoreCheck(int tries)
{
    // Create score struct
    Score score;

    // Read file
    FileData fdata = useFile(FILE_SCORE, "r");

    // Set score
    score.isHighScore = false; // start as highscore false

    // Set rowline
    int row_line = 1;

    // variables
    int number;

    // loop through file
    while (fgets(fdata.file_row, sizeof(fdata.file_row), fdata.file_ptr) != NULL)
    {
        // try to get score from string
        if (sscanf(fdata.file_row, "%*s %*s %*s %d", &number) != 1)
        {
            // line doesn't match expected format, skip it
            continue;
        }

        // if number is higher than tries, highscore found
        if (number > tries)
        {
            // High score found! create a new score.
            score = (Score){.isHighScore = true, .row = row_line};
            break;
        }

        // add to rowline
        row_line++;
    }

    // count lines in file. If less than MAX_SCORES, add to last row
    if (row_line < MAX_SCORES && !score.isHighScore)
    {
        // create a new score
        score = (Score){.isHighScore = true, .row = row_line};
    }

    // close file
    fclose(fdata.file_ptr);

    // return score
    return score;
}