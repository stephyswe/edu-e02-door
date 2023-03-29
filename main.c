#include <unistd.h>

// header files
#include "prompt.h"
#include "common.h"
#include "util.h"
#include "file.h"
#include "input.h"

// struct files
#include "FileData.h"

// Function: main
// Description: Main function
void main()
{
    // variables
    int userChoice;
    const int MAX_MENU_CHOICE = 9;

    // strings
    char *strMenu = "Admin menu \n1. Remote open door \n2. List all cards in system \n3. Add/remove access \n4. Exit \n9. FAKE TEST SCAN CARD \n \nVälj: ";
    char *strError = "Fel inmatning. Försök igen.";

    do
    {
        // show the menu and get the user's choice
        userChoice = usePrompt(strMenu, MAX_MENU_CHOICE);

        if (userChoice == 1)
        {
            printf("CURRENTLY LAMP IS:Green\n");
            sleep(3);
        }
        else if (userChoice == 2)
        {
            printf("All cards in system\n");
            viewFileData();
            pauseKeyboard();
        }
        else if (userChoice == 3)
        {
            int cardNumber;
            char text[254];
            const int CHOICE_THREE_MAX = 2;

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
        else if (userChoice == 4)
        {
            exit(EXIT_SUCCESS);
        }
        else if (userChoice == 9)
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
        else
        {
            fprintf(stderr, "%s\n", strError);
        }

        printf("\n");

    } while (userChoice != 4);
}
