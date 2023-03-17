#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// struct files
#include "FileData.h"

// header files

bool isAccessInArray(ArrayData arrData, int i)
{
    return strcmp(arrData.data[i].access, "No access Added to system:") != 0;
}

void viewArrayData(ArrayData arrData)
{
    for (int i = 0; i < arrData.size; i++)
    {
        printf("%d %s %s\n", arrData.data[i].id, arrData.data[i].access, arrData.data[i].date);
    }
};

void updateDataToArray(ArrayData *arrData, int cardNumber, char *newAccess)
{
    // Loop through the array to find the row with the specified id
    for (int i = 0; i < arrData->size; i++)
    {
        if (cardNumber == arrData->data[i].id)
        {
            // Update the access field
            strncpy(arrData->data[i].access, newAccess, strlen(newAccess));
            arrData->data[i].access[strlen(newAccess)] = '\0'; // Ensure null termination                                                 // Exit the function after updating the data
        }
    }
}

void addDataToArray(ArrayData *arrData, Data newData, int row)
{
    if (row < 0 || row > arrData->size)
    {
        printf("Invalid row specified.\n");
        return;
    }

    // Increase the size of the data array by 1
    arrData->data = realloc(arrData->data, (arrData->size + 1) * sizeof(Data));

    // Shift existing data up to make space for the new data
    memmove(&arrData->data[row + 1], &arrData->data[row], (arrData->size - row) * sizeof(Data));

    // Insert the new data
    arrData->data[row] = newData;

    // Increment the size of the array
    arrData->size++;
}