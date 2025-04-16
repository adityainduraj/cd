
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

// Global variables for input, position tracking, and error handling
const char *input;
int row = 1, column = 1;

// Error function to handle errors
void error(const char *message) {
    printf("Error at row %d, column %d: %s\n", row, column, message);
    exit(1);
}

// Function prototypes
void program();
void declarations();
void identifier_list();
void statement_list();
void statement();
void assign_stat();
void decision_stat();
void looping_stat();
void expn();
void simple_expn();
void eprime();
void seprime();
void term();
void tprime();
void factor();
void dprime();
void match(char expected);
void match_string(const char *expected);
int is_relop();
int is_addop();
int is_mulop();
void skip_whitespace();

// Skip whitespace characters (space, tab, newline)
void skip_whitespace() {
    while (*input == ' ' || *input == '\t' || *input == '\n') {
        if (*input == '\n') {
            row++;
            column = 1;
        } else {
            column++;
        }
        input++;
    }
}

// Utility function to match and consume expected characters
void match(char expected) {
    skip_whitespace();
    if (*input == expected) {
        if (expected == '\n') {
            row++;
            column = 1;
        } else {
            column++;
        }
        input++;
    } else {
        char errMsg[50];
        sprintf(errMsg, "Expected '%c', found '%c'", expected, *input);
        error(errMsg);
    }
}

// Utility function to match and consume expected strings
void match_string(const char *expected) {
    skip_whitespace();
    int len = strlen(expected);
    if (strncmp(input, expected, len) == 0) {
        input += len;
        column += len;
    } else {
        char errMsg[100];
        char found[20] = {0};
        strncpy(found, input, len > 19 ? 19 : len);
        sprintf(errMsg, "Expected '%s', found '%s'", expected, found);
        error(errMsg);
    }
}

// Check for relational operators
int is_relop() {
    if (*input == '=' && *(input + 1) == '=') return 1;
    if (*input == '!' && *(input + 1) == '=') return 1;
    if (*input == '>' && *(input + 1) == '=') return 1;
    if (*input == '<' && *(input + 1) == '=') return 1;
    if (*input == '>' || *input == '<') return 1;
    return 0;
}

// Check for additive operators
int is_addop() {
    return (*input == '+' || *input == '-');
}

// Check for multiplicative operators
int is_mulop() {
    return (*input == '*' || *input == '/' || *input == '%');
}

// Recursive Descent Parser functions

void program() {
    match_string("main");
    skip_whitespace();
    match('(');
    skip_whitespace();
    match(')');
    skip_whitespace();
    match('{');
    declarations();
    statement_list();
    match('}');
    
    skip_whitespace();
    if (*input == '\0') {
        printf("Parsing successful!\n");
    } else {
        error("Unexpected input after program");
    }
}

void declarations() {
    skip_whitespace();
    if (strncmp(input, "int", 3) == 0 || strncmp(input, "char", 4) == 0) {
        // Consume data type
        if (strncmp(input, "int", 3) == 0) {
            input += 3;
            column += 3;
        } else {
            input += 4;
            column += 4;
        }
        
        skip_whitespace();
        identifier_list();
        match(';');
        declarations();
    }
    // Empty declaration is valid (epsilon)
}

void identifier_list() {
    skip_whitespace();
    if (isalpha(*input) || *input == '_') {
        // Parse identifier
        while (isalnum(*input) || *input == '_') {
            input++;
            column++;
        }
        
        skip_whitespace();
        // Handle array declaration
        if (*input == '[') {
            match('[');
            skip_whitespace();
            
            // Parse number
            if (isdigit(*input)) {
                while (isdigit(*input)) {
                    input++;
                    column++;
                }
            } else {
                error("Expected array size (number)");
            }
            
            skip_whitespace();
            match(']');
        }
        
        skip_whitespace();
        // Handle multiple declarations
        if (*input == ',') {
            match(',');
            identifier_list();
        }
    } else {
        error("Expected identifier");
    }
}

void statement_list() {
    skip_whitespace();
    // Check if there's a statement (starting with identifier, `if`, `while`, or `for`)
    if (isalpha(*input) || *input == '_' || strncmp(input, "if", 2) == 0 || strncmp(input, "while", 5) == 0 || strncmp(input, "for", 3) == 0) {
        statement();
        statement_list();
    }
    // Empty statement list is valid (epsilon)
}

void statement() {
    skip_whitespace();
    if (strncmp(input, "if", 2) == 0) {
        decision_stat();
    } else if (strncmp(input, "while", 5) == 0 || strncmp(input, "for", 3) == 0) {
        looping_stat();
    } else {
        assign_stat();
        match(';');
    }
}

void assign_stat() {
    skip_whitespace();
    if (isalpha(*input) || *input == '_') {
        // Parse identifier
        while (isalnum(*input) || *input == '_') {
            input++;
            column++;
        }
        
        skip_whitespace();
        // Handle array access
        if (*input == '[') {
            match('[');
            expn();
            match(']');
        }
        
        skip_whitespace();
        match('=');
        expn();
    } else {
        error("Expected identifier in assignment");
    }
}

void decision_stat() {
    skip_whitespace();
    match_string("if");
    skip_whitespace();
    match('(');
    expn();
    match(')');
    skip_whitespace();
    match('{');
    statement_list();
    match('}');
    dprime();
}

void dprime() {
    skip_whitespace();
    if (strncmp(input, "else", 4) == 0) {
        match_string("else");
        skip_whitespace();
        match('{');
        statement_list();
        match('}');
    }
    // epsilon (no 'else') is valid
}

void looping_stat() {
    skip_whitespace();
    if (strncmp(input, "while", 5) == 0) {
        // Parse "while(expn){statement-list}"
        match_string("while");
        skip_whitespace();
        match('(');
        expn();
        match(')');
        skip_whitespace();
        match('{');
        statement_list();
        match('}');
    } else if (strncmp(input, "for", 3) == 0) {
        // Parse "for(assign-stat; expn; assign-stat){statement-list}"
        match_string("for");
        skip_whitespace();
        match('(');
        assign_stat();
        match(';');
        expn();
        match(';');
        assign_stat();
        match(')');
        skip_whitespace();
        match('{');
        statement_list();
        match('}');
    } else {
        error("Expected 'while' or 'for' for looping statement");
    }
}

void expn() {
    skip_whitespace();
    simple_expn();
    eprime();
}

void eprime() {
    skip_whitespace();
    if (is_relop()) {
        // Handle relational operators
        if (*input == '=' && *(input + 1) == '=') {
            input += 2;
            column += 2;
        } else if (*input == '!' && *(input + 1) == '=') {
            input += 2;
            column += 2;
        } else if (*input == '>' && *(input + 1) == '=') {
            input += 2;
            column += 2;
        } else if (*input == '<' && *(input + 1) == '=') {
            input += 2;
            column += 2;
        } else if (*input == '>' || *input == '<') {
            input++;
            column++;
        }
        
        simple_expn();
    }
    // Empty eprime is valid (epsilon)
}

void simple_expn() {
    skip_whitespace();
    term();
    seprime();
}

void seprime() {
    skip_whitespace();
    if (is_addop()) {
        // Handle additive operators
        char op = *input;
        input++;
        column++;
        
        term();
        seprime();
    }
    // Empty seprime is valid (epsilon)
}

void term() {
    skip_whitespace();
    factor();
    tprime();
}

void tprime() {
    skip_whitespace();
    if (is_mulop()) {
        // Handle multiplicative operators
        char op = *input;
        input++;
        column++;
        
        factor();
        tprime();
    }
    // Empty tprime is valid (epsilon)
}

void factor() {
    skip_whitespace();
    
    if (isalpha(*input) || *input == '_') {
        // Parse identifier
        while (isalnum(*input) || *input == '_') {
            input++;
            column++;
        }
        
        // Handle array access
        skip_whitespace();
        if (*input == '[') {
            match('[');
            expn();
            match(']');
        }
    } else if (isdigit(*input)) {
        // Parse number
        while (isdigit(*input)) {
            input++;
            column++;
        }
    } else if (*input == '(') {
        // Handle parenthesized expressions
        match('(');
        expn();
        match(')');
    } else {
        error("Expected identifier, number, or parenthesized expression");
    }
}

int main() {
    // Sample input for testing
    input = "main() {\n"
            "  int i, sum;\n"
            "  sum = 0;\n"
            "  for (i = 0; i < 10; i = i + 1) {\n"
            "    sum = sum + i;\n"
            "  }\n"
            "  while (sum > 50) {\n"
            "    sum = sum - 10;\n"
            "  }\n"
            "}";
    
    program();
    return 0;
}