#include <math.h>
#include <stdio.h>

int
palindrome(int x)
{
    if (x < 0)
        return 0;

    int size = log10(x) + 1;
    int exp = size + 1;

    for (int i = 1; i < size / 2 + 1; i += 1) {

        exp -= 2;
        int tmp = (int)(pow(10, exp));

        int last = x % 10;
        int first = x / tmp;

        if (first != last)
            return 0;

        // Cut the first and last digit
        x = (x % tmp) / 10;

        if (x == 0)
            return 1;
    }
    return 1;
}

int
main()
{
    int x = 1000021;

    printf("%d is %sa palindrome\n", x, palindrome(x) ? "" : "not ");
    return 0;
}
