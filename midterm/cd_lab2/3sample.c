#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_LINE_LENGTH 1024

const char *keywords[] = {
    "auto", "break", "case", "char", "const", "continue", "default", "do",
    "double", "else", "enum", "extern", "float", "for", "goto", "if",
    "inline", "int", "long", "register", "restrict", "return", "short",
    "signed", "sizeof", "static", "struct", "switch", "typedef", "union",
    "unsigned", "void", "volatile", "while", "_Bool", "_Complex", "_Imaginary"
};

#define NUM_KEYWORDS (sizeof(keywords) / sizeof(keywords[0]))

int is_keyword(const char *word) {
    for (int i = 0; i < NUM_KEYWORDS; i++) {
        if (strcmp(word, keywords[i]) == 0) {
            return 1;
        }
    }
    return 0;
}

void to_uppercase(char *word) {
    while (*word) {
        *word = toupper(*word);
        word++;
    }
}

int main() {
    char filename[100], word[MAX_LINE_LENGTH];
    FILE *file;

    printf("Enter filename: ");
    scanf("%s", filename);

    if ((file = fopen(filename, "r")) == NULL) {
        printf("Error opening file %s\n", filename);
        return 1;
    }

    printf("Keywords in uppercase:\n");

    while (fscanf(file, "%1023s", word) == 1) {
        if (is_keyword(word)) {
            to_uppercase(word);
            printf("%s\n", word);
        }
    }

    fclose(file);
    return 0;
}
