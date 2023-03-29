#include <stdio.h>
#include <stdlib.h>

// struct files
#include "FileData.h"

// Function usePrompt
// Description: default prompt
// Parameters: char* prompt, int max
// Returns: int number
int usePrompt(char *prompt, int max);

// Function usePromptWithExit
// Description: prompt with exit option
// Parameters: char* prompt, int max, int* inputValue
// Returns: int number
int usePromptWithExit(const char *prompt, int max, int *inputValue);