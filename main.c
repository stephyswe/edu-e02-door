#include <time.h>

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

// Function: choiceOneRemoteOpenDoor
// Description: Opens door for 3 seconds
void choiceOneRemoteOpenDoor()
{
    // strings
    char *strMessage = "CURRENTLY LAMP IS:Green\n";

    // prompt user for input
    printf(strMessage);

    // if timeout passes 3 seconds, print timeout message
    if (getTimeoutPerSecond(3) == 1)
    {
        // printf("Time Out\n");
        return;
    }

    // return to menu
}

// Function: menu
// Description: Menu function
void menu()
{
    // variables
    int userChoice;

    // strings
    char *strMenu = "Admin menu \n1. Remote open door \n2. List all cards in system \n3. Add/remove access \n4. Exit \n9. FAKE TEST SCAN CARD \n \nVälj: ";
    char *strError = "Fel inmatning. Försök igen.";

    do
    {
        // show the menu and get the user's choice
        userChoice = usePrompt(strMenu, MENU_MAX, 0);

        // execute the chosen option
        switch (userChoice)
        {
        case OPTION_REMOTE_OPEN_DOOR:
            choiceOneRemoteOpenDoor();
            break;
        case OPTION_LIST_ALL_CARDS:
            printf("Option 2, Not implemented yet");
            break;
        case OPTION_ADD_REMOVE_ACCESS:
            printf("Option 3, Not implemented yet");
            break;
        case OPTION_EXIT:
            exit(EXIT_SUCCESS);
            break;
        case OPTION_FAKE_SCAN_CARD:
            printf("Option 9, Not implemented yet");
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
    // menu with options
    menu();
}
