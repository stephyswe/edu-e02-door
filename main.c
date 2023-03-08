// define file
#include "Define.h"

// header files
#include "prompt.h"
#include "common.h"
#include "file.h"
#include "input.h"

// struct files
#include "FileData.h"
#include "Player.h"
#include "Score.h"

// Function: viewLowScoreboard
// Description: View low scoreboard
void viewLowScoreboard()
{
    // Read file
    FileData fdata = useFile(FILE_SCORE, "r");

    // Loop through file
    while (fgets(fdata.file_row, 60, fdata.file_ptr) != NULL)
    {
        // Print file row
        printf("%s", fdata.file_row);
    }

    // Close file
    fclose(fdata.file_ptr);
};

// Function: playGame
// Description: Plays a game of 'Guess the number'
int playGame()
{
    // variables
    int randomNumber = getRandomNumber();
    randomNumber = 50;
    int userGuess = 0;
    int numTries = 0;
    bool isWin = false;

    // strings
    char *strIntro = "Gissa ett tal mellan 1 och 100. \n";
    char *strHigher = "Talet är högre. \n";
    char *strLower = "Talet är lägre. \n";
    char *strCorrect = "Rätt! Du gissade rätt på %d försök.\n";
    char *strWrong = "Fel inmatning. Gissa ett tal mellan 1 och 100. Försök igen: ";
    char *strGuess = "Gissning %d: ";

    // intro
    printf("%s", strIntro);

    // while loop to check if guess is correct
    while (!isWin)
    {
        // increment tries
        numTries++;

        // checks if guess is between 1 and 100 and if it is an integer
        userGuess = usePrompt(strGuess, GAME_MAX, numTries);

        // if guess is higher than number
        if (userGuess > randomNumber)
            printf(strLower);
        // if guess is lower than number
        else if (userGuess < randomNumber)
            printf(strHigher);
        // guess is correct
        else
        {
            // print correct message
            printf(strCorrect, numTries);

            // set win to true
            isWin = true;
        }
    }

    // return tries
    return numTries;
}

// Function: playGameScore
// Description: Plays a game of 'Guess the number' and checks if score is highscore
void playGameScore()
{
    int tries = playGame();
    Score score = scoreCheck(tries);

    if (score.isHighScore)
        scoreToFile(score.row, tries);
}

// Function: menu
// Description: Menu function
void menu()
{
    // variables
    int userChoice;

    // strings
    char *strMenu = "\n1. Spela igen \n2. Avsluta \n3. Se lowscore \nVälj: ";
    char *strError = "Fel inmatning. Försök igen.";

    do
    {
        // show the menu and get the user's choice
        userChoice = usePrompt(strMenu, MENU_MAX, 0);

        // execute the chosen option
        switch (userChoice)
        {
        case OPTION_PLAY_AGAIN:
            playGameScore();
            break;
        case OPTION_EXIT:
            exit(EXIT_SUCCESS);
            break;
        case OPTION_VIEW_SCOREBOARD:
            viewLowScoreboard();
            break;
        default:
            fprintf(stderr, "%s\n", strError);
            break;
        }

        printf("\n");

    } while (userChoice != OPTION_EXIT);
}

// Function: main
// Description: Main function
void main()
{
    // play game
    playGameScore();

    // menu with options
    menu();
}
