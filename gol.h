#include <stdbool.h>

#define ROWS 8
#define COLS 8

bool calcState(const int arr[3][3]);
void extendArray(const int in[][COLS], int out[][COLS+2]);
void getNeighbours(const int arr[][COLS+2], int **out, int row, int cols);
