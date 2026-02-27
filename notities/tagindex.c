// tag_indexer: Print a list of tags and all the files that have them:
// for example:

// #todo:
//     filename1.md
//     filename2.md
// #uni:
//     another_file_but_with_uni_tag.md
//     filename3.md
//     filename4.md
//     filename5.md

// Could implement saving to a file
// or some way to interact with fzf
// for example:
//     tagindex -l | fzf
//     # only show distinct tags
//     tagindex -t <tag>
//     # only show filenames matching that tag
//     # (tag could be read from stdin?)
//     # or:
//     tagindex -t $(tagindex -l | fzf)

#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int
main(int argc, char **argv)
{
    int fildes;
    // Should really be using getopt in the future if I'll be adding flags
    // And file reading should be in a loop for all the files?
    if (argc > 2) {
        fprintf(stderr, "%s\n", "too many arguments");
        return EXIT_FAILURE;
    } else if (argc == 1) {
        // No args: read from stdin
        fildes = STDIN_FILENO;
    } else {
        // No
        if ((fildes = open(argv[1], O_RDONLY)) < 0) {
            fprintf(stderr, "%s: %s\n", argv[1], strerror(errno));
            return EXIT_FAILURE;
        }
    }

    printf("Hello world!\n");

    return EXIT_SUCCESS;
}
