/* https://adventofcode.com/2025/day/4
 *
 * we get a map (a 2D grid) containing either dots (.) or ats (@).
 * Each at is a roll.
 * A roll is accessible if it has less than 4 other rolls within
 * its 8 adjacent neighbours
 *
 * The challenge: count the number of accessible rolls given a map
 */
#include <assert.h>
#include <stdio.h>
#include <string.h>

#define MAX_ADJ_ROLLS 4
#define ROLL_SYMBOL   '@'

typedef struct
{
    int x;
    int y;
} offset;

const offset offsets[] = {{-1, -1}, {0, -1}, {1, -1}, {-1, 0}, {1, 0}, {-1, 1}, {0, 1}, {1, 1}};

int
off_range(const int tmpx, const int tmpy, const int rows, const int cols)
{
    return tmpx < 0 || tmpx > cols || tmpy < 0 || tmpy > cols;
}

int
is_valid(char matrix[][256], const int i, const int j, const int rows, const int columns)
{
    int num_adjacent_rolls = 0;

    for (int k = 0; k < sizeof(offsets) / sizeof(offsets[1]); k++) {

        int tmpx = j + offsets[k].x;
        int tmpy = i + offsets[k].y;

        if (off_range(tmpx, tmpy, k, j)) {
            continue;
        }

        printf("matrix at tmpx %d, tmpy %d: %c\n", tmpx, tmpy, matrix[tmpx][tmpy]);

        if (matrix[tmpx][tmpy] == ROLL_SYMBOL) {
            num_adjacent_rolls++;
        }
    }
    return num_adjacent_rolls < MAX_ADJ_ROLLS;
}

int
main(int argc, const char **argv)
{

    const char *filename = argv[1];
    FILE *fIn = fopen(filename, "r");
    assert(fIn != NULL);

    char matrix[256][256] = {0};
    char scanned_matrix[256][256] = {0};

    // read in the whole matrix
    int rows = 0;
    for (; rows < 256; rows++) {
        char *c = fgets(matrix[rows], sizeof(matrix[rows]) * sizeof(matrix[rows][0]), fIn);
        if (!c) {
            break;
        }
    }

    const int columns = strlen(matrix[0]) - 1; // account for newline char

    printf("size: %d cols x %d rows\n", columns, rows);

    // create new scanned_matrix and print out the whole matrix
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            scanned_matrix[i][j] = matrix[i][j];
            printf("%c", scanned_matrix[i][j]);
        }
        printf("\n");
    }

    int num_accessible = 0;
    printf("Counting num accessible\n");
    printf("size: %d cols x %d rows\n", columns, rows);
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            // printf("%c", matrix[i][j]);
            printf("scanning at i %d and j %d (%c)\n", i, j, matrix[i][j]);
            if (is_valid(matrix, i, j, rows, columns)) {
                scanned_matrix[i][j] = 'x';
                num_accessible++;
            }
        }
        printf("\n");
    }

    for (int i = 0; i < rows; i++) {
        printf("%s\n", scanned_matrix[i]);
    }

    printf("Rolls accessible: %d\n", num_accessible);

    fclose(fIn);
    return 0;
}
