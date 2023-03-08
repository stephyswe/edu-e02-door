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

// Function: choiceNineFakeScanCard
// Description: Fake scan card
void choiceNineFakeScanCard()
{
    // variables
    char *strMessage = "CURRENTLY LAMP IS:%s \n";
    const char *LAMP_OFF = "Off";
    const char *LAMP_STATUS_MESSAGES[] = {"Red", "Green"};
    int cardNumber;

    printf(strMessage, LAMP_OFF);
    scanf("%d", &cardNumber);

    bool status = getFakeCardStatus(cardNumber);
    printf(strMessage, LAMP_STATUS_MESSAGES[status]);

    pauseKeyboard();
}

// Function: choiceThreeAddRemoveAccess
// Description: Add or remove access to card
void choiceThreeAddRemoveAccess()
{
    // strings
    char *strMessage = "Enter cardnumber>";

    // variables
    int cardNumber;

    printf(strMessage);
    scanf("%d", &cardNumber);

    // check if card entered has access or not
    viewStatusCards(cardNumber);

    // return to menu
}

// Function: choiceTwoListAllCards
// Description: List all cards in system
void choiceTwoListAllCards()
{
    // strings
    char *strMessage = "All cards in system\n";

    // print message
    printf(strMessage);

    // view all cards
    viewAllCards();

    // prompt user to press any key to continue
    pauseKeyboard();

    // return to menu
}

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
            choiceTwoListAllCards();
            break;
        case OPTION_ADD_REMOVE_ACCESS:
            choiceThreeAddRemoveAccess();
            break;
        case OPTION_EXIT:
            exit(EXIT_SUCCESS);
            break;
        case OPTION_FAKE_SCAN_CARD:
            choiceNineFakeScanCard();
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
