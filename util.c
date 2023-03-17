#include <stdio.h>

// define file
#include "Define.h"

// struct files
#include "FileData.h"

// header files
#include "common.h"
#include "array.h"

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
            card->hasAccess = isAccessInArray(*arrData, i);
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
        .hasAccess = false,
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
