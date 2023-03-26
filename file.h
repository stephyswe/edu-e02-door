#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// struct files
#include "FileData.h"

// Function: isAccessInFile
// Description: Check if access is in file
// Parameters: char row
// Returns: bool
bool isAccessInFile(char *row);

// Function: viewFileData
// Description: View all file data in door file
void viewFileData();

// Function: useFile
// Description: use the file and returns the data
// Parameters: char fileName, char mode
// Returns: FileData fileData
FileData useFile(char *fileName, char *mode);

// Function: useDoorFile
// Description: use the door file and returns the data
// Parameters: char mode
// Returns: FileData fileData
FileData useDoorFile(char *mode);

// Function: addDataToFile
// Description: Add data to file
// Parameters: char file_path, int rowLine, char text
void addDataToFile(char *file_path, int rowLine, char *text);

// Function: updateDataToFile
// Description: Modify row in file
// Parameters: int rowNumber, char newRow
void updateDataToFile(int rowNumber, char *newRow);