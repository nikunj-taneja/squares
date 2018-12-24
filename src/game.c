#include <stdio.h>
#include <stdlib.h>
#include "helpers.h"
#include "game.h"

int inputMove(struct gameState * state) {
    int move;
    printf("Please input your move: ");
    scanf("%d", &move);
    while (validMove(state->board, move) == 0 || validMove(state->board, move) == -1) {
        if (validMove(state->board, move) == -1) {
            printf("Input out of the game board, please "
                   "input again (in [11, 88]): ");
            scanf("%d", &move);
        }
        else if (validMove(state->board, move) == 0) {
            printf("Input invalid, the provided location is not "
                   "empty, please input again: ");
            scanf("%d", &move);
        }
    }
    return move;
}

int gameEnd(struct gameState * state) {
    if(state->redScore > 150 || state->blueScore > 150) {
        if(abs(state->redScore - state->blueScore) >= 15) {
            return 1;
        }
    }

    int fg = 0;
    for(int i = 1; i <= N; i++) {
        for(int j = 1; j <= N; j++) {
            if(state->board[ind(i, j)] == 0) {
                fg++;
                break;
            }
        }
    }
    if(fg)
        return 0;
    else
        return 1;
}

void updateState(struct gameState * state, int move, int score) {
    state->board[move] = state->currentPlayer;

    if(state->currentPlayer == BLUE)
        state->blueScore += score;
    else
        state->redScore += score;

    if(state->currentPlayer == BLUE)
        state->currentPlayer = RED;
    else
        state->currentPlayer = BLUE;
}

int getScore(struct gameState * state, int move) {
    int row = move/10;
    int col = move%10;
    int player = state->currentPlayer;
    int score = 0;
    int rMax = max(row, N - row);
    int cMax = max(col, N - col);
    int rMin = rMax > cMax ? 1 : 0;
    int cMin = rMax <= cMax ? 1 : 0;
    for (int i = rMin; i <= rMax; i++) {
        for (int j = cMin; j <= cMax; j++) {
            int point1 = getDisc(state, row + i, col + j) == player ? 1 : 0;
            int point2 = getDisc(state, row - j, col + i) == player ? 1 : 0;
            int point3 = getDisc(state, row - i, col - j) == player ? 1 : 0;
            int point4 = getDisc(state, row + j, col - i) == player ? 1 : 0;

            if (point1 && point2 && getDisc(state, row + i - j, col + j + i) == player) {
                int numCol;
                numCol = (max(col + j, max(col + i, max(col + j + i, col))) -
                         min(col + j, min(col + i, min(col + j + i, col))) + 1);
                int d1 = ind(row + i, col + j);
                int d2 = ind(row - j,  col + i);
                int d3 = ind(row, col);
                int d4 = ind(row + i - j, col + j + i);
                if (onBoard(d1) && onBoard(d2) && onBoard(d3) && onBoard(d4)) {
                    score += numCol * numCol;
                    printf("Discs %d %d %d %d form a square.\n", d1, d2, d3, d4);
                }
            }

            if (point2 && point3 && getDisc(state, row - j - i, col + i - j) == player) {
                int numCol = (max(col + i, max(col - j, max(col + i - j, col))) -
                             min(col + i, min(col - j, min(col + i - j, col))) + 1);
                int d1 = ind(row - j, col + i);
                int d2 = ind(row - i,  col - j);
                int d3 = ind(row, col);
                int d4 = ind(row - j - i, col + i - j);
                if (onBoard(d1) && onBoard(d2) && onBoard(d3) && onBoard(d4)) {
                    score += numCol * numCol;
                    printf("Discs %d %d %d %d form a square.\n", d1, d2, d3, d4);
                }
            }

            if (point3 && point4 && getDisc(state, row - i + j, col - j - i) == player) {
                int numCol = (max(col - j, max(col - i, max(col - j - i, col))) -
                             min(col - j, min(col - i, min(col - j - i, col))) + 1);
                int d1 = ind(row - i, col - j);
                int d2 = ind(row + j,  col - i);
                int d3 = ind(row, col);
                int d4 = ind(row - i + j, col - j - i);
                if (onBoard(d1) && onBoard(d2) && onBoard(d3) && onBoard(d4)) {
                    score += numCol * numCol;
                    printf("Discs %d %d %d %d form a square.\n", d1, d2, d3, d4);
                }
            }

            if (point4 && point1 && getDisc(state, row + j + i, col - i + j) == player) {
                int numCol = (max(col - i, max(col + j, max(col - i + j, col))) -
                             min(col - i, min(col + j, min(col - i + j, col))) + 1);
                int d1 = ind(row + j, col - i);
                int d2 = ind(row + i,  col + j);
                int d3 = ind(row, col);
                int d4 = ind(row + j + i, col - i + j);
                if (onBoard(d1) && onBoard(d2) && onBoard(d3) && onBoard(d4)) {
                    score += numCol * numCol;
                    printf("Discs %d %d %d %d form a square.\n", d1, d2, d3, d4);
                }
            }
        }
    }
    if (score > 0) {
        if (player == BLUE) {
            printf("Blue gets %d points!\n", score);
        }

        else {
            printf("Red gets %d points!\n", score);
        }
    }
    return score;
}

int checkScore(struct gameState * state, int move) {
    int row = move/10;
    int col = move%10;
    int player = state->currentPlayer;
    int score = 0;
    int rMax = max(row, N - row);
    int cMax = max(col, N - col);
    int rMin = rMax > cMax ? 1 : 0;
    int cMin = rMax <= cMax ? 1 : 0;
    for (int i = rMin; i <= rMax; i++) {
        for (int j = cMin; j <= cMax; j++) {
            int point1 = getDisc(state, row + i, col + j) == player ? 1 : 0;
            int point2 = getDisc(state, row - j, col + i) == player ? 1 : 0;
            int point3 = getDisc(state, row - i, col - j) == player ? 1 : 0;
            int point4 = getDisc(state, row + j, col - i) == player ? 1 : 0;

            if (point1 && point2 && getDisc(state, row + i - j, col + j + i) == player) {
                int numCol;
                numCol = (max(col + j, max(col + i, max(col + j + i, col))) -
                          min(col + j, min(col + i, min(col + j + i, col))) + 1);
                int d1 = ind(row + i, col + j);
                int d2 = ind(row - j,  col + i);
                int d3 = ind(row, col);
                int d4 = ind(row + i - j, col + j + i);
                if (onBoard(d1) && onBoard(d2) && onBoard(d3) && onBoard(d4)) {
                    score += numCol * numCol;
                }
            }

            if (point2 && point3 && getDisc(state, row - j - i, col + i - j) == player) {
                int numCol = (max(col + i, max(col - j, max(col + i - j, col))) -
                              min(col + i, min(col - j, min(col + i - j, col))) + 1);
                int d1 = ind(row - j, col + i);
                int d2 = ind(row - i,  col - j);
                int d3 = ind(row, col);
                int d4 = ind(row - j - i, col + i - j);
                if (onBoard(d1) && onBoard(d2) && onBoard(d3) && onBoard(d4)) {
                    score += numCol * numCol;
                }
            }

            if (point3 && point4 && getDisc(state, row - i + j, col - j - i) == player) {
                int numCol = (max(col - j, max(col - i, max(col - j - i, col))) -
                              min(col - j, min(col - i, min(col - j - i, col))) + 1);
                int d1 = ind(row - i, col - j);
                int d2 = ind(row + j,  col - i);
                int d3 = ind(row, col);
                int d4 = ind(row - i + j, col - j - i);
                if (onBoard(d1) && onBoard(d2) && onBoard(d3) && onBoard(d4)) {
                    score += numCol * numCol;
                }
            }

            if (point4 && point1 && getDisc(state, row + j + i, col - i + j) == player) {
                int numCol = (max(col - i, max(col + j, max(col - i + j, col))) -
                              min(col - i, min(col + j, min(col - i + j, col))) + 1);
                int d1 = ind(row + j, col - i);
                int d2 = ind(row + i,  col + j);
                int d3 = ind(row, col);
                int d4 = ind(row + j + i, col - i + j);
                if (onBoard(d1) && onBoard(d2) && onBoard(d3) && onBoard(d4)) {
                    score += numCol * numCol;
                }
            }
        }
    }
    return score;
}

int computerPlayer(struct gameState * state) {
    int maxScore = -1;
    int ans = 0;
    for(int x = 1; x <= N; x++) {
        for(int y = 1; y <= N; y++) {
            if(state->board[ind(x, y)] == 0) {
                int tempScore = checkScore(state, ind(x, y));
                if(tempScore > maxScore) {
                    ans = ind(x, y);
                    maxScore = tempScore;
                }
            }
        }
    }
    if(state->currentPlayer == RED)
        state->currentPlayer = BLUE;
    else
        state->currentPlayer = RED;
    int otherMaxScore = -1;
    int otherAns = 0;
    for(int x = 1; x <= N; x++) {
        for (int y = 1; y <= N; y++) {
            if (state->board[ind(x, y)] == 0) {
                int tempScore = checkScore(state, ind(x, y));
                if (tempScore > otherMaxScore) {
                    otherAns = ind(x, y);
                    otherMaxScore = tempScore;
                }
            }
        }
    }
    if(state->currentPlayer == RED)
        state->currentPlayer = BLUE;
    else
        state->currentPlayer = RED;
    if(maxScore < otherMaxScore) {
        ans = otherAns;
    }
    if(maxScore == 0 && otherMaxScore == 0) {
        int strategicMoves[] = {44, 46, 45, 26, 62, 24, 82, 77, 57, 73, 15, 43, 31, 35, 84, 28, 53, 42, 55, 74, 88, 14,
                                25, 52, 75, 32, 64, 54, 37};
        for(int i = 0; i < sizeof(strategicMoves)/sizeof(int); i++) {
            if(getDisc(state, strategicMoves[i]/10, strategicMoves[i]%10) == 0) {
                ans = strategicMoves[i];
                break;
            }
        }
    }
    return ans;
}
