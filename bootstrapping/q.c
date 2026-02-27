// clang-format off
#include <stdio.h>
#include <string.h>

int main() {

    char buf[256];
    const char* self = "// clang-format off\n#include <stdio.h>\n#include <string.h>\n\nint main() {\n\n    char buf[256];\n    const char* self = \"?\";\n\n    for (;;) {\n        char* s = fgets(buf, sizeof(buf), stdin);\n\n        if (s == NULL) { return 0; }\n\n        while (*s) {\n            if (*s == 'q') {\n                // When the 'q' function is called in the source code\n                int n = strlen(self);\n                for (int i = 0; i < n; i++) {\n                    if (self[i] == 63) { // use ascii instead of char itself\n                        // On the special character, print whole source code\n                        // And escape special characters\n                        for (int j = 0; j < n; j++) {\n                            switch (self[j]) {\n                                case '\\n': printf(\"\\\\n\");  break;\n                                case '\"':  printf(\"\\\\\\\"\"); break;\n                                case '\\\\': printf(\"\\\\\\\\\"); break;\n                                default:   printf(\"%c\", self[j]);\n                            }\n                        }\n                    }\n                    else {\n                        // Otherwise print current char\n                        printf(\"%c\", self[i]);\n                    }\n                }\n            }\n            s++;\n        }\n    }\n    return 0;\n}\n";

    for (;;) {
        char* s = fgets(buf, sizeof(buf), stdin);

        if (s == NULL) { return 0; }

        while (*s) {
            if (*s == 'q') {
                // When the 'q' function is called in the source code
                int n = strlen(self);
                for (int i = 0; i < n; i++) {
                    if (self[i] == 63) { // use ascii instead of char itself
                        // On the special character, print whole source code
                        // And escape special characters
                        for (int j = 0; j < n; j++) {
                            switch (self[j]) {
                                case '\n': printf("\\n");  break;
                                case '"':  printf("\\\""); break;
                                case '\\': printf("\\\\"); break;
                                default:   printf("%c", self[j]);
                            }
                        }
                    }
                    else {
                        // Otherwise print current char
                        printf("%c", self[i]);
                    }
                }
            }
            s++;
        }
    }
    return 0;
}
