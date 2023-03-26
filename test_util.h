// Redirects stdout to a given file descriptor
int redirect_stdin(int fd);

// Resets stdin to a given file descriptor
int reset_stdin(int fd);

// Mocks user input by redirecting stdin to a temporary file with the given input
int mock_input(char *input);

// Used to test assert statements & free memory
void use_assert(int condition, void* ptr);