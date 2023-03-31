// Redirects stdout to a given file descriptor
int redirect_stdin(int fd);

// Resets stdin to a given file descriptor
int reset_stdin(int fd);

// Second reset stdin function
int reset_stdin_multiple(int fd, FILE *temp_file);

// Mocks user input by redirecting stdin to a temporary file with the given input
int mock_input(char *input);

// Mocks user input by redirecting stdin to a temporary file with the given inputs
int mock_inputs(char *inputs[], int num_inputs);

// Used to test assert statements & free memory
void use_assert(int condition, void *ptr);