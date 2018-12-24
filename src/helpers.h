#ifndef _HELPERS_H
#ifndef _GAME_H
#include "game.h"
#endif
#define _HELPERS_H

// Converts 2D representation to 1D representation
#define ind(i, j) ((i)*10 + (j))

// Returns minimum of the 2 args
int min(int, int);

// Return maximum of the 2 args
int max(int a, int b);

// Initializes the game state
void init(struct gameState *);

// Displays the game state
void display(struct gameState *);

// Checks validity of a move
int validMove(int[89], int);

// Checks if the location passed is on board
int onBoard(int);

// Returns the disc at location passed
int getDisc(struct gameState *, int, int);

// Displays the winner or prints "It is a draw." in case of draw
void displayWinner(struct gameState *);

#endif