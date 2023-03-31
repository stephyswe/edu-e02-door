#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>

// header files
#include "input.h"

bool parseDouble(const char *str, double *val)
{
	char *temp;
	bool rc = true;
	errno = 0;
	*val = strtod(str, &temp);

	if (temp == str || *temp != '\0' ||
		(isnan(*val) && errno == ERANGE))
		rc = false;

	return rc;
}

bool parseLong(const char *str, long *val)
{
	char *temp;
	bool rc = true;
	errno = 0;
	*val = strtol(str, &temp, 0);

	if (temp == str || *temp != '\0' ||
		((*val == LONG_MIN || *val == LONG_MAX) && errno == ERANGE))
		rc = false;

	return rc;
}

bool parseChar(const char *str, char *val)
{
	if (str[0] == '\0' || str[1] != '\0')
	{
		return false;
	}
	*val = str[0];
	return true;
}

bool GetInputChar(char *prompt, char *value)
{
	char buff[255];
	if (GetInputAlt(prompt, buff, sizeof(buff)) != INPUT_RESULT_OK)
		return false;
	return parseChar(buff, value);
}

bool GetInputDouble(char *prompt, double *value)
{
	char buff[255];
	if (GetInputAlt(prompt, buff, sizeof(buff)) != INPUT_RESULT_OK)
		return false;
	double d = NAN;
	if (!parseDouble(buff, &d))
		return false;
	*value = d;
	return true;
}

bool GetInputInt(char *prompt, int *value)
{
	char buff[255];
	if (GetInputAlt(prompt, buff, sizeof(buff)) != INPUT_RESULT_OK)
		return false;
	long l = LONG_MIN;
	if (!parseLong(buff, &l))
		return false;
	*value = l;
	return true;
}

INPUT_RESULT GetInput(char *prompt, char *buff, int maxSize)
{

	if (prompt != NULL && strlen(prompt) > 0)
	{
		printf("%s", prompt);
	}
	if (fgets(buff, maxSize, stdin) == NULL || (strlen(buff) == 1 && buff[0] == '\n'))
		return INPUT_RESULT_NO_INPUT;

	// If it was too long, there'll be no newline. In that case, we flush
	// to end of line so that excess doesn't affect the next call.
	if (buff[strlen(buff) - 1] != '\n')
	{
		int extra = 0;
		char ch;
		while (((ch = getchar()) != '\n') && (ch != EOF))
			extra = 1;
		return (extra == 1) ? INPUT_RESULT_TOO_LONG : INPUT_RESULT_OK;
	}

	// Otherwise remove newline and give string back to caller.
	buff[strlen(buff) - 1] = '\0';
	return INPUT_RESULT_OK;
}

INPUT_RESULT GetInputAlt(char *prompt, char *buff, int maxSize)
{
	if (prompt != NULL && strlen(prompt) > 0)
	{
		printf("%s", prompt);
	}

	// Read input using fgets
	if (fgets(buff, maxSize, stdin) == NULL)
	{
		return INPUT_RESULT_NO_INPUT;
	}

	// If buff equal X or x, return;
	if (buff[0] == 'X' || buff[0] == 'x')
	{
		return INPUT_RESULT_EXIT;
	}

	// Remove newline character
	size_t len = strlen(buff);
	if (len > 0 && buff[len - 1] == '\n')
	{
		buff[len - 1] = '\0';
		len--;
	}

	// Remove leading whitespace
	char *start = buff;
	while (isspace(*start))
	{
		start++;
		len--;
	}

	// Remove trailing whitespace
	char *end = buff + len - 1;
	while (end > start && isspace(*end))
	{
		end--;
		len--;
	}
	*(end + 1) = '\0';

	// Check if the input was truncated
	if (len == maxSize - 1 && buff[maxSize - 2] != '\n')
	{
		int c;
		while ((c = getchar()) != '\n' && c != EOF)
			;
		return INPUT_RESULT_TOO_LONG;
	}

	return INPUT_RESULT_OK;
}