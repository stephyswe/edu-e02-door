// Description: concatStrings
// Parameters: const char *str1, const char *str2
// Returns: char *result
char *concatStrings(const char *str1, const char *str2);

// Function: pauseKeyboard
// Description: Pause keyboard
void pauseKeyboard();

// Function: waitSeconds
// Description: Timeout function per second
// Parameters: int seconds
void waitSeconds(int seconds);

// Function: getCurrentDate
// Description: Returns card date
// Returns: char *date
char* getCardDateToFile(char *row);

// Function: getCurrentDate specific format
// Description: Returns current date
// Parameters: char *format
// Returns: char *date
char *getCurrentDate(char *format);