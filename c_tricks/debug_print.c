// The preprocessor can print variable NAMES:

#include <stdio.h>

#define DEBUG_PRINT(x, y) printf("%s (%d) + %s (%d) = %d", #x, x, #y, y, (x) + (y))

int
main()
{

    int first = 100;
    int second = 200;

    DEBUG_PRINT(first, second);

    return 0;
}
