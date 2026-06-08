// https://adventofcode.com/2025/day/3#part2
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>

#define NUM_BATTERIES 12

int
main(int argc, const char ** argv)
{
    const char * filename = argv[1];
    FILE * fIn = fopen(filename, "r");
    assert(fIn != NULL);

    // each bank:
    char bank[256] = {0}; // a line of digits in the input

    // now, we need to find the max joltage with 12 batteries per bank

    uint64_t sum_joltage = 0;

    // read the file
    for (;;) {
        char * c = fgets(bank, sizeof(bank)*sizeof(bank[0]), fIn);
        if (c == NULL) { break; }


        char highest[NUM_BATTERIES+1] = {0};
        highest[NUM_BATTERIES] = '\0';
        int idx_highest = 0;

        *(c + strlen(c) - 1) = '\0'; // get rid of newline

        printf("line: %s\n", bank);
        printf("strlen: %zu\n", strlen(c));

        // ith_battery keeps track of which battery we're finding
        for (int ith_battery = 0; ith_battery < NUM_BATTERIES; ith_battery++) {
            int limit = strlen(c) - (NUM_BATTERIES - ith_battery) + 1;
            for (int i = idx_highest; i < limit; i++)
            {
                //printf("*c (%c), highest[%d] (%c)\n", *(c+i), ith_battery, highest[ith_battery]);
                if (*(c+i) > highest[ith_battery])
                {
                    highest[ith_battery] = *(c+i);
                    *(c+i) = '0';
                    idx_highest = i;
                }
            }
        }

        uint64_t total = atoll(highest);
        printf("total (uint64): %lu\n", total);
        sum_joltage += total;
    }

    printf("total joltage: %lu\n", sum_joltage);
    // answer -> total joltage: 173416889848394

    fclose(fIn);
    return 0;
}
