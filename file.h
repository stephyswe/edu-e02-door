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

// Function: viewStatusCards
// Description: View status of cards
// Parameters: int cardNumber
// Returns: FileCard card
FileCard viewStatusCards(int cardNumber);

// Function: getFakeCardStatus
// Description: Get fake card status
// Parameters: int cardNumber
bool getFakeCardStatus(int cardNumber);

// Function: getStatusCard
// Description: Get status card
// Parameters: int cardNumber
// Returns: FileStatusCard statusCard
FileStatusCard getStatusCard(int cardNumber);

// Function: appendCardIfNotExist
// Description: Append card if not exist
// Parameters: FileStatusCard fileStatusCard, int cardNumber
// Returns: FileCard fileCard
FileCard AppendCardIfNotExist(FileStatusCard fileStatusCard, int cardNumber);

#endif /* FILE_H */