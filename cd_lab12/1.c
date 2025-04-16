#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100

// Stack structure for evaluation
typedef struct {
    char items[MAX][MAX];
    int top;
} Stack;

// Initialize the stack
void initStack(Stack *s) {
    s->top = -1;
}

// Push an item onto the stack
void push(Stack *s, char *item) {
    if (s->top == MAX - 1) {
        printf("Stack Overflow\n");
        exit(1);
    }
    strcpy(s->items[++(s->top)], item);
}

// Pop an item from the stack
char *pop(Stack *s) {
    if (s->top == -1) {
        printf("Stack Underflow\n");
        exit(1);
    }
    return s->items[(s->top)--];
}

// Function to check if a character is an operator
int isOperator(char op) {
    return op == '+' || op == '-' || op == '*' || op == '/' || op == '^';
}

// Function to generate assembly code from postfix expression
void generateAssembly(char postfix[]) {
    Stack stack;
    initStack(&stack);

    int tempVarCount = 0;
    char assembly[MAX][MAX];  // Store generated assembly instructions
    int asmIndex = 0;

    char *token = strtok(postfix, " ");
    while (token != NULL) {
        if (isOperator(token[0]) && strlen(token) == 1) {
            // Operator: Pop two operands from the stack
            char operand2[MAX], operand1[MAX], tempVar[MAX];
            strcpy(operand2, pop(&stack));
            strcpy(operand1, pop(&stack));

            // Create a temporary variable for the result
            sprintf(tempVar, "TEMP%d", tempVarCount++);

            // Generate assembly code for the operator
            if (token[0] == '+') {
                sprintf(assembly[asmIndex++], "LOAD %s", operand1);
                sprintf(assembly[asmIndex++], "ADD %s", operand2);
                sprintf(assembly[asmIndex++], "STORE %s", tempVar);
            } else if (token[0] == '-') {
                sprintf(assembly[asmIndex++], "LOAD %s", operand1);
                sprintf(assembly[asmIndex++], "SUB %s", operand2);
                sprintf(assembly[asmIndex++], "STORE %s", tempVar);
            } else if (token[0] == '*') {
                sprintf(assembly[asmIndex++], "LOAD %s", operand1);
                sprintf(assembly[asmIndex++], "MUL %s", operand2);
                sprintf(assembly[asmIndex++], "STORE %s", tempVar);
            } else if (token[0] == '/') {
                sprintf(assembly[asmIndex++], "LOAD %s", operand1);
                sprintf(assembly[asmIndex++], "DIV %s", operand2);
                sprintf(assembly[asmIndex++], "STORE %s", tempVar);
            } else if (token[0] == '^') {
                sprintf(assembly[asmIndex++], "LOAD %s", operand1);
                sprintf(assembly[asmIndex++], "EXP %s", operand2);
                sprintf(assembly[asmIndex++], "STORE %s", tempVar);
            }

            // Push the result onto the stack
            push(&stack, tempVar);
        } else {
            // Operand: Push onto the stack
            push(&stack, token);
        }

        // Move to the next token
        token = strtok(NULL, " ");
    }

    // Print the generated assembly code
    printf("Generated Assembly Code:\n");
    for (int i = 0; i < asmIndex; i++) {
        printf("%s\n", assembly[i]);
    }
}

int main() {
    char postfix[MAX];

    // Input: Postfix expression
    printf("Enter a postfix expression (e.g., '3 4 + 5 *'):\n");
    fgets(postfix, MAX, stdin);
    postfix[strcspn(postfix, "\n")] = '\0';  // Remove trailing newline

    // Generate assembly code
    generateAssembly(postfix);

    return 0;
}