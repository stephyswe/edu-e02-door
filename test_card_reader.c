#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// test header files
#include "test_util.h"
#include "test_common.h"

// Calls the function being tested and checks the result
void test_function(int (*func)(), char *input)
{
    // Mock the user input
    int stdin_fd = mock_input(input);

    // Call the function being tested
    int result = func();

    // Reset stdin
    reset_stdin(stdin_fd);

    // Close the temporary file
    fclose(stdin);

    // Check if the result is correct
    if (result == atoi(input))
    {
        printf("Test case passed\n");
    }
    else
    {
        printf("Test case failed\n");
    }
}

// Function being tested
int my_function()
{
    int value;
    printf("Enter a value: ");
    scanf("%d", &value);
    return value;
}


void testCommon()
{
    // test concatStrings
    printf("before test_concatStrings\n");
    test_concatStrings();

    // test pauseKeyboard - TODO
    // test_pauseKeyboard()

    // test waitSeconds
    printf("before waitSeconds\n");
    test_waitSeconds();

    // test_getCardDateToFile
    printf("before test_getCardDateToFile\n");
    test_getCardDateToFile();

    printf("before test_function\n");

    // Test the function - mock user input demo
    test_function(my_function, "42");
}

int main()
{
    // Test the function
    testCommon();

    return 0;
}
