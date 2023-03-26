#include <time.h>

// header files
#include "prompt.h"
#include "common.h"
#include "util.h"
#include "array.h"
#include "input.h"

// struct files
#include "FileData.h"

// Function: choiceNineFakeScanCard
// Description: Fake scan card
void choiceNineFakeScanCard(ArrayData arrData)
{
    // variables
    char *LAMP_MESSAGE = "CURRENTLY LAMP IS:";
    const char *LAMP_STATUS_MESSAGES[] = {"Red", "Green"};
    int cardNumber;

    printf("Please scan card to enter or X to back to admin mode\n");

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
    bool status = getFakeCardStatus(arrData, cardNumber);

    // print card status
    printf("%s %s", LAMP_MESSAGE, LAMP_STATUS_MESSAGES[status]);
}

// Function: choiceThreeAddRemoveAccess
// Description: Add or remove access to card
void choiceThreeAddRemoveAccess(ArrayData *arrData)
{
    int cardNumber;
    char text[60];
    const int CHOICE_THREE_MAX = 2;

    // Prompt user for card number
    GetInputInt("Enter cardnumber>", &cardNumber);

    // Get card information
    Card card = getCardInfo(cardNumber, arrData);

    // Print card information
    printf("This card %s\n", card.isAccess ? "has access" : "has no access");

    // Prompt user for input
    int input = usePrompt("Enter 1 for access, 2 for no access\n", CHOICE_THREE_MAX);

    // Validate input and set modify flag
    bool isModify = validateModifyInput(input, card, cardNumber, text);

    // Modify if needed
    if (isModify)
    {
        updateDataToArray(arrData, cardNumber, text);
    }
}

// Function: choiceTwoListAllCards
// Description: List all cards in system
void choiceTwoListAllCards(ArrayData arrData)
{
    printf("All cards in system\n");

    viewArrayData(arrData);

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
    ArrayData arrData;
    int userChoice;
    const int MAX_MENU_CHOICE = 9;

    // initial data
    initialDataWithLoop(&arrData, 15);

    // strings
    char *strMenu = "Admin menu \n1. Remote open door \n2. List all cards in system \n3. Add/remove access \n4. Exit \n9. FAKE TEST SCAN CARD \n \nVälj: ";
    char *strError = "Fel inmatning. Försök igen.";

    do
    {
        // show the menu and get the user's choice
        userChoice = usePrompt(strMenu, MAX_MENU_CHOICE);

        // execute the chosen option
        switch (userChoice)
        {
        case 1:
            choiceOneRemoteOpenDoor();
            break;
        case 2:
            choiceTwoListAllCards(arrData);
            break;
        case 3:
            choiceThreeAddRemoveAccess(&arrData);
            break;
        case 4:
            exit(EXIT_SUCCESS);
            break;
        case 9:
            choiceNineFakeScanCard(arrData);
            break;
        default:
            fprintf(stderr, "%s\n", strError);
            break;
        }

        printf("\n");

    } while (userChoice != 4);
}

// Function: main
// Description: Main function
void main()
{
    // menu with options
    menu();
}
