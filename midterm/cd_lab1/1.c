#include <stdio.h>

int main() {
    FILE *file;
    char filename[100];
    char ch;
    int lines = 0, characters = 0;

    // Get the file name from the user
    printf("Enter the filename: ");
    scanf("%s", filename);

    // Open the file in read mode
    file = fopen(filename, "r");

    // Check if the file exists
    if (file == NULL) {
        printf("Could not open file %s\n", filename);
        return 1;
    }

    // Read the file character by character
    while ((ch = fgetc(file)) != EOF) {
        characters++; // Increment character count

        // Check for a newline character
        if (ch == '\n') {
            lines++;
        }
    }

    // Add 1 to the line count if the file is not empty
    if (characters > 0 && ch != '\n') {
        lines++;
    }

    // Close the file
    fclose(file);

    // Print the results
    printf("Number of lines: %d\n", lines);
    printf("Number of characters: %d\n", characters);

    return 0;
}
