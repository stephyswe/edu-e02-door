#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include <string.h>
#include <unistd.h>

// define file
#include "Define.h"

// struct files
#include "FileData.h"

// header files
#include "file.h"
#include "common.h"

// Helper function to show array data
void viewArrayData(ArrayData arrData)
{
    for (int i = 0; i < arrData.size; i++)
    {
        printf("%d %s %s\n", arrData.data[i].id, arrData.data[i].access, arrData.data[i].date);
    }
};

// Helper function to check if a row indicates the card has no access
bool isAccessInArray(ArrayData arrData, int i)
{
    return strcmp(arrData.data[i].access, "No access Added to system:") != 0;
}

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

bool findCardInArray(ArrayData *arrData, int cardNumber, CardStatus *cardStatus)
{
    // use while loop to find the card number
    int i = 0;
    bool cardExist = false;

    while (i < arrData[0].size && cardNumber >= arrData->data[i].id)
    {
        if (cardNumber == arrData->data[i].id)
        {
            cardExist = true;
            cardStatus->hasAccess = isAccessInArray(*arrData, i);
            getCardDateToArray(cardStatus, arrData->data[i].date);
            break;
        }
        cardStatus->row++;
        i++;
    }
    cardStatus->endOfFile = cardStatus->row >= arrData->size;
    return cardExist;
}

void appendNewCard(ArrayData *arrData, int cardNumber, CardStatus *cardStatus)
{
    const char *textFormat = cardStatus->endOfFile ? "\n%d %s %s %s" : "%d %s %s %s\n";
    char *date = getCurrentDate("%Y-%m-%d");
    addDataToArray(arrData, (Data){cardNumber, concatStrings(TEXT_NO_ACCESS, TEXT_ADDED), date}, cardStatus->row);
}

CardStatus getCardInfo(int cardNumber, ArrayData *arrData)
{
    CardStatus cardStatus = {
        .row = 0,
        .endOfFile = false,
        .hasAccess = false,
        .date = NULL};

    bool cardExist = findCardInArray(arrData, cardNumber, &cardStatus);

    if (!cardExist)
    {
        appendNewCard(arrData, cardNumber, &cardStatus);
    }

    return cardStatus;
}

bool getFakeCardStatus(ArrayData arrData, int cardNumber)
{
    bool cardAccess = false;

    // Iterate through the array
    for (int i = 0; i < arrData.size; i++)
    {
        // Check if the card number matches
        if (cardNumber == arrData.data[i].id)
        {
            cardAccess = isAccessInArray(arrData, i);
            break;
        }
    }

    return cardAccess;
};
