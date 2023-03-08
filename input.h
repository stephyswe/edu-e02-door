#include <stdio.h>
#include <stdlib.h>

// struct files
#include "Score.h"
#include "Player.h"

// Function: playerAdd
// Description: Adds player to struct
// Parameters: int tries
// Returns: struct Player
Player playerAdd(int tries);

// Function: scoreCheck
// Description: Checks if score is highscore
// Parameters: int tries
// Returns: struct Score
Score scoreCheck(int tries);