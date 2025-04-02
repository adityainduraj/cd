#include <stdio.h>
#include <stdlib.h>

#define MAX_FILENAME 100

int main() {
    FILE *inputFile, *outputFile;
    char inputFilename[MAX_FILENAME], outputFilename[MAX_FILENAME];
    char ch, prevChar = '\0';

    // Get the input and output file names from the user
    printf("Enter the name of the input file: ");
    scanf("%s", inputFilename);
    printf("Enter the name of the output file: ");
    scanf("%s", outputFilename);

    // Open the input file in read mode
    inputFile = fopen(inputFilename, "r");
    if (inputFile == NULL) {
        printf("Could not open file %s\n", inputFilename);
        return 1;
    }

    // Open the output file in write mode
    outputFile = fopen(outputFilename, "w");
    if (outputFile == NULL) {
        printf("Could not open file %s\n", outputFilename);
        fclose(inputFile);
        return 1;
    }

    // Process the input file character by character
    while ((ch = fgetc(inputFile)) != EOF) {
        // Replace tabs or multiple spaces with a single space
        if (ch == ' ' || ch == '\t') {
            if (prevChar != ' ') { // Only write a space if the previous character is not a space
                fputc(' ', outputFile);
            }
        } else {
            fputc(ch, outputFile); // Write the non-space character to the output file
        }
        prevChar = ch; // Update the previous character
    }

    // Close the files
    fclose(inputFile);
    fclose(outputFile);

    printf("Blank spaces and tabs replaced by single spaces successfully.\n");
    return 0;
}
