#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// struct files
#include "FileData.h"

// Function: getCardInfo
// Description: Get card information
// Parameters: int cardNumber
// Returns: Card card
Card getCardInfo(int cardNumber, ArrayData *data);

// Function: getFakeCardStatus
// Description: Get fake card status
// Parameters: ArrayData arrData, int cardNumber
// Returns: bool fakeCardStatus
bool getFakeCardStatus(ArrayData arrData, int cardNumber);

// Function: validateModifyInput
// Description: Validate modify input
// Parameters: int input, Card card, int cardNumber, char *text
// Returns: bool isValid
bool validateModifyInput(int input, Card card, int cardNumber, char *text);

// Function: initialDataWithLoop
// Description: Initial data with loop
// Parameters: ArrayData *arrData, int size
void initialDataWithLoop(ArrayData *arrData, int size);
