#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>

// pauseKeyboard - _getch
#include <conio.h>

// header files
#include "Define.h"

void pauseKeyboard()
{
    printf("\nPress key to continue\n");
    _getch();
}

int getTimeoutPerSecond(int seconds)
{
    clock_t endwait;
    endwait = clock() + seconds * CLOCKS_PER_SEC;
    while (clock() < endwait)
    {
    }

    return 1;
}

// Helper function to extract the date from a row
char* getCardDate(char *row)
{
    char *date = malloc(11); // allocate memory for 11 characters (10 for date, 1 for null terminator)
    char *date_start = strstr(row, ": ") + 2;
    strncpy(date, date_start, 10);
    date[10] = '\0'; // add a null terminator at the end
    return date;
}