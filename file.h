#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// struct files
#include "FileData.h"

#ifndef FILE_H
#define FILE_H

// Function: viewFileData
// Description: View all file data
// Parameters: char fileName
void viewFileData(char *fileName);

// Function: useFile
// Description: use the file and returns the data
// Parameters: char fileName, char mode
// Returns: FileData fileData
FileData useFile(char *fileName, char *mode);

// Function: modifyRow
// Description: Modify row in file
// Parameters: int rowNumber, char newRow
void modifyRow(int rowNumber, char *newRow);

// Function: getFakeCardStatus
// Description: Get fake card status
// Parameters: int cardNumber
bool getFakeCardStatus(int cardNumber);

// Function: getCardStatus
// Description: Get card status
// Parameters: int cardNumber
// Returns: CardStatus cardStatus
CardStatus getCardStatus(int cardNumber);

#endif /* FILE_H */