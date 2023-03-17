#include <stdbool.h>

typedef enum
{
	INPUT_RESULT_OK,
	INPUT_RESULT_TOO_LONG,
	INPUT_RESULT_NO_INPUT,
	INPUT_RESULT_EXIT
} INPUT_RESULT;

// Function: GetInput
// Description: Get input type int
// Parameters: char *prompt, char *buff, int maxSize
// Returns: INPUT_RESULT
INPUT_RESULT GetInput(char *prompt, char *buff, int maxSize);

// Function: GetInputAlt
// Description: Get input type int (alternative)
// Parameters: char *prompt, char *buff, int maxSize
// Returns: INPUT_RESULT
INPUT_RESULT GetInputAlt(char *prompt, char *buff, int maxSize);

// Function: GetInputInt
// Description: Get input type int
// Parameters: char *prompt, int *value
// Returns: bool
bool GetInputInt(char *prompt, int *value);

// Function: GetInputDouble
// Description: Get input type double
// Parameters: char *prompt, double *value
// Returns: bool
bool GetInputDouble(char *prompt, double *value);

// Function: GetInputChar
// Description: Get input type char
// Parameters: char *prompt, char *value
// Returns: bool
bool GetInputChar(char *prompt, char *value);