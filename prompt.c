#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

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

int isBufferOverflow(char *buffer, size_t size, bool currentValid)
{
    // Check if the last character is a newline character
    if (buffer[strlen(buffer) - 1] != '\n')
    {
        // Buffer overflow occurred
        printf("Buffer overflow. Input truncated.\n");
        while (getchar() != '\n')
            ; // Clear input buffer
        return false;
    }
    return currentValid;
}

int usePrompt(const char *prompt, int max)
{
    int number;
    char inputBuffer[100];
    const int PROMPT_MIN = 1;

    while (true)
    {
        printf(prompt);
        validateInput(inputBuffer);

        int inputValue = atoi(inputBuffer);
        bool isValidInput = isInteger(inputBuffer) && isInRange(inputValue, PROMPT_MIN, max);

        // make a function that check if prompt is buffer overflow safe
        isValidInput = isBufferOverflow(inputBuffer, sizeof(inputBuffer), isValidInput);

        if (isValidInput)
            return inputValue;

        printf(isValidInput ? "" : "Felaktig %s, måste vara %d - %d, försök igen\n",
               isInteger(inputBuffer) ? "nummer" : "inmatning", PROMPT_MIN, max);
    }
}

bool usePromptWithExit(const char *prompt, int max, int *value)
{
    char inputBuffer[100];
    const int PROMPT_MIN = 1;
    bool isExit = false;

    while (true)
    {
        printf(prompt);
        validateInput(inputBuffer);

        // check if inputBuffer is "X"
        if (inputBuffer[0] == 'X' || inputBuffer[0] == 'x')
        {
            isExit = true;
            break;
        }

        int inputValue = atoi(inputBuffer);
        bool isValidInput = isInteger(inputBuffer) && isInRange(inputValue, PROMPT_MIN, max);

        // make a function that check if prompt is buffer overflow safe
        isValidInput = isBufferOverflow(inputBuffer, sizeof(inputBuffer), isValidInput);

        if (isValidInput)
            break;

        printf(isValidInput ? "" : "Felaktig %s, måste vara %d - %d, försök igen\n",
               isInteger(inputBuffer) ? "nummer" : "inmatning", PROMPT_MIN, max);
    }
    return isExit;
}