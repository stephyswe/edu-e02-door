#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// struct files
#include "FileData.h"

#ifndef FILE_H
#define FILE_H

// Function: viewArrayData
// Description: View all array data
// Parameters: ArrayData arrData
void viewArrayData(ArrayData arrData);

// Function: getFakeCardStatus
// Description: Get fake card status
// Parameters: ArrayData arrData, int cardNumber
// Returns: bool fakeCardStatus
bool getFakeCardStatus(ArrayData arrData, int cardNumber);

// Function: getCardStatus
// Description: Get card status
// Parameters: int cardNumber
// Returns: CardStatus cardStatus
CardStatus getCardStatus(int cardNumber, ArrayData *data);

// Function: addDataToArray
// Description: Add data to array
// Parameters: ArrayData arrData, Data newData, int row
void addDataToArray(ArrayData *arrData, Data newData, int row);

// Function: updateDataToArray
// Description: Update data in array
// Parameters: ArrayData arrData, int id, char newAccess
void updateDataToArray(ArrayData *arrData, int id, char *newAccess);

#endif /* FILE_H */