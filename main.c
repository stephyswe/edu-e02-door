// define file
#include "Define.h"

// header files
#include "prompt.h"
#include "common.h"
#include "file.h"
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

    // add two string together to a new char array
    char *LAMP_INIT = concatStrings(LAMP_MESSAGE, " Off\n");

    // get card number
    GetInputInt(LAMP_INIT, &cardNumber);

    // get card status
    bool status = getFakeCardStatus(arrData, cardNumber);

    // print card status
    printf("%s %s", LAMP_MESSAGE, LAMP_STATUS_MESSAGES[status]);
}

// Function: choiceThreeAddRemoveAccess
// Description: Add or remove access to card
void choiceThreeAddRemoveAccess(ArrayData *arrData)
{
    // variables
    int cardNumber;
    char text[MAX_ROW_LENGTH];

    // get card number
    GetInputInt("Enter cardnumber>", &cardNumber);

    // Get card information from file and append if it doesn't exist
    CardStatus card = getCardStatus(cardNumber, arrData);

    // print card information
    printf("This card %s.\n", card.hasAccess ? "has access" : "has no access");

    // get input
    int input = usePrompt("Enter 1 for access, 2 for no access.\n", CHOICE_THREE_MAX);

    // check input, return true if modify is valid
    bool isModify = validateModifyInput(input, card, cardNumber, text);

    // modify file if needed
    if (isModify)
        updateDataToArray(arrData, cardNumber, text);
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

// Function: initialData
// Description: Initial data
void initialData(ArrayData *arrData)
{
    addDataToArray(arrData, (Data){1000, concatStrings(TEXT_ACCESS, TEXT_ADDED), "2023-03-11"}, 0);
    addDataToArray(arrData, (Data){1212, concatStrings(TEXT_NO_ACCESS, TEXT_ADDED), "2019-10-19"}, 1);
    addDataToArray(arrData, (Data){1213, concatStrings(TEXT_NO_ACCESS, TEXT_ADDED), "2019-10-20"}, 2);
    addDataToArray(arrData, (Data){1215, concatStrings(TEXT_NO_ACCESS, TEXT_ADDED), "2020-10-20"}, 3);
    addDataToArray(arrData, (Data){1216, concatStrings(TEXT_NO_ACCESS, TEXT_ADDED), "2021-10-24"}, 4);
}

// Function: menu
// Description: Menu function
void menu()
{
    // variables
    ArrayData arrData;
    arrData.size = 0;
    arrData.data = NULL;
    int userChoice;

    // initial data
    initialData(&arrData);

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
            choiceTwoListAllCards(arrData);
            break;
        case OPTION_ADD_REMOVE_ACCESS:
            choiceThreeAddRemoveAccess(&arrData);
            break;
        case OPTION_EXIT:
            exit(EXIT_SUCCESS);
            break;
        case OPTION_FAKE_SCAN_CARD:
            choiceNineFakeScanCard(arrData);
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
