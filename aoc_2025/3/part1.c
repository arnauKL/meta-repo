// https://adventofcode.com/2025/day/3
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>

int
main(int argc, const char ** argv)
{
    const char * filename = argv[1];
    FILE * fIn = fopen(filename, "r");
    assert(fIn != NULL);

    // each bank:
    char bank[256] = {0}; // a line of digits in the input

    // the joltage that the bank produces is equal to the
    // number formed by the digits on the batteries you've
    // turned on.
    // batteries cannot be rearranged
    // only 2 batteries can be turned on

    int sum_joltage = 0;

    // read the file
    for (;;) {
        char * c = fgets(bank, sizeof(bank)*sizeof(bank[0]), fIn);
        if (c == NULL) { break; }

        char highest[3] = {0};
        highest[2] = '\0';
        int idx_highest = 0;

        *(c + strlen(c) - 1) = '\0'; // get rid of newline

        for (int i = 0; i < strlen(c) - 1; i++)
        {
            //printf("*c (%c), highest[0] (%c)\n", *(c+i), highest[0]);
            if (*(c+i) > highest[0])
            {
                highest[0] = *(c+i);
                idx_highest = i;
            }
        }

        // idx_highest + 1 could be accessing out of buffer
        for (int j = idx_highest+1; j < strlen(c); j++)
        {
            //printf("*c (%c), highest[1] (%c)\n", *(c+j), highest[1]);
            if (*(c+j) > highest[1])
            {
                highest[1] = *(c+j);
            }
        }

        int total = atoi(highest);
        // printf("line: %s\n", bank);
        // printf("highest: %c%c\n", highest[0], highest[1]);
        // printf("total (int): %d\n", total);
        sum_joltage += total;
    }

    printf("total joltage: %d\n", sum_joltage);
    // Answer -> total joltage: 17403

    fclose(fIn);
    return 0;
}
