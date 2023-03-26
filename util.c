#include <stdio.h>

// define file
#include "Define.h"

// struct files
#include "FileData.h"

// header files
#include "common.h"
#include "file.h"

bool findCardInFile(FileData fdata, int cardNumber, Card *card)
{
    const int MAX_ROW_LENGTH = 60;
    bool cardExist = false;

    while (fgets(fdata.file_row, MAX_ROW_LENGTH, fdata.file_ptr) != NULL && cardNumber >= getCardNumber(fdata.file_row))
    {
        if (cardNumber == getCardNumber(fdata.file_row))
        {
            cardExist = true;
            card->isAccess = isAccessInFile(fdata.file_row);
            card->date = getCardDateToFile(fdata.file_row);
            break;
        }
        card->row++;
    }

    card->endOfFile = feof(fdata.file_ptr);
    return cardExist;
}

void appendNewCard(FileData fdata, int cardNumber, Card *card)
{
    const int MAX_ROW_LENGTH = 60;
    const char *textFormat = card->endOfFile ? "\n%d %s %s %s" : "%d %s %s %s\n";
    char *date = getCurrentDate("%Y-%m-%d");

    snprintf(fdata.file_row, MAX_ROW_LENGTH, textFormat, cardNumber, TEXT_NO_ACCESS, TEXT_ADDED, date);
    addDataToFile("door.txt", card->row, fdata.file_row);

    // use in vg-file as file update whole row, not only access status
    card->date = date;
}

Card getCardInfo(int cardNumber)
{
    FileData fdata = useDoorFile("r+");

    Card card = {
        .row = 1,
        .endOfFile = false,
        .isAccess = false,
        .date = NULL};

    bool cardExist = findCardInFile(fdata, cardNumber, &card);

    if (!cardExist)
    {
        appendNewCard(fdata, cardNumber, &card);
    }

    fclose(fdata.file_ptr);

    return card;
}

bool getFakeCardStatus(int cardNumber)
{
    // variables
    FileData fdata = useDoorFile("r");
    bool cardAccess = false;

    // Iterate through the file until we find the card number
    while (fgets(fdata.file_row, 60, fdata.file_ptr) != NULL)
    {
        if (cardNumber == getCardNumber(fdata.file_row))
        {
            cardAccess = isAccessInFile(fdata.file_row);
            break;
        }
    }

    fclose(fdata.file_ptr);

    return cardAccess;
};