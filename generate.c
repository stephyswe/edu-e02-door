#include <stdio.h>
#include <stdlib.h>

// struct files
#include "FileData.h"

// Generates a random integer between min and max (inclusive)
int randomInt(int min, int max)
{
    return min + rand() % (max - min + 1);
}

int genDay(int month, int year)
{
    int max_days = 31;
    if (month == 2)
    {
        // Check if it's a leap year
        if ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0)
        {
            max_days = 29;
        }
        else
        {
            max_days = 28;
        }
    }
    else if (month == 4 || month == 6 || month == 9 || month == 11)
    {
        max_days = 30;
    }
    int day = rand() % max_days + 1;
    return day;
}

char *genDate()
{
    char *dateStr = malloc(11 * sizeof(char));
    int year = randomInt(1990, 2023);
    int month = randomInt(1, 12);
    int day = genDay(month, year);

    // Format the date string
    sprintf(dateStr, "%04d-%02d-%02d", year, month, day);
    return dateStr;
}

// Define the comparison function for qsort
int compareIds(const void *a, const void *b)
{
    Data *dataA = (Data *)a;
    Data *dataB = (Data *)b;
    return dataA->id - dataB->id;
}