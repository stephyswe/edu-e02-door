#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>

// pauseKeyboard - _getch
#include <conio.h>

// header files
#include "Define.h"

char *concatStrings(const char *str1, const char *str2)
{
    size_t len1 = strlen(str1);
    size_t len2 = strlen(str2);
    char *result = malloc((len1 + len2 + 1) * sizeof(char)); // allocate memory for result string

    if (result == NULL)
    { // check for allocation failure
        printf("Error: unable to allocate memory.\n");
        return NULL;
    }

    strcpy(result, str1); // copy str1 to result
    strcat(result, str2); // concatenate str2 to result

    return result;
}

void pauseKeyboard()
{
    printf("\nPress any key to continue...\n");
    fflush(stdout); // Ensure prompt is displayed immediately

    int c;
    do
    {
        c = getchar();
    } while (c != EOF && c != '\n');
}

void waitSeconds(int seconds)
{
    clock_t endTime = clock() + seconds * CLOCKS_PER_SEC;
    // Pause execution until endTime is reached
    while (clock() < endTime)
    {
    }
}

char *getCardDateToFile(const char *row)
{
    // Allocate memory for 11 characters (10 for date, 1 for null terminator)
    char *date = malloc(11);

    if (date != NULL)
    {
        // Find the start of the date
        const char *date_start = strstr(row, ": ") + 2;

        // Copy date from row to date
        memcpy(date, date_start, 10);

        // Add a null terminator at the end
        date[10] = '\0';
    }

    // Return date
    return date;
}

char *getCurrentDate(char *format)
{
    // Allocate memory for date buffer
    char *date = malloc(11);

    // Get current date and time
    time_t current_time = time(NULL);

    // Convert to local time format and format date and time
    struct tm *local_time = localtime(&current_time);
    strftime(date, 11, format, local_time);

    // Return date buffer
    return date;
}

int getCardNumber(char *row)
{
    int number;
    sscanf(row, "%d %*s %*s", &number);
    return number;
}
