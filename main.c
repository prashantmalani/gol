/* Game Of Life primary executable */

#include <string.h>
#include <stdio.h>

#include "gol.h"

enum Pattern{
    BLINKER = 0,
};

const int blinker_arr[][COLS] = {
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 1, 0, 0, 0},
    {0, 0, 0, 0, 1, 0, 0, 0},
    {0, 0, 0, 0, 1, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0}
};

int loadState(int arr[][COLS], int pattern) {
    // Load the state.
    const int (*target)[COLS];
    if (pattern == 0) {
        target = blinker_arr;
    } else {
        printf(__func__, "%s(): Invalid pattern %d", pattern);
        return -1;
    }

    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            arr[i][j] = target[i][j];
        }
    }

    return 0;
}

void printState(const int arr[][COLS]) {
    printf("\n");
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            printf("%c ", arr[i][j] ? 'X' : '.');
        }
        printf("\n");
    }
}

void doGol(int pattern) {
    int state[ROWS][COLS] = {0};
    loadState(state, pattern);

    printState(state);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage ./gol <pattern>\n");
        return 1;
    }

    int pattern;
    if (!strcmp(argv[1], "blinker")) {
        pattern = BLINKER;
        printf("Blinker\n");
    } else {
        printf("Unknown pattern: %s\n", argv[1]);
        return 1;
    }

    doGol(pattern);

    return 0;
}
