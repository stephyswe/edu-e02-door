#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <io.h>
#include <fcntl.h>

// Redirects stdin to a given file descriptor
int redirect_stdin(int fd)
{
    // Save the original stdin file descriptor
    int stdin_fd = dup(STDIN_FILENO);

    // Redirect stdin to the given file descriptor
    if (dup2(fd, STDIN_FILENO) == -1)
    {
        printf("Failed to redirect stdin\n");
        return -1;
    }

    return stdin_fd;
}

// Resets stdin to a given file descriptor
int reset_stdin(int fd)
{
    // Reset stdin to the given file descriptor
    if (dup2(fd, STDIN_FILENO) == -1)
    {
        printf("Failed to reset stdin\n");
        return -1;
    }

    return 0;
}


// Mocks user input by redirecting stdin to a temporary file with the given input
int mock_input(char *input)
{
    // Open a temporary file to hold the mock input
    FILE *tmp_file = tmpfile();
    if (tmp_file == NULL)
    {
        printf("Failed to open temporary file\n");
        return -1;
    }

    // Write the mock input to the temporary file
    fprintf(tmp_file, "%s\n", input);
    rewind(tmp_file);

    // Redirect stdin to the temporary file
    int fd = redirect_stdin(fileno(tmp_file));
    if (fd == -1)
    {
        fclose(tmp_file);
        return -1;
    }

    return fd;
}

// Assert function to check if a condition is true and free memory if needed
void use_assert(int condition, void* ptr)
{
    if (!condition)
    {
        free(ptr);
        printf("Assertion failed!\n");
        exit(1);
    }
}