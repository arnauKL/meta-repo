#include <stdio.h>
#include <stdlib.h>

// It's always 5
#define WORDLEN 5

enum result
{
    CORRECT,
    INCORRECT,
    MISSPLACED,
};

enum result
process_choice(char *correct_word, char choice, int cur_idx)
{
    if (choice == correct_word[cur_idx]) {
        // Right character, right position
        return CORRECT;
    } else {
        for (int i = 0; i < WORDLEN; i++) {
            if (choice == correct_word[i]) {
                // Character in word but misplaced
                return MISSPLACED;
            }
        }
    }
    return INCORRECT;
}

int
main()
{
    char correct_word[] = "racer";

    printf("Enter %d letter word:\n", WORDLEN);
    fflush(stdout);

    while (1) {
        char choice = getchar();
        int cur_idx = 0;
        int correct = 0;

        // Get a word
        while (choice != '\n' && cur_idx <= WORDLEN) {

            enum result r = process_choice(correct_word, choice, cur_idx);

            switch (r) {
            case CORRECT:
                printf("\e[0;32m%c\e[0m", choice);
                correct++;
                break;
            case MISSPLACED:
                printf("\e[0;33m%c\e[0m", choice);
                break;
            case INCORRECT: /* cascades */
            default:
                printf("%c", choice);
                break;
            }

            // Get the next char
            choice = getchar();
            cur_idx++;
        }
        fflush(stdout);
        fflush(stdin);

        if (correct == WORDLEN) {
            printf("\nYou guessed the word!\n");
            break;
        } else {
            cur_idx = 0;
            printf("\n");
        }
    }

    return EXIT_SUCCESS;
}
