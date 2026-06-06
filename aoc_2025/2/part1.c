#include <stdio.h>
#include <stdint.h>
#include <math.h>

int
main(int argc, const char ** argv)
{
    const char * filename = argv[1];
    FILE * fIn = fopen(filename, "r");
    if(fIn == NULL) { perror("file"); }

    long long unsigned int start = 0;
    long long unsigned int end = 0;
    long long unsigned int sum = 0;

    while(fscanf(fIn, "%llu-%llu,", &start, &end) == 2)
    {
        for (long long unsigned int i = start; i <= end; i++)
        {
            /*
             *  You can find the invalid IDs by looking for any ID which is
             *  made only of some sequence of digits repeated twice. So, 55 (5
             *  twice), 6464 (64 twice), and 123123 (123 twice) would all be
             *  invalid IDs.
             */

            // for starters, their length (aka, log 10)
            int n_digits = (int)log10f(i) + 1;
            if (n_digits % 2 != 0) { continue; }

            // now, get 2 slices and compare if they're the same
            long long unsigned int left =  i / (int)pow(10, n_digits/2);
            long long unsigned int right = i % (int)pow(10, n_digits/2);

            if (left == right) {
                sum += i;
                printf("%llu-%llu (%llu) is an invalid ID; sum: %llu\n", left, right, i, sum);
            }
        }
    }

    printf("The sum is %llu\n", sum);
    // Answer: 30599400849

    fclose(fIn);
    return 0;
}
