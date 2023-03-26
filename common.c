#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>

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
    const int MILLISECONDS = 1000;
    clock_t endTime = clock() + seconds * MILLISECONDS;
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
        const char *date_start = strstr(row, ": ");

        if (date_start == NULL)
        {
            // ": " not found in row, return NULL
            return NULL;
        }

        date_start += 2;

        // Check that the date has the correct format (YYYY-MM-DD)
        if (strlen(date_start) < 10 || date_start[4] != '-' || date_start[7] != '-')
        {
            printf("Invalid date format.\n");
            free(date);
            return NULL;
        }

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

// Helper function to extract the card number from a row
int getCardNumber(char *row)
{
    int number;
    sscanf(row, "%d %*s %*s", &number);
    return number;
}
