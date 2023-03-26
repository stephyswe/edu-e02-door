#include <stdio.h>

// struct files
#include "FileData.h"

// header files
#include "common.h"
#include "file.h"

// define values
#define TEXT_NO_ACCESS "No access"
#define TEXT_ACCESS "Access"
#define TEXT_ADDED "Added to system:"

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

bool validateModifyInput(int input, Card card, int cardNumber, char *text)
{
    // variables
    bool modify = false;

    // check if input is 1 or 2
    if ((input == 1 && !card.isAccess) || (input == 2 && card.isAccess))
    {
        // decide action
        const char *action = input == 1 ? TEXT_ACCESS : TEXT_NO_ACCESS;

        // text
        snprintf(text, 256, "%d %s %s %s", cardNumber, action, TEXT_ADDED, card.date);

        // modify row in file
        modify = true;
    }
    return modify;
}