#include <stdio.h>

#define LEN_ARR(x) sizeof(x) / sizeof(x[0])

const char case_map[] = {['a'] = 'A', ['b'] = 'B', ['c'] = 'C', ['d'] = 'D', ['e'] = 'E'};

int
main(void)
{
    const char abc[] = "abcd";

    for (int i = 0; i < LEN_ARR(abc); i++) {
        printf("%c", case_map[abc[i]]);
    }

    printf("\n");
    return 0;
}
