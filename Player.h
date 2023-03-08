#include <stdio.h>

#ifndef PLAYER_H
#define PLAYER_H

// Function: Player
// Description: date, name and points
typedef struct
{
    char date[20];
    char name[20];
    int points;
} Player;

#endif