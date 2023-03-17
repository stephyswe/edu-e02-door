#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// struct files
#include "FileData.h"

// Function: isAccessInArray
// Description: Check if access is in array
// Parameters: ArrayData arrData, int i
// Returns: bool isAccessInArray
bool isAccessInArray(ArrayData arrData, int i);

// Function: viewArrayData
// Description: View all array data
// Parameters: ArrayData arrData
void viewArrayData(ArrayData arrData);

// Function: addDataToArray
// Description: Add data to array
// Parameters: ArrayData arrData, Data newData, int row
void addDataToArray(ArrayData *arrData, Data newData, int row);

// Function: updateDataToArray
// Description: Update data in array
// Parameters: ArrayData arrData, int id, char newAccess
void updateDataToArray(ArrayData *arrData, int id, char *newAccess);