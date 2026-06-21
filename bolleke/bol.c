#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

struct StringView
{
    const char *start;
    size_t length;
};

enum TokenType
{
    TOKEN_LPAREN,    // '('
    TOKEN_RPAREN,    // ')'
    TOKEN_TEXT,      // any seq of words/punctutation
    TOKEN_KEYWORD,   // any seq of chars right after LPAREN
    TOKEN_PAR_BREAK, // Double newlines
};

struct Token
{
    struct StringView text;
    enum TokenType type;
};

int
main(int argc, char *argv[])
{
    // read from stdin, will do piping later
    if (argc != 2) {
        printf("usage: %s [filename.bol]\n", argv[0]);
        return EXIT_FAILURE;
    }

    FILE *fIn = fopen(argv[1], "r");
    if (fIn == NULL) {
        printf("Error opening %s\n", argv[1]);
        return EXIT_FAILURE;
    }

    // very provisional
    const int max_filesize = 2000;   // characters
    char raw_text[max_filesize + 1]; // null terminator

    struct Token tokens[max_filesize]; // this should be less
    int n_tokens = 0;

    // fread returns the num of items read aka the number of chars
    int n_chars = fread(raw_text, sizeof(raw_text[0]), max_filesize, fIn);
    fclose(fIn);

    raw_text[n_chars] = '\0';

    int i = 0;
    while (raw_text[i] != '\0') {

        // Skip leading spaces and single newlines
        if (raw_text[i] == ' ' || raw_text[i] == '\t' ||
            (raw_text[i] == '\n' && raw_text[i + 1] != '\n')) {
            i++;
            continue;
        }

        // Handle double newlines (Paragraph break)
        if (raw_text[i] == '\n' && raw_text[i + 1] == '\n') {
            tokens[n_tokens++] = (struct Token){.type = TOKEN_PAR_BREAK};
            i += 2; // Advance past both newlines safely
            continue;
        }

        switch (raw_text[i]) {
        case '(':
            tokens[n_tokens++] = (struct Token){.type = TOKEN_LPAREN};
            i++;

            // Catch the keyword
            const char *start = &raw_text[i];
            size_t len = 0;

            while (raw_text[i] != '\n' && raw_text[i] != ' ') {
                len++;
                i++;
            }
            tokens[n_tokens++] =
                (struct Token){.type = TOKEN_KEYWORD, .text = {.start = start, .length = len}};
            break;
        case ')':
            tokens[n_tokens++] = (struct Token){.type = TOKEN_RPAREN};
            i++;
            break;
        default: {
            // Text mode
            const char *start = &raw_text[i];
            size_t len = 0;

            // This needs to be taken into a function
            while (raw_text[i] != '(' && raw_text[i] != ')' &&     // left and
                                                                   // right parens
                                                                   // break
                   !(raw_text[i] == '\\' && raw_text[i] == '(') && // escaped
                                                                   //  left and
                                                                   //  right
                                                                   //  parens
                   !(raw_text[i] == '\\' && raw_text[i] == ')') && // same
                   !(raw_text[i] == '\n' && raw_text[i + 1] == '\n')) {
                len++;
                i++;
            }

            // clang-format off
            tokens[n_tokens++] = (struct Token){
                .type = TOKEN_TEXT,
                .text = { .start = start, .length = len }
            };
            // clang-format on
        }; break;
        }
    }

    for (int j = 0; j < n_tokens; j++) {
        switch (tokens[j].type) {
        case TOKEN_LPAREN:
            printf("LPAREN\t'('\n");
            break;
        case TOKEN_RPAREN:
            printf("RPAREN\t')'\n");
            break;
        case TOKEN_PAR_BREAK:
            printf("NEWLINE\t'\\n'\n");
            break;
        case TOKEN_KEYWORD:
            printf("KEYWORD\t'%.*s'\n", (int)tokens[j].text.length, tokens[j].text.start);
            break;
        case TOKEN_TEXT:
            printf("TEXT\t'%.*s'\n", (int)tokens[j].text.length, tokens[j].text.start);
            break;
        }
    }

    printf("keywords found:\n");
    for (int j = 0; j < n_tokens; j++) {
        if (tokens[j].type == TOKEN_KEYWORD) {
            printf("\t'%.*s'\n", (int)tokens[j].text.length, tokens[j].text.start);
        }
    }

    return EXIT_SUCCESS;
}
