#include <stdio.h>
#include <stdlib.h>
#include "game.h"
#include "helpers.h"

int main(void) {
    struct gameState game;
    int mode, validMode;
    init(&game);
    printf("[] SQUARES []\n1. Human v/s Human\n2. Human v/s Computer\nPlease select a game mode (1/2): ");
    do {
        scanf("%d", &mode);
        if(mode == 1) {
            validMode = 1;
            while (1) {
                display(&game);
                int move = inputMove(&game);
                updateState(&game, move, getScore(&game, move));
                if (gameEnd(&game)) {
                    displayWinner(&game);
                    break;
                }
            }
        }

        else if(mode == 2) {
            validMode = 1;
            while(1) {
                display(&game);
                if(game.currentPlayer == BLUE) {
                    int move = inputMove(&game);
                    updateState(&game, move, getScore(&game, move));
                }
                else {
                    int move = computerPlayer(&game);
                    printf("Computer chose %d.\n", move);
                    updateState(&game, move, getScore(&game, move));
                }
                if (gameEnd(&game)) {
                    displayWinner(&game);
                    break;
                }
            }
        }

        else {
            validMode = 0;
            printf("Invalid game mode, please enter a valid game mode (1/2): ");
        }
    } while(!validMode);
    return 0;
}