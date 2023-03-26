#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// struct files
#include "FileData.h"

// Function: getCardInfo
// Description: Get card information
// Parameters: int cardNumber
// Returns: Card card
Card getCardInfo(int cardNumber);

// Function: getFakeCardStatus
// Description: Get fake card status
// Parameters: int cardNumber
// Returns: bool fakeCardStatus
bool getFakeCardStatus(int cardNumber);

// Function: validateModifyInput
// Description: Validate modify input
// Parameters: int input, Card card, int cardNumber, char *text
// Returns: bool isValid
bool validateModifyInput(int input, Card card, int cardNumber, char *text);