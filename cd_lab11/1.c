#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Utility functions and global variables
int tempCount = 0;  // Temporary variable counter for three-address code
int labelCount = 0; // Label counter for branching

void generateTemp(char *result) {
    sprintf(result, "t%d", tempCount++);
}

void generateLabel(char *result) {
    sprintf(result, "L%d", labelCount++);
}

// Function to generate three-address code for conditional branching
void processCondition(char *condition, char *trueLabel, char *falseLabel, char *buffer) {
    sprintf(buffer + strlen(buffer), "if %s goto %s\n", condition, trueLabel);
    sprintf(buffer + strlen(buffer), "goto %s\n", falseLabel);
}

// Function to process if-else statements
void processIfElse(char *condition, char *trueBlock, char *falseBlock, char *output) {
    char trueLabel[10], falseLabel[10], endLabel[10];
    generateLabel(trueLabel);
    generateLabel(falseLabel);
    generateLabel(endLabel);

    // Condition check
    sprintf(output + strlen(output), "if %s goto %s\n", condition, trueLabel);
    sprintf(output + strlen(output), "goto %s\n", falseLabel);

    // True block
    sprintf(output + strlen(output), "%s:\n", trueLabel);
    strcat(output, trueBlock);
    strcat(output, "\n");  // Ensure newline
    sprintf(output + strlen(output), "goto %s\n", endLabel);

    // False block
    sprintf(output + strlen(output), "%s:\n", falseLabel);
    strcat(output, falseBlock);
    strcat(output, "\n");  // Ensure newline

    // End label
    sprintf(output + strlen(output), "%s:\n", endLabel);
}

// Main function
int main() {
    char condition[50], trueBlock[100], falseBlock[100], output[500] = "";

    // Input for decision-making example
    printf("Enter a condition (e.g., x > y): ");
    fgets(condition, sizeof(condition), stdin);
    condition[strcspn(condition, "\n")] = '\0';  // Remove trailing newline

    printf("Enter a true block statement (e.g., a = b): ");
    fgets(trueBlock, sizeof(trueBlock), stdin);
    trueBlock[strcspn(trueBlock, "\n")] = '\0';  // Remove trailing newline

    printf("Enter a false block statement (e.g., c = d): ");
    fgets(falseBlock, sizeof(falseBlock), stdin);
    falseBlock[strcspn(falseBlock, "\n")] = '\0';  // Remove trailing newline

    // Generate three-address code
    processIfElse(condition, trueBlock, falseBlock, output);

    printf("Generated Three-Address Code:\n%s", output);
    return 0;
}
