#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// test header files
#include "test_util.h"
#include "test_common.h"

// header menu file
#include "menu.h"

void test_my_function2()
{
    // Call my_function and check its return value
    int result = menu();
    if (result == 0)
    {
        printf("Test passed!\n");
    }
    else
    {
        printf("Test failed!\n");
    }
}

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

void test_multiple_inputs()
{
    char buffer[100];
    char *input1 = "first input\n";
    char *input2 = "second input\n";

    // Mock user input
    printf("Enter first input: ");
    fgets(buffer, sizeof(buffer), stdin);
    if (strcmp(buffer, input1) != 0)
    {
        printf("Test failed: incorrect first input\n");
        return;
    }

    printf("Enter second input: ");
    fgets(buffer, sizeof(buffer), stdin);
    if (strcmp(buffer, input2) != 0)
    {
        printf("Test failed: incorrect second input\n");
        return;
    }

    printf("Test passed\n");
}

// Function being tested
int my_function()
{
    int value;
    printf("Enter a value: ");
    scanf("%d", &value);
    return value;
}

int my_function_multiple_at_once()
{
    int a, b, c;
    scanf("%d%d%d", &a, &b, &c);
    return a + b + c;
}

int my_function_multiple_one_by_one()
{
    int a, b, c;
    scanf("%d", &a);
    scanf("%d", &b);
    scanf("%d", &c);
    return a + b + c;
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

    test_my_function2();
}

void test_function_multiple_2(int (*func)(), char *inputs[], int num_inputs, int expected_output)
{
    // Mock the user input
    int stdin_fd = mock_inputs(inputs, num_inputs);
    FILE *temp_file = fdopen(stdin_fd, "r"); // Get a file pointer to the temporary file

    // Call the function being tested
    int result = func();

    // Reset stdin
    reset_stdin_multiple(stdin_fd, temp_file);

    // Check if the result is correct
    if (result == expected_output)
    {
        printf("Test case passed, result is: %d and expected output is: %d \n", result, expected_output);
    }
    else
    {
        printf("Test case failed, result is: %d and expected output is: %d \n", result, expected_output);
    }
}

void test_function_multiple(int (*func)(), char **inputs, int num_inputs)
{
    int passed = 0;

    for (int i = 0; i < num_inputs; i++)
    {
        // Mock the user input
        int stdin_fd = mock_input(inputs[i]);

        // Call the function being tested
        int result = func();

        // Reset stdin
        reset_stdin(stdin_fd);

        // Close the temporary file
        fclose(stdin);

        // Check if the result is correct
        if (result == atoi(inputs[i]))
        {
            printf("Test case %d passed\n", i + 1);
            passed++;
        }
        else
        {
            printf("Test case %d failed\n", i + 1);
        }
    }

    printf("%d/%d test cases passed\n", passed, num_inputs);
}

void test_my_function_multiple()
{
    char *inputs[] = {"2\n", "3\n", "4\n"};
    char *inputs2[] = {"2\n", "3\n", "4\n"};
    int expected_output = 9;
    test_function_multiple_2(my_function_multiple_at_once, inputs, 3, expected_output);
    test_function_multiple_2(my_function_multiple_one_by_one, inputs2, 3, expected_output);
}

int main()
{
    test_my_function_multiple();
    return 0;
}
