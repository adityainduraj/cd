#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 1024

int main() {
    FILE *inputFile, *outputFile;
    char inputFilename[100], outputFilename[100];
    char line[MAX_LINE_LENGTH];

    // Get the input and output file names from the user
    printf("Enter the name of the input C file: ");
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

    // Process the input file line by line
    while (fgets(line, MAX_LINE_LENGTH, inputFile) != NULL) {
        // Check if the line starts with '#'
        if (line[0] != '#') {
            fputs(line, outputFile); // Write the line to the output file
        }
    }

    // Close the files
    fclose(inputFile);
    fclose(outputFile);

    printf("Preprocessor directives removed successfully.\n");
    return 0;
}
