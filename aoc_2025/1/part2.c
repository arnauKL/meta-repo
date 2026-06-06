#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

#define CLOCK_SIZE 100 // goes from 0 to 99

int
main(int argc, const char ** argv)
{
    const char * filename = argv[1];
    FILE * fIn = fopen(filename, "r");
    assert(fIn != NULL);

    char buf[256] = {0};

    int position = 50; // clock starts at 50
    int times_passed_by_zero = 0;

    printf("Initial position: %d\n", position);

    // read the file
    for (;;) {
        const char * c = fgets(buf, sizeof(buf)*sizeof(buf[0]), fIn);
        if (c == NULL) { break; }
        int delta = 0;

        const char dir = *c;
        delta = atoi(++c);

        // dumb approach, go one by one and check if 0
        for (int i = 0; i < abs(delta); i++) {
            if (dir == 'L')
                position = (position - 1) % 100;
            else {
                position = (position + 1) % 100;
            }

            if (position == 0) {
                printf("0++\n");
                times_passed_by_zero++;
            }
        }

        //printf("Delta: %d, New position: %d\n", delta, position);
    }

    printf("\n\nThe password is %d\n", times_passed_by_zero);

    fclose(fIn);
    return 0;
}

