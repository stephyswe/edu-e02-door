#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <assert.h>
#include <math.h>

#include "common.h"

// test header files
#include "test_util.h"

// Test function
void test_concatStrings()
{
    // Test case 1: concatenate two empty strings
    const char *str1 = "";
    const char *str2 = "";
    char *result = concatStrings(str1, str2);
    use_assert(strcmp(result, "") == 0, result);

    // Test case 2: concatenate two non-empty strings
    str1 = "Hello, ", str2 = "world!";
    result = concatStrings(str1, str2);
    use_assert(strcmp(result, "Hello, world!") == 0, result);

    // Test case 3: concatenate a non-empty string and an empty string
    str1 = "Test string", str2 = "";
    result = concatStrings(str1, str2);
    use_assert(strcmp(result, "Test string") == 0, result);

    // Test case 4: concatenate a long string and a short string
    str1 = "This is a long string that is longer than the other string.";
    str2 = "short";
    result = concatStrings(str1, str2);
    use_assert(strcmp(result, "This is a long string that is longer than the other string.short") == 0, result);
}

void test_waitSeconds()
{
    const int MILISECONDS = 1000;
    clock_t start = clock();

    // Call function being tested
    waitSeconds(3);

    clock_t end = clock();

    double elapsed_time = ((double)(end - start)) / MILISECONDS;

    // The first assertion checks if elapsed_time is equal to 3,
    // and the second assertion checks if the difference between elapsed_time and 3.0
    // is less than 0.0001 (to account for possible floating point inaccuracies).
    assert(elapsed_time == 3);
    assert(fabs(elapsed_time - 3.0) < 0.0001);
}

void test_getCardDateToFile()
{
    // Test case 1: valid input
    char *row1 = "Card date: 2022-03-31\n";
    char *date1 = getCardDateToFile(row1);
    use_assert(strcmp(date1, "2022-03-31") == 0, date1);

    // Test 2: input with incorrect format
    char *row2 = "Some other row";
    char *date2 = getCardDateToFile(row2);
    use_assert(date2 == NULL, date2);
}
