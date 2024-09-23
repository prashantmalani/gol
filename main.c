/* Game Of Life primary executable */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "gol.h"

#define NUM_TICKS 3

enum Pattern {
    BLINKER = 0,
    TOAD,
    BEACON,
    RANDOM,
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

const int toad_arr[][COLS] = {
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 1, 1, 1, 0, 0},
    {0, 0, 1, 1, 1, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0}
};

const int beacon_arr[][COLS] = {
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 1, 1, 0},
    {0, 0, 0, 0, 0, 1, 1, 0},
    {0, 0, 0, 1, 1, 0, 0, 0},
    {0, 0, 0, 1, 1, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0}
};

const int random_arr[][COLS] = {
    {0, 0, 0, 1, 1, 0, 1, 1},
    {0, 0, 0, 1, 1, 1, 1, 0},
    {0, 1, 1, 1, 1, 0, 1, 0},
    {0, 1, 1, 0, 0, 0, 1, 1},
    {0, 0, 1, 0, 1, 1, 1, 1},
    {1, 1, 1, 0, 1, 1, 1, 1},
    {1, 1, 1, 1, 0, 1, 1, 0},
    {1, 0, 1, 0, 0, 0, 0, 1}
};

int loadState(int arr[][COLS], int pattern) {
    /* Load the state. */
    const int (*target)[COLS];
    if (pattern == BLINKER) {
        target = blinker_arr;
    } else if (pattern == TOAD) {
        target = toad_arr;
    } else if (pattern == BEACON) {
        target = beacon_arr;
    } else if (pattern == RANDOM) {
        target = random_arr;
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

/* Print out the provided array */
void printState(const int arr[][COLS]) {
    printf("\n");
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            printf("%c ", arr[i][j] ? 'X' : '.');
        }
        printf("\n");
    }
}

/* Calculate the next state, given current state in |arr|. */
void doTick(int arr[][COLS]) {
    int extend[ROWS+2][COLS+2] = {0};
    int ngbr[3][3] = {0};
    int newstate[ROWS][COLS] = {0};

    extendArray(arr, extend);

    /* Calculate the next state for each cell. */
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            getNeighbours(extend, ngbr, i, j);
            bool live = calcState(ngbr);
            newstate[i][j] = live ? 1 : 0;
        }
    }

    /* Copy new state into arr */
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            arr[i][j] = newstate[i][j];
        }
    }

    printState(arr);
}

void doGol(int pattern) {
    int state[ROWS][COLS] = {0};
    if (loadState(state, pattern))
        return;

    printState(state);
    for (int i = 0; i < NUM_TICKS; i++) {
        doTick(state);
    }
}

int main(int argc, char *argv[]) {
    if (argc > 2) {
        printf("Usage ./gol <pattern>\n");
        return 1;
    }

    int pattern;
    if (argc == 1 || !strcmp(argv[1], "random")) {
        pattern = RANDOM;
        printf("Random\n");
    } else if (!strcmp(argv[1], "blinker")) {
        pattern = BLINKER;
        printf("Blinker\n");
    } else if (!strcmp(argv[1], "toad")) {
        pattern = TOAD;
        printf("Toad\n");
    } else if (!strcmp(argv[1], "beacon")) {
        pattern = BEACON;
        printf("Beacon\n");
    } else {
        printf("Unknown pattern: %s\n", argv[1]);
        return 1;
    }

    doGol(pattern);

    return 0;
}
