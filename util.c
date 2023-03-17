#include <stdio.h>

// define file
#include "Define.h"

// struct files
#include "FileData.h"

// header files
#include "common.h"
#include "file.h"

bool findCardInFile(FileData fdata, int cardNumber, CardStatus *cardStatus)
{

    bool cardExist = false;

    while (fgets(fdata.file_row, MAX_ROW_LENGTH, fdata.file_ptr) != NULL && cardNumber >= getCardNumber(fdata.file_row))
    {
        if (cardNumber == getCardNumber(fdata.file_row))
        {
            cardExist = true;
            cardStatus->hasAccess = isAccessInFile(fdata.file_row);
            cardStatus->date = getCardDateToFile(fdata.file_row);
            break;
        }
        cardStatus->row++;
    }

    cardStatus->endOfFile = feof(fdata.file_ptr);
    return cardExist;
}

void appendNewCard(FileData fdata, int cardNumber, CardStatus *cardStatus)
{
    const char *textFormat = cardStatus->endOfFile ? "\n%d %s %s %s" : "%d %s %s %s\n";
    char *date = getCurrentDate("%Y-%m-%d");

    snprintf(fdata.file_row, MAX_ROW_LENGTH, textFormat, cardNumber, TEXT_NO_ACCESS, TEXT_ADDED, date);
    addDataToFile(FILE_DOOR, cardStatus->row, fdata.file_row);

    // use in vg-file as file update whole row, not only access status
    cardStatus->date = date;
}

CardStatus getCardInfo(int cardNumber)
{
    FileData fdata = useFile(FILE_DOOR, "r+");

    CardStatus cardStatus = {
        .row = 1,
        .endOfFile = false,
        .hasAccess = false,
        .date = NULL};

    bool cardExist = findCardInFile(fdata, cardNumber, &cardStatus);

    if (!cardExist)
    {
        appendNewCard(fdata, cardNumber, &cardStatus);
    }

    fclose(fdata.file_ptr);

    return cardStatus;
}

bool getFakeCardStatus(int cardNumber)
{
    // variables
    FileData fdata = useFile(FILE_DOOR, "r");
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