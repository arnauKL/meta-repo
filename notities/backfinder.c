// Backfinder: find backlinks ([[a_file_name|a possible title]])
// recreate obsidian's functionality
//
// prints all the backlinks found in that file

#include <errno.h>
#include <fcntl.h> //open
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h> //open
#include <unistd.h>

#define USAGE          "Usage: backfinder <filename>"
#define PROGRAM_NAME   "backfinder"
#define FILE_EXTENSION ".md"
#define BUFFER_SIZE    4096
#define MAX_NOTES      500
#define MAX_LINKS_NOTE 10

enum State
{
    LINK_STATE,
    TEXT_STATE
};

struct note
{
    const char *name; // Name of the note
    char **links_to;  // array of files linked by this note
    int n_links;      // index to last filename
};

struct vault
{
    struct note notes[MAX_NOTES];
    int n_notes;
};

void process_file(int fildes, struct vault *v);
void print_note(struct note n);
void print_vault(struct vault *v);
struct vault *create_vault();
void free_vault(struct vault *v);

int
main(int argc, char **argv)
{
    struct vault *vault = create_vault(); // needs free_vault()

    int file_descriptor;
    if (argc != 2) {
        fprintf(stderr, "%s\n", USAGE);
        return EXIT_FAILURE;
    }

    // try to open and process the file
    if ((file_descriptor = open(argv[1], O_RDONLY)) < 0) {
        fprintf(stderr, "%s: %s: %s\n", PROGRAM_NAME, argv[1], strerror(errno));
    } else {
        process_file(file_descriptor, vault);
    }

    print_vault(vault);
    free_vault(vault);

    return EXIT_SUCCESS;
}

struct vault *
create_vault()
{
    // Mallocs but does not free
    struct vault *v = malloc(sizeof(struct vault));

    for (int i = 0; i < MAX_NOTES; i++) {
        v->notes[i].n_links = 0;
    }
    v->n_notes = 0;

    return v;
}

void
free_vault(struct vault *v)
{
    for (int i = 0; i < v->n_notes; i++) {
        for (int j = 0; j < v->notes[i].n_links; j++) {
            free(v->notes[i].links_to[j]);
        }
    }
    free(v);
}

void
process_file(int fildes, struct vault *v)
{
    unsigned char buffer[BUFFER_SIZE];
    enum State state = TEXT_STATE;
    int bytes_read = 0;
    while ((bytes_read = read(fildes, buffer, sizeof(buffer))) > 0) {

        for (int i = 0; i < bytes_read - 1; i++) {
            switch (state) {
            case LINK_STATE:
                if (buffer[i] == ']' && buffer[i + 1] == ']') {
                    i++;
                    state = TEXT_STATE;
                    printf("\n");
                } else {
                    // In here I'm just printing the characters
                    // that make up a link, but should be storing
                    // them inside of the note instead
                    printf("%c", buffer[i]);
                }
                break;
            case TEXT_STATE:
                if (buffer[i] == '[' && buffer[i + 1] == '[') {
                    state = LINK_STATE;
                    i++;
                }
                break;
            }
        }
    }
}

void
print_vault(struct vault *v)
{
    for (int i = 0; i < v->n_notes; v++) {
        print_note(v->notes[i]);
    }
}

void
print_note(struct note n)
{
    printf("note %s:\n", n.name);
    for (int i = 0; i < n.n_links; i++) {
        printf("note %s:\n", n.name);
    }
}
