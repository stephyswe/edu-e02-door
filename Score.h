#include <stdio.h>
#include <stdbool.h>

#ifndef SCORE_H
#define SCORE_H

// Struct: Score
// Description: confirm highscore and row
typedef struct
{
    bool isHighScore;
    int row;
} Score;

#endif