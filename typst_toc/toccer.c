/*
 * Read a file.
 * Parse its headings (lines starting with one or more '= ')
 *
 * Store each line with its level:
 *      = My first heading -> struct {level: 1, content: "My first heading\0"}
 *
 * Once the whole file has been read, print out the stored headers.
 * Neovim expects:
 * filename:line:col:message
 *
 * No LLM use
 */

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUF_SIZE  256
#define LINE_LEN  80
#define MAX_DEPTH 6 // max depth in typst is 6 (aka, six '=')

/*
 * Heading struct:
 * contains
 *  - null-terminated string (truncated it's too long)
 *  - depth (number of '='s, 0-indexed)
 *  - line (line number of the heading)
 */
typedef struct
{
    char data[LINE_LEN];
    int depth;
    int line;
} Heading;

/*
 * Headings struct: list of headings
 * contains:
 * - list of `Heading`
 * - count: number of headings in the array at any time
 * - capacity: space allocated (in num of Headings)
 */
typedef struct
{
    Heading **items;
    int count;
    size_t capacity;
    int start_section;   // user config: starting heading num
    int max_depth_limit; // user config: max depth shown
} Headings;

/*
 * macro to add headings, reallocs if needed
 */
#define heading_append(hs, h)                                                                      \
    do {                                                                                           \
        if (hs.count >= hs.capacity) {                                                             \
            if (hs.count == 0) {                                                                   \
                hs.capacity = 256;                                                                 \
            } else {                                                                               \
                hs.capacity *= 2;                                                                  \
            }                                                                                      \
            hs.items = realloc(hs.items, hs.capacity * sizeof(hs.items[0]));                       \
            if (hs.items == NULL) {                                                                \
                fprintf(stderr, "Error reallocating memory\n");                                    \
                return 1;                                                                          \
            }                                                                                      \
        }                                                                                          \
        hs.items[hs.count++] = h;                                                                  \
    } while (0)

/*
 * *hs: ptr to list of headings
 * *filename: argv[1], normally; so nvim knows where headings come from
 */
void
print_headings_numbering(Headings *hs, const char *filename)
{
    int n[MAX_DEPTH] = {0};                                    /*store numbering*/
    n[0] = hs->start_section != 0 ? hs->start_section - 1 : 0; // configure initial section
    int last_depth = 0;

    for (int i = 0; i < hs->count; i++) {

        int depth = hs->items[i]->depth;
        if (depth > hs->max_depth_limit - 1) {
            continue;
        }
        if (last_depth > depth) {
            for (int j = depth + 1; j < MAX_DEPTH; j++) n[j] = 0;
        }

        last_depth = depth;
        n[hs->items[i]->depth]++;

        printf("%s:", filename);
        printf("%d:1:", hs->items[i]->line);
        for (int d = 0; d <= hs->items[i]->depth; d++) {
            printf("%d.", n[d]);
        }
        printf(" %s", hs->items[i]->data);
        printf("\n");
    }
}

/*
 * cstr: c-string containing the heading text (null terminated)
 * dpth: depth of the heading (number of '=', 0-indexed)
 */
Heading *
create_heading(const char *cstr, int dpth)
{
    Heading *h = malloc(sizeof(Heading));
    if (h == NULL) {
        fprintf(stderr, "Error allocating memory\n");
        return NULL;
    }
    strncpy(h->data, cstr, LINE_LEN);
    h->data[LINE_LEN - 1] = '\0';
    // cap depth to MAX_DEPTH
    h->depth = dpth >= MAX_DEPTH ? MAX_DEPTH - 1 : dpth;
    return h;
}

/*
 * h: pointer to Heading
 * s: current character in the buffer
 */
Heading *
absorb_to_newline(char *s)
{
    int depth = 0;
    // Add padding to avoid storing the space after '='
    char *start = s + 2;

    do {
        s++;
        if (*s == '=') {
            depth++;
            // Do not store '='s
            start++;
        }
    } while (*s != '\n' && *s != '\0');

    // s points to a newline (or null), replace with null
    *s = '\0';
    return create_heading(start, depth);
}

int
main(int argc, const char **argv)
{
    FILE *fIn = NULL;

    // Manage cli args
    if (argc == 2) {
        // we got a filename via cli
        fIn = fopen(argv[1], "r");
    } else {
        // wrong cli args
        printf("usage: %s <filename.typ>\n", argv[0]);
        return EXIT_FAILURE;
    }

    // file reading errors
    if (fIn == NULL) {
        fprintf(stderr, "Error opening %s\n", argv[1]);
        return EXIT_FAILURE;
    }

    // create array of headings
    Headings hs = {0};
    hs.max_depth_limit = MAX_DEPTH;
    hs.start_section = 0;

    char buf[BUF_SIZE];
    int line = 0;

    // read from the file
    for (;;) {
        // fgets stops at EOF and newlines and stores newlines in the buffer
        char *s = fgets(buf, sizeof(buf), fIn);
        line++;

        if (s == NULL) {
            // no more characters to read
            break;
        }

        // Check for settings comments
        if (strncmp(buf, "// toc-start: ", 14) == 0) {
            int tmp = atoi(buf + 14);
            int clamped = (tmp < 1) ? 0 : tmp;
            hs.start_section = clamped;
            continue; // Skip processing this as a heading
        }
        if (strncmp(buf, "// toc-depth: ", 14) == 0) {
            int tmp = atoi(buf + 14);
            int clamped = (tmp > MAX_DEPTH - 1) || (tmp < 0) ? MAX_DEPTH : tmp;
            hs.max_depth_limit = clamped;
            continue;
        }
        // look at the first char to see if it's a heading
        do {
            if (*s == '=') {
                Heading *h = absorb_to_newline(s);
                h->line = line;
                heading_append(hs, h);
            }
        } while (isspace(*s++));
    }
    fclose(fIn);

    print_headings_numbering(&hs, argv[1]);

    return EXIT_SUCCESS;
}
