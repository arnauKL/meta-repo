#include <stdio.h>
#include <stdint.h>
#include <assert.h>
#include <string.h>

int
is_valid(long long unsigned int i)
{
    /*
     * Now, an ID is invalid if it is made only of some sequence of
     * digits repeated at least twice. So, 12341234 (1234 two times),
     * 123123123 (123 three times), 1212121212 (12 five times), and
     * 1111111 (1 seven times) are all invalid IDs.
     */


    // convert the int into a string
    char num_string[100];
    snprintf(num_string, 100, "%llu", i);
    int n_digits = strlen(num_string);

    // now, check for all possible slice length combinations:
    // 111111 -> 6 times 1 (slice length (j) is 1)
    // 121212 -> 3 times 12 (slice length (j) is 2)
    for (int j = 1; j <= (n_digits / 2); j++)
    {
        if (n_digits % j != 0) { continue; }
        int repeating = 1;

        // now, strncmp slices of this string
        // 111111
        // ^  ^
        // k  k+j    (if j is 3 here)
        for (int k = 0; k + j < n_digits; k += j) {
            if (strncmp(num_string+k, num_string+k+j, j) != 0) {
                // if not repeating, check larger slices or finish
                repeating = 0;
                break;
            }
        }
        if (repeating) return 0;
    }

    return 1;
}

int
main(int argc, const char ** argv)
{
    const char * filename = argv[1];
    FILE * fIn = fopen(filename, "r");
    if(fIn == NULL) {
        perror("file");
        return 1;
    }

    long long unsigned int start = 0;
    long long unsigned int end = 0;
    long long unsigned int sum = 0;

    // get chunks of "start-end,"
    while(fscanf(fIn, "%llu-%llu,", &start, &end) == 2)
    {
        // iterate through all numbers in [start, end]
        for (long long unsigned int i = start; i <= end; i++)
        {
            if (is_valid(i) == 0) {
                //printf("%llu is invalid\n", i);
                sum += i;
            }
        }
    }

    printf("The sum is %llu\n", sum);
    // answer: The sum is 46270373595

    fclose(fIn);
    return 0;
}
