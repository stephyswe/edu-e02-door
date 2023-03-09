// define file
#include "Define.h"

// header files
#include "prompt.h"
#include "common.h"
#include "file.h"

// struct files
#include "FileData.h"

// Function: choiceNineFakeScanCard
// Description: Fake scan card
void choiceNineFakeScanCard()
{
    const char *LAMP_OFF = "Off";
    const char *LAMP_MESSAGE = "CURRENTLY LAMP IS:%s \n";
    const char *LAMP_STATUS_MESSAGES[] = {"Red", "Green"};

    int cardNumber;
    printf(LAMP_MESSAGE, LAMP_OFF);
    scanf("%d", &cardNumber);

    bool status = getFakeCardStatus(cardNumber);
    printf(LAMP_MESSAGE, LAMP_STATUS_MESSAGES[status]);

    pauseKeyboard();
}

// Function: choiceThreeAddRemoveAccess
// Description: Add or remove access to card
void choiceThreeAddRemoveAccess()
{
    int cardNumber;
    char new_row[MAX_ROW_LENGTH];

    printf("Enter cardnumber>");
    scanf("%d", &cardNumber);

    FileCard card = viewStatusCards(cardNumber);

    printf("This card %s.\n", card.hasAccess ? "has access" : "has no access");

    int input = usePrompt("Enter 1 for access, 2 for no access.\n", CHOICE_THREE_MAX, 0);

    if ((input == 1 && !card.hasAccess) || (input == 2 && card.hasAccess))
    {
        const char *action = input == 1 ? "Access added to system:" : "No access added to system:";
        snprintf(new_row, MAX_ROW_LENGTH, "%d %s %s", cardNumber, action, card.date);
        modifyRow(card.row, new_row);
    }
}

// Function: choiceTwoListAllCards
// Description: List all cards in system
void choiceTwoListAllCards()
{
    printf("All cards in system\n");

    viewAllCards();

    pauseKeyboard();
}

// Function: choiceOneRemoteOpenDoor
// Description: Opens door for 3 seconds
void choiceOneRemoteOpenDoor()
{
    printf("CURRENTLY LAMP IS:Green\n");

    getTimeoutPerSecond(3);
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
