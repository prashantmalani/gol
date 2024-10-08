/*
 * Unit tests for various functions used in the main program.
 */

#include <stdbool.h>
#include <stdio.h>

#include "gol.h"

struct calcStateTestCase {
    int arr[3][3];
    bool result;
};

struct calcStateTestCase cases[] = {
    /* Case 1 */
    {
        {{1,1,1},
         {1,0,1},
         {1,0,1}},
        false,
    },
    /* Case 2 */
    {
        {{1,0,1},
         {1,0,1},
         {1,0,1}},
        false,
    },
    /* Case 3 */
    {
        {{0,0,1},
         {0,0,1},
         {0,0,1}},
        true,
    },
    /* Case 4 */
    {
        {{0,1,1},
         {0,0,1},
         {0,0,0}},
        true,
    },
    /* Case 5 */
    {
        {{1,1,1},
         {0,1,1},
         {0,0,0}},
        false,
    },
    /* Case 6 */
    {
        {{0,1,1},
         {0,1,1},
         {1,0,0}},
        false,
    },
    /* Case 7 */
    {
        {{0,1,1},
         {0,1,1},
         {1,0,1}},
        false,
    },
    /* Case 8 */
    {
        {{0,1,1},
         {0,1,0},
         {0,0,0}},
        true,
    },
    /* Case 9 */
    {
        {{0,1,0},
         {1,1,0},
         {0,0,0}},
        true,
    },
    /* Case 10 */
    {
        {{0,1,0},
         {1,1,0},
         {0,1,0}},
        true,
    },
    /* Case 11 */
    {
        {{0,0,1},
         {0,1,0},
         {1,0,0}},
        true,
    },
    /* Case 12 */
    {
        {{1,0,1},
         {0,1,0},
         {0,0,0}},
        true,
    },
    /* Case 13 */
    {
        {{1,1,1},
         {0,1,0},
         {0,0,0}},
        true,
    },
    /* Case 14 */
    {
        {{0,0,1},
         {0,1,1},
         {0,0,1}},
        true,
    },
    /* Case 15 */
    {
        {{0,0,0},
         {0,1,0},
         {0,0,1}},
        false,
    },
    /* Case 16 */
    {
        {{0,0,0},
         {0,1,0},
         {1,0,0}},
        false,
    },
};

const int extendArrayTest[][COLS] = {
    {1,1,1,0,1,0,1,0},
    {0,1,1,0,1,1,0,0},
    {0,1,1,0,1,1,1,1},
    {0,1,1,0,1,1,0,0},
    {1,1,1,0,1,0,1,1},
    {0,1,1,0,1,1,1,0},
    {0,0,1,0,1,0,1,0},
    {0,1,1,0,1,1,1,1},
};

const int extendArrayResult[][COLS+2] = {
    {1,0,1,1,0,1,1,1,1,0},
    {0,1,1,1,0,1,0,1,0,1},
    {0,0,1,1,0,1,1,0,0,0},
    {1,0,1,1,0,1,1,1,1,0},
    {0,0,1,1,0,1,1,0,0,0},
    {1,1,1,1,0,1,0,1,1,1},
    {0,0,1,1,0,1,1,1,0,0},
    {0,0,0,1,0,1,0,1,0,0},
    {1,0,1,1,0,1,1,1,1,0},
    {0,1,1,1,0,1,0,1,0,1},
};

struct neighboursTestResult {
    int row;
    int col;
    int arr[3][3];
};

struct neighboursTestResult getNeighboursResults[] = {
    /* Case 1 */
    {
        0,
        0,
        {{1,0,1},
        {0,1,1},
        {0,0,1}}
    },
    /* Case 2 */
    {
        7,
        7,
        {{1,0,0},
        {1,1,0},
        {1,0,1}}
    },
    /* Case 3 */
    {
        7,
        0,
        {{0,0,0},
        {1,0,1},
        {0,1,1}}
    },
    /* Case 4 */
    {
        3,
        3,
        {{1,0,1},
        {1,0,1},
        {1,0,1}}
    },
};

/* Series of tests that verifies that calcState works correctly. */
void testCalcState() {
    printf("Running calcState test cases.\n");
    for (int i = 0; i < (int)(sizeof(cases) / sizeof(cases[0])); i++) {
        if (calcState(cases[i].arr) != cases[i].result)
            printf("Calc state case %d failed\n", i + 1);
    }
}

/* Tests that the code used to expand the array works correctly. */
void testExtendArray() {
    printf("Running extendArray test case.\n");
    int arr[ROWS+2][COLS+2] = {0};

    extendArray(extendArrayTest, arr);

    for (int i = 0; i < ROWS+2; i++) {
        for (int j = 0; j < COLS+2; j++) {
            if (arr[i][j] != extendArrayResult[i][j]) {
                printf("Mismatch in extended array check");
                break;
            }
        }
    }
}

/* Helper function to compare two neighbour arrays */
bool checkNeighbours(const int arr[][3], const int compare[][3]) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (arr[i][j] != compare[i][j])
                return false;
        }
    }
    return true;
}


/* Tests that the code used to construct neighbours array works correctly. */
void testGetNeighbours() {
    printf("Running getNeighbours test cases.\n");

    int arr[3][3] = {0};
    for (int i = 0; i < (int)(sizeof(getNeighboursResults) / sizeof(getNeighboursResults[0])); i++) {
        getNeighbours(extendArrayResult, arr,
                      getNeighboursResults[i].row,
                      getNeighboursResults[i].col);
        if (!checkNeighbours(arr, getNeighboursResults[i].arr)) {
            printf("Neighbours check for Case %d failed\n", i + 1);
        }
    }
}

int main() {
    testCalcState();
    testExtendArray();
    testGetNeighbours();
}
