// define file
#include "Define.h"

// header files
#include "prompt.h"
#include "common.h"
#include "util.h"
#include "file.h"
#include "input.h"

// struct files
#include "FileData.h"

// Function: choiceNineFakeScanCard
// Description: Fake scan card
void choiceNineFakeScanCard()
{
    // variables
    char *LAMP_MESSAGE = "CURRENTLY LAMP IS:";
    const char *LAMP_STATUS_MESSAGES[] = {"Red", "Green"};
    int cardNumber;

    // add two string together to a new char array
    char *LAMP_INIT = concatStrings(LAMP_MESSAGE, " Off\n");

    // get card number
    bool isNumber = GetInputInt(LAMP_INIT, &cardNumber);

    // if not number, return
    if (!isNumber)
    {
        return;
    }

    // get card status
    bool status = getFakeCardStatus(cardNumber);

    // print card status
    printf("%s %s", LAMP_MESSAGE, LAMP_STATUS_MESSAGES[status]);
}

// Function: choiceThreeAddRemoveAccess
// Description: Add or remove access to card
void choiceThreeAddRemoveAccess()
{
    int cardNumber;
    char text[MAX_ROW_LENGTH];

    // Prompt user for card number
    GetInputInt("Enter cardnumber>", &cardNumber);

    // Get card information
    Card card = getCardInfo(cardNumber);

    // Print card information
    printf("This card %s\n", card.isAccess ? "has access" : "has no access");

    // Prompt user for input
    int input = usePrompt("Enter 1 for access, 2 for no access\n", CHOICE_THREE_MAX);

    // Validate input and set modify flag
    bool isModify = validateModifyInput(input, card, cardNumber, text);

    // Modify if needed
    if (isModify)
    {
        updateDataToFile(card.row, text);
    }
}

// Function: choiceTwoListAllCards
// Description: List all cards in system
void choiceTwoListAllCards()
{
    printf("All cards in system\n");

    viewFileData(FILE_DOOR);

    pauseKeyboard();
}

// Function: choiceOneRemoteOpenDoor
// Description: Opens door for 3 seconds
void choiceOneRemoteOpenDoor()
{
    printf("CURRENTLY LAMP IS:Green\n");

    waitSeconds(3);
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
        userChoice = usePrompt(strMenu, MENU_MAX);

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
