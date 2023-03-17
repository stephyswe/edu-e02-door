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