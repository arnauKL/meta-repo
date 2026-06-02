/*
 * Read a file.
 * Parse its headings (lines starting with one or more '= ')
 *
 * Store each line with its level:
 *      = My first heading -> struct {level: 1, content: "My first heading\0"}
 *
 *
 * Once the whole file has been read, print out the stored headers.
 *      it could be nice to print them with numbers as if a real TOC.
 *      and even further this could also print line numbers so vim could go
 *      there?
 *
 *
 * No LLM use
 *
 */

// clang-format on
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include <unistd.h> // idk if I need this, it provides STDIN_FILENO but:
// Note that mixing use of FILEs and raw file
// descriptors can produce unexpected results 
// and  should  generally  be avoided.

#define BUF_SIZE 256
#define LINE_LEN 80
#define MAX_DEPTH 5 // max depth in typst is 5 (aka, six '=')

/*
 * Heading struct:
 * contains 80-char null-terminated string (truncated if it gets longer)
 * future updates could add the heading number/depth
 */
typedef struct {
    char data[LINE_LEN];
    int depth;
    int line;
} Heading;

typedef struct {
    Heading ** items; // array of headings
    int count; // how many items it has
    size_t capacity; // how much memory it has allocated
} Headings;

struct HeadingList {
    char* elems; // a list of `struct Heading`s
    size_t count; // the ammount of these `struct Heading`s
    size_t capacity;
};

#define heading_append(hs, h)\
    do {\
        if (hs.count >= hs.capacity) {\
            if (hs.count == 0) { hs.capacity = 256; }\
            else { hs.capacity *= 2; }\
            hs.items = realloc(hs.items, hs.capacity*sizeof(hs.items[0]));\
            if (hs.items == NULL) {\
                fprintf(stderr, "Error reallocating memory\n");\
                return EXIT_FAILURE;\
            }\
        }\
        hs.items[hs.count++] = h;\
    } while (0)\

void print_headings_numbering(Headings *hs) {
    int n[MAX_DEPTH+1] = {0}; /*store numbering*/
    int last_depth = 0;
    for (int i = 0; i < hs->count; i++)
    {
        int depth = hs->items[i]->depth;

        if (last_depth > depth) {
            for (int j = depth + 1; j < MAX_DEPTH; j++)
                n[j] = 0;
        }

        last_depth = depth;
        depth++;
        n[hs->items[i]->depth]++;

        printf("%3d|", hs->items[i]->line);
        for (int d = 0; d <= hs->items[i]->depth; d++) {
            printf("%d.", n[d]);
        }
        printf(" %s", hs->items[i]->data);
        //printf("\t|%d:0|", hs->items[i]->line);
        printf("\n");
    }
}

Heading *
create_heading(const char* cstr, int dpth)
{
    Heading * h = malloc(sizeof(Heading));
    if (h == NULL) {
        fprintf(stderr, "Error allocating memory\n");
        return NULL;
    }
    strncpy(h->data, cstr, LINE_LEN);
    // cap depth to MAX_DEPTH
    h->depth = dpth > MAX_DEPTH ? MAX_DEPTH : dpth;
    return h;
}

/*
 * h: pointer to Heading
 * s: current character in the buffer
 */
Heading * absorb_to_newline(char *s){
    int depth = 0;
    // Add padding to avoid storing the space after '='
    char* start = s + 2;

    do {
        s++;
        if (*s == '=') {
            depth++;
            // Do not store '='s
            start++;
        }
    } while (*s != '\n');

    // s points to a newline, replace with null
    *s = '\0';
    return create_heading(start, depth);
}

int main(int argc, const char ** argv)
{
    FILE *fIn = NULL;

    // Manage cli args
    if (argc == 2) {
        // we got a filename via cli
        fIn = fopen(argv[1], "r");
    } else if (argc == 1) {
        // we read from stdin
        fIn = stdin;
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

    char buf[BUF_SIZE];
    int line = 0;

    // read from the file
    for (;;){
        // fgets stops at EOF and newlines and stores newlines in the buffer
        char *s = fgets(buf, sizeof(buf), fIn);
        line++;

        if (s == NULL) {
            // no more characters to read
            break;
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

    print_headings_numbering(&hs);

    return EXIT_SUCCESS;
}
