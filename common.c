#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>

// header files
#include "Define.h"

int getTimeoutPerSecond(int seconds)
{
    clock_t endwait;
    endwait = clock() + seconds * CLOCKS_PER_SEC;
    while (clock() < endwait)
    {
    }

    return 1;
}

int getRandomNumber()
{
    // Initialize random number generator
    static int initialized = 0;

    // Initialize random number generator
    if (!initialized)
    {
        // Seed random number generator
        srand(time(NULL));

        // Set initialized to 1
        initialized = 1;
    }

    // Return random number
    return rand() % GAME_MAX + 1;
}

char *getCurrentDate()
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
    strftime(buffer, sizeof(buffer), "%d/%m/%Y %H:%M", local_time);

    // Copy buffer to date
    strcpy(date, buffer);

    // Return date
    return date;
}