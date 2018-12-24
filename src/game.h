#ifndef _GAME_H
#define _GAME_H

#define BLUE 1
#define RED 2
#define N 8

struct gameState {
    int board[89];
    int redScore;
    int blueScore;
    int currentPlayer;
};

// Inputs a move
int inputMove(struct gameState *);

// Checks for squares after a move, returns the score for new squares formed
int getScore(struct gameState *, int);

// Updates the state of the game
void updateState(struct gameState *, int, int);

// Checks if the game has ended
int gameEnd(struct gameState *);

// Checks the possible score of location passed as argument
int checkScore(struct gameState *, int);

// AI
int computerPlayer(struct gameState *);

#endif