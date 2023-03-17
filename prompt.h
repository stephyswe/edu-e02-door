#include <stdio.h>
#include <stdlib.h>

// struct files
#include "FileData.h"

// Function usePrompt
// Description: default prompt
// Parameters: char* prompt & int max
// Returns: int number
int usePrompt(char *prompt, int max);

// Function: checkInput
// Description: Checks input
// Parameters: int input, Card card, int cardNumber, char *text
// Returns: bool isValid
bool validateModifyInput(int input, Card card, int cardNumber, char *text);