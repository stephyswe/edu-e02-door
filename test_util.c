#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <io.h>
#include <fcntl.h>
#include <sys/stat.h>

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
int reset_stdin_multiple(int stdin_fd, FILE *temp_file)
{
    fflush(stdin);                // Flush any remaining input from the temporary file
    dup2(stdin_fd, STDIN_FILENO); // Restore stdin to its original file descriptor
    close(stdin_fd);              // Close the copy of the original stdin file descriptor
    fclose(temp_file);            // Close the temporary file
    remove("temp.txt");           // Remove the temporary file from the file system
    return 0;
}

int reset_stdin(int stdin_fd)
{
    // Close the temporary file descriptor
    close(STDIN_FILENO);

    // Reopen the original stdin file descriptor
    dup2(stdin_fd, STDIN_FILENO);

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

int mock_inputs(char *inputs[], int num_inputs)
{
    int stdin_fd = dup(STDIN_FILENO);                                    // Save a copy of the original stdin file descriptor
    int temp_fd = open("temp.txt", O_CREAT | O_RDWR, S_IRUSR | S_IWUSR); // Create a temporary file for input

    for (int i = 0; i < num_inputs; i++)
    {
        write(temp_fd, inputs[i], strlen(inputs[i])); // Write each input to the temporary file
    }

    lseek(temp_fd, 0, SEEK_SET); // Reset file offset to the beginning of the file
    dup2(temp_fd, STDIN_FILENO); // Replace stdin with the temporary file descriptor

    return stdin_fd; // Return the original stdin file descriptor for resetting later
}

// Assert function to check if a condition is true and free memory if needed
void use_assert(int condition, void *ptr)
{
    if (!condition)
    {
        free(ptr);
        printf("Assertion failed!\n");
        exit(1);
    }
}