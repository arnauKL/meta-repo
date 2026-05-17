// https://en.wikipedia.org/wiki/Levenshtein_distance
// The Levenshtein distance between two words is the minimum number of
// single-character edits (insertions, deletions or substitutions) required to
// change one word into the other.

// This file is the same as the recursive one but adding cache and sadly less
// pretty to look at.
// clang-format off

#include <stdio.h>
#include <string.h>

int
min(int a, int b, int c)
{
    if (a > b) a = b;
    if (a > c) a = c;
    return a;
}

int
lev(const char *s1, const char *s2)
{
    // this is so pretty
    if (*s1 == '\0') return strlen(s2);
    if (*s2 == '\0') return strlen(s1);
    if (*s1 == *s2) return lev(s1 + 1, s2 + 1);

    return 1 + min(
            lev(s1 + 1, s2),
            lev(s1, s2 + 1),
            lev(s1 + 1, s2 + 1)
            );
}

int
main(void)
{
    const char *s1 = "menorca";
    const char *s2 = "mallorca";

    int dist = lev(s1, s2);

    printf("The distance is: %d\n", dist);
    return 0;
}
