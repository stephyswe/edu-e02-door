#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// struct files
#include "FileData.h"
#include "Player.h"

#ifndef FILE_H
#define FILE_H

// Function: viewAllCards
// Description: View all cards
void viewAllCards();

// Function: useFile
// Description: use the file and returns the data
// Parameters: char filename, char mode
// Returns: FileData file_data
FileData useFile(char *filename, char *mode);

// Function: modifyRow
// Description: Modify row in file
// Parameters: int row_number, char new_row
void modifyRow(int row_number, char *new_row);

// Function: viewStatusCards
// Description: View status of cards
// Parameters: int cardNumber
// Returns: FileCard card
FileCard viewStatusCards(int cardNumber);

// Function: getFakeCardStatus
// Description: Get fake card status
// Parameters: int cardNumber
bool getFakeCardStatus(int cardNumber);

#endif /* FILE_H */