#include <stdint.h>
#include <stdio.h>

#define N_CELLS             30000
#define INSTRUCTIONS_LENGTH 30000

int
main(int argc, char **argv)
{
    if (argc != 2) {
        printf("usage: %s [filename.bf]", argv[0]);
        return 1;
    }

    char instructions[INSTRUCTIONS_LENGTH] = {0};
    FILE *fIn = fopen(argv[1], "r");

    if (fIn == NULL) {
        printf("Error opening %s\n", argv[1]);
        return -1;
    }

    fread(instructions, sizeof(instructions[0]), sizeof(instructions) - 1, fIn);

    // 0-255 only => uint8_t
    uint8_t cells[N_CELLS] = {0};
    uint8_t *ptr = cells;
    int ip = 0; // instruction pointer

    printf("BF output: ");
    fflush(stdout);
    while (instructions[ip] != '\0') {
        switch (instructions[ip]) {
        case '>':
            ptr++;
            break;
        case '<':
            ptr--;
            break;
        case '+':
            (*ptr)++;
            break;
        case '-':
            (*ptr)--;
            break;
        case '.':
            putchar(*ptr);
            fflush(stdout);
            break;
        case ',':
            *ptr = (uint8_t)getchar();
            break;
        case '[':
            if (*ptr == 0) {
                int depth = 1;
                while (depth > 0) {
                    ip++;
                    if (instructions[ip] == '[') {
                        depth++;
                    } else if (instructions[ip] == ']') {
                        depth--;
                    }
                }
            }
            break;
        case ']':
            if (*ptr != 0) {
                int depth = 1;
                while (depth > 0) {
                    ip--;
                    if (instructions[ip] == '[') {
                        depth--;
                    } else if (instructions[ip] == ']') {
                        depth++;
                    }
                }
            }
            break;
        default:
            // anything else is a comment
            break;
        }
        ip++;
    }

    printf("\n");
    return 0;
}
