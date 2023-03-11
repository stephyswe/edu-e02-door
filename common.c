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
    printf("\nPress any key to continue...\n");
    fflush(stdout); // Ensure prompt is displayed immediately

    int c;
    do {
        c = getchar();
    } while (c != EOF && c != '\n');
}

void waitSeconds(int seconds)
{
    clock_t endTime = clock() + seconds * CLOCKS_PER_SEC;
    // Pause execution until endTime is reached
    while (clock() < endTime) { }
}

// Helper function to extract the date from a row
char* getCardDate(char *row)
{
    // allocate memory for 11 characters (10 for date, 1 for null terminator)
    char *date = malloc(11);

    // find the start of the date
    char *date_start = strstr(row, ": ") + 2;

    // copy date from row to date
    strncpy(date, date_start, 10);

    // add a null terminator at the end
    date[10] = '\0';

    // return date
    return date;
}

char *getCurrentDate(char *format)
{
    // Get current date and time
    time_t current_time = time(NULL);

    // Convert to local time format and print to stdout
    struct tm *local_time = localtime(&current_time);

    // Format date and time
    char buffer[100];

    // Date
    static char date[11];

    // Format date and time
    strftime(buffer, sizeof(buffer), format, local_time);

    // Copy buffer to date
    strcpy(date, buffer);

    // Return date
    return date;
}