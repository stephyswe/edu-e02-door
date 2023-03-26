#include <stdio.h>
#include <time.h>

// struct files
#include "FileData.h"

// header files
#include "common.h"
#include "array.h"
#include "generate.h"

// define values
#define TEXT_NO_ACCESS "No access"
#define TEXT_ACCESS "Access"
#define TEXT_ADDED " Added to system:"

bool findCardInArray(ArrayData *arrData, int cardNumber, Card *card)
{
    // use while loop to find the card number
    int i = 0;
    bool cardExist = false;

    while (i < arrData[0].size && cardNumber >= arrData->data[i].id)
    {
        if (cardNumber == arrData->data[i].id)
        {
            cardExist = true;
            card->isAccess = isAccessInArray(*arrData, i);
            getCardDateToArray(card, arrData->data[i].date);
            break;
        }
        card->row++;
        i++;
    }
    card->endOfFile = card->row >= arrData->size;
    return cardExist;
}

void appendNewCard(ArrayData *arrData, int cardNumber, Card *card)
{
    const char *textFormat = card->endOfFile ? "\n%d %s %s %s" : "%d %s %s %s\n";
    char *date = getCurrentDate("%Y-%m-%d");
    addDataToArray(arrData, (Data){cardNumber, concatStrings(TEXT_NO_ACCESS, TEXT_ADDED), date}, card->row);
}

Card getCardInfo(int cardNumber, ArrayData *arrData)
{
    Card card = {
        .row = 0,
        .endOfFile = false,
        .isAccess = false,
        .date = NULL};

    bool cardExist = findCardInArray(arrData, cardNumber, &card);

    if (!cardExist)
    {
        appendNewCard(arrData, cardNumber, &card);
    }

    return card;
};

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

bool validateModifyInput(int input, Card card, int cardNumber, char *text)
{
    // variables
    bool modify = false;
    const int MAX_ROW_LENGTH = 60;

    // check if input is 1 or 2
    if ((input == 1 && !card.isAccess) || (input == 2 && card.isAccess))
    {
        // decide action
        const char *action = input == 1 ? TEXT_ACCESS : TEXT_NO_ACCESS;

        // text
        snprintf(text, MAX_ROW_LENGTH, "%s", concatStrings(action, TEXT_ADDED));

        // modify row in file
        modify = true;
    }
    return modify;
};

void initialDataWithLoop(ArrayData *arrData, int size)
{
    arrData->size = size;
    arrData->data = malloc(arrData->size * sizeof(Data));

    srand(time(NULL)); // Initialize random number generator with current time

    for (int i = 0; i < arrData->size; i++)
    {
        arrData->data[i].date = genDate();
        arrData->data[i].id = rand() % 9900 + 100;
        arrData->data[i].access = concatStrings((rand() % 2 == 0) ? TEXT_NO_ACCESS : TEXT_ACCESS, TEXT_ADDED);
    }

    // Sort the array after id
    qsort(arrData->data, arrData->size, sizeof(Data), compareIds);
};