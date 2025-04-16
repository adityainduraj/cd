
#include <stdio.h>
#include <stdlib.h>

#define MAX_LINE_LENGTH 1024

int main() {
    FILE *file1, *file2, *outputFile;
    char file1Name[100], file2Name[100], outputFileName[100];
    char line[MAX_LINE_LENGTH];
    int turn = 1; // Variable to alternate between files

    // Get file names from the user
    printf("Enter the name of the first file: ");
    scanf("%s", file1Name);
    printf("Enter the name of the second file: ");
    scanf("%s", file2Name);
    printf("Enter the name of the output file: ");
    scanf("%s", outputFileName);

    // Open the files
    file1 = fopen(file1Name, "r");
    file2 = fopen(file2Name, "r");
    outputFile = fopen(outputFileName, "w");

    // Check if files are opened successfully
    if (file1 == NULL || file2 == NULL || outputFile == NULL) {
        printf("Error opening one or more files.\n");
        return 1;
    }

    // Merge lines alternatively
    while (1) {
        if (turn == 1 && fgets(line, MAX_LINE_LENGTH, file1) != NULL) {
            fputs(line, outputFile); // Write line from file1 to output
        } else if (turn == 2 && fgets(line, MAX_LINE_LENGTH, file2) != NULL) {
            fputs(line, outputFile); // Write line from file2 to output
        } else {
            break; // Break when lines from both files are exhausted
        }
        turn = (turn == 1) ? 2 : 1; // Switch between file1 and file2
    }

    // Write any remaining lines from file1
    while (fgets(line, MAX_LINE_LENGTH, file1) != NULL) {
        fputs(line, outputFile);
    }

    // Write any remaining lines from file2
    while (fgets(line, MAX_LINE_LENGTH, file2) != NULL) {
        fputs(line, outputFile);
    }

    // Close all files
    fclose(file1);
    fclose(file2);
    fclose(outputFile);

    printf("Lines merged successfully into %s\n", outputFileName);

    return 0;
}
