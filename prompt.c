#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

// define file
#include "Define.h"

// struct files
#include "FileData.h"

// Function: validateInput
// Description: Validates input
// Parameters: char *inputBuffer
void validateInput(char *inputBuffer)
{
    if (fgets(inputBuffer, sizeof(inputBuffer), stdin) == NULL)
    {
        printf("Error reading input\n");
        exit(1);
    }
}

// Function: isInteger
// Description: Checks if input is integer
// Parameters: char *input
// Returns: bool
bool isInteger(char *input)
{
    // variables
    int length = strlen(input);
    int i;
    bool is_integer = true;

    // loop through input
    for (i = 0; i < length; i++)
    {

        // check if input is integer
        if (!isdigit(input[i]))
        {

            // check if input is newline or null
            if (input[i] == '\n' || input[i] == '\0')
            {
                break;
            }

            // input is not integer
            is_integer = false;
            break;
        }
    }
    return is_integer;
}

// Function: isInRange
// Description: Checks if number is in range
// Parameters: int num
// Returns: bool
bool isInRange(int num, int min, int max)
{
    return (num >= min && num <= max);
}

int usePrompt(const char *prompt, int max)
{
    int number;
    char inputBuffer[100];

    while (true)
    {
        printf(prompt);
        validateInput(inputBuffer);

        int inputValue = atoi(inputBuffer);
        bool isValidInput = isInteger(inputBuffer) && isInRange(inputValue, PROMPT_MIN, max);

        if (isValidInput)
            return inputValue;

        printf(isValidInput ? "" : "Felaktig %s, måste vara %d - %d, försök igen\n",
               isInteger(inputBuffer) ? "nummer" : "inmatning", PROMPT_MIN, max);
    }
}

bool validateModifyInput(int input, CardStatus card, int cardNumber, char *text)
{
    // variables
    bool modify = false;

    // check if input is 1 or 2
    if ((input == 1 && !card.hasAccess) || (input == 2 && card.hasAccess))
    {
        // decide action
        const char *action = input == 1 ? TEXT_ACCESS : TEXT_NO_ACCESS;

        // text
        snprintf(text, MAX_ROW_LENGTH, "%d %s %s %s", cardNumber, action, TEXT_ADDED, card.date);

        // modify row in file
        modify = true;
    }
    return modify;
}