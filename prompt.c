#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

// define file
#include "Define.h"

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

// Function: checkInteger
// Description: Checks if input is integer
// Parameters: char *input
// Returns: bool
bool checkInteger(char *input)
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

// Function: isWithinRange
// Description: Checks if number is within range
// Parameters: int num
// Returns: bool
bool isWithinRange(int num, int min, int max)
{
    return (num >= min && num <= max);
}

int usePrompt(const char *prompt, int max, int tries)
{
    // variables
    int number;
    char inputBuffer[100];

    // error messages
    const char *strErrorDefaultMsg = "Felaktig inmatning, försök igen\n";
    const char *strErrorNumberMsg = "Felaktigt nummer, måste vara %d - %d, försök igen\n";

    while (true)
    {
        printf(prompt, tries);
        validateInput(inputBuffer);
        int inputValue = atoi(inputBuffer);
        const int withinRage = isWithinRange(inputValue, PROMPT_MIN, max);

        bool isValidInput = checkInteger(inputBuffer) && withinRage;

        if (isValidInput)
        {
            number = inputValue;
            break;
        }
        else if (!checkInteger(inputBuffer))
        {
            printf(strErrorDefaultMsg);
        }
        else if (withinRage)
        {
            printf(strErrorDefaultMsg);
        }
        else
        {
            printf(strErrorNumberMsg, PROMPT_MIN, max);
        }
    }
    return number;
}