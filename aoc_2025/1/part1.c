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

    // read the file
    for (;;) {
        const char * c = fgets(buf, sizeof(buf)*sizeof(buf[0]), fIn);
        if (c == NULL) { break; }

        // first char is either 'L' or 'R'
        if (*c == 'L') {
            position += atoi(++c);
        } else {
            position -= atoi(++c);       
        }

        if (position % CLOCK_SIZE == 0) { times_passed_by_zero++; }
    }

    printf("The password is %d\n", times_passed_by_zero);

    fclose(fIn);
    return 0;
}
