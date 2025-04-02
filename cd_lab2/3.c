#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_LINE_LENGTH 1024

// List of all C keywords
const char *keywords[] = {
    "auto", "break", "case", "char", "const", "continue", "default", "do",
    "double", "else", "enum", "extern", "float", "for", "goto", "if",
    "inline", "int", "long", "register", "restrict", "return", "short",
    "signed", "sizeof", "static", "struct", "switch", "typedef", "union",
    "unsigned", "void", "volatile", "while", "_Bool", "_Complex", "_Imaginary"
};

#define NUM_KEYWORDS (sizeof(keywords) / sizeof(keywords[0]))

// Function to check if a word is a C keyword
int is_keyword(const char *word) {
    for (int i = 0; i < NUM_KEYWORDS; i++) {
        if (strcmp(word, keywords[i]) == 0) {
            return 1; // It's a keyword
        }
    }
    return 0; // Not a keyword
}

// Function to convert a string to uppercase
void to_uppercase(char *word) {
    for (int i = 0; word[i] != '\0'; i++) {
        word[i] = toupper(word[i]);
    }
}

int main() {
    FILE *inputFile;
    char filename[100];
    char line[MAX_LINE_LENGTH];
    char word[MAX_LINE_LENGTH];

    // Get the input file name from the user
    printf("Enter the name of the C program file: ");
    scanf("%s", filename);

    // Open the input file
    inputFile = fopen(filename, "r");
    if (inputFile == NULL) {
        printf("Could not open file %s\n", filename);
        return 1;
    }

    printf("Keywords in uppercase:\n");

    // Read the file line by line
    while (fgets(line, MAX_LINE_LENGTH, inputFile) != NULL) {
        // Tokenize the line into words
        char *token = strtok(line, " \t\n(){}[];,<>=+-*/&|!");
        while (token != NULL) {
            // Check if the word is a keyword
            if (is_keyword(token)) {
                strcpy(word, token); // Copy the keyword to a new variable
                to_uppercase(word); // Convert it to uppercase
                printf("%s\n", word); // Print the keyword in uppercase
            }
            token = strtok(NULL, " \t\n(){}[];,<>=+-*/&|!");
        }
    }

    // Close the file
    fclose(inputFile);

    return 0;
}
