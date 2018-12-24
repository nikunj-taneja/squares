#include <stdio.h>
#include <stdlib.h>
#include "helpers.h"
#include "game.h"

int min(int a, int b) {
    return (a) < (b) ? (a) : (b);
}

int max(int a, int b) {
    return (a) > (b) ? (a) : (b);
}

void init(struct gameState * state) {
    for(int i = 1; i <= N; i++) {
        for(int j = 1; j <= N; j++) {
            state->board[ind(i, j)] = 0;
        }
    }

    state->redScore = 0;
    state->blueScore = 0;

    state->currentPlayer = BLUE;
}

void display(struct gameState * state) {
    printf("\n[ 0 Red's score : %d ; # Blue's score : %d ]\n", state->redScore, state->blueScore);
    printf("  ");
    for (int i = 1; i <= N; i++) {
        printf(" %d", i);
    }
    printf("\n");

    for (int i = 1; i <= N; i++) {
        printf("%d  ", i);
        for (int j = 1; j <= N; j++) {
            if (state->board[ind(i, j)] == 0)
                printf(". ");
            else if (state->board[ind(i, j)] == 1)
                printf("# ");
            else
                printf("0 ");
        }
        printf("\n");
    }
    printf("\n");
    if (!gameEnd(state)) {
        if (state->currentPlayer == BLUE)
            printf("This is Blue's turn.\n");
        else
            printf("This is Red's turn.\n");
    }
}

int validMove(int board[89], int move) {
    int x = move/10;
    int y = move%10;

    if(move < 11 || move > 88 || x < 1 || x > 8 || y < 1 || y > 8)
        return -1;

    else if(board[ind(x, y)] == BLUE || board[ind(x, y)] == RED)
        return 0;

    else
        return 1;
}

int onBoard(int point) {
    if(point < 11 || point > 88)
        return 0;
    else {
        int x = point/10;
        int y = point%10;
        if(x < 1 || x > 8 || y < 1 || y > 8)
            return 0;
        else
            return 1;
    }
}

int getDisc(struct gameState * state, int x, int y) {
    if(x < 1 || x > 8 || y < 1 || y > 8 || ind(x, y) < 11 || ind(x, y) > 88)
        return 0;
    else
        return state->board[ind(x, y)];
}

void displayWinner(struct gameState * state) {
    display(state);
    printf("GAME OVER!\n");
    if(state->redScore > state->blueScore) {
        printf("RED WINS with a score of %d.\n", state->redScore);
    }
    else if(state->blueScore > state->redScore) {
        printf("BLUE WINS with a score of %d.\n", state->blueScore);
    }
    else
        printf("It is a DRAW.\n");
    printf("Press any key to exit.");
    getchar();
}