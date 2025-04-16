#include <stdio.h>
#include <stdlib.h>

int main() {
    FILE *inputFile, *outputFile;
    char inputFilename[100], outputFilename[100];
    long fileSize;
    char *buffer;

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

    // Find the size of the input file
    fseek(inputFile, 0, SEEK_END);  // Move to the end of the file
    fileSize = ftell(inputFile);   // Get the current file pointer position
    rewind(inputFile);             // Move back to the beginning of the file

    // Allocate memory to hold the file contents
    buffer = (char *)malloc(fileSize * sizeof(char));
    if (buffer == NULL) {
        printf("Memory allocation failed.\n");
        fclose(inputFile);
        return 1;
    }

    // Read the file contents into the buffer
    fread(buffer, sizeof(char), fileSize, inputFile);

    // Open the output file in write mode
    outputFile = fopen(outputFilename, "w");
    if (outputFile == NULL) {
        printf("Could not open file %s\n", outputFilename);
        free(buffer);
        fclose(inputFile);
        return 1;
    }

    // Write the contents of the buffer in reverse order to the output file
    for (long i = fileSize - 1; i >= 0; i--) {
        fputc(buffer[i], outputFile);
    }

    // Close the files and free the allocated memory
    fclose(inputFile);
    fclose(outputFile);
    free(buffer);

    // Display the size of the original file
    printf("The size of the file '%s' is: %ld bytes\n", inputFilename, fileSize);

    return 0;
}
    