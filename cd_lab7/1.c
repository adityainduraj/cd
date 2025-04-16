#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct {
    char tokens[256][256];
    int pos;
    int row;
    int col;
} Parser;

void error(Parser *parser, const char *expected) {
    printf("Expected %s at line %d, column %d, but found '%s'\n", expected, parser->row, parser->col, parser->tokens[parser->pos]);
    exit(1);
}

void eat(Parser *parser, const char *token_type) {
    if (strcmp(parser->tokens[parser->pos], token_type) == 0) {
        parser->pos++;
        parser->col++;
    } else {
        error(parser, token_type);
    }
}

void skip_whitespace(const char *code, int *pos) {
    while (isspace(code[*pos])) {
        (*pos)++;
    }
}

void tokenize(const char *code, Parser *parser) {
    int pos = 0;
    int token_index = 0;
    while (code[pos] != '\0') {
        skip_whitespace(code, &pos);
        if (strncmp(&code[pos], "main()", 6) == 0) {
            strcpy(parser->tokens[token_index++], "main()");
            pos += 6;
        } else if (isalpha(code[pos])) {
            int start = pos;
            while (isalpha(code[pos])) {
                pos++;
            }
            strncpy(parser->tokens[token_index], &code[start], pos - start);
            parser->tokens[token_index++][pos - start] = '\0';
        } else if (isdigit(code[pos])) {
            int start = pos;
            while (isdigit(code[pos])) {
                pos++;
            }
            strncpy(parser->tokens[token_index], &code[start], pos - start);
            parser->tokens[token_index++][pos - start] = '\0';
        } else {
            parser->tokens[token_index][0] = code[pos];
            parser->tokens[token_index++][1] = '\0';
            pos++;
        }
        skip_whitespace(code, &pos);
    }
    parser->tokens[token_index][0] = '\0';  // End of tokens
}

void program(Parser *parser);
void declarations(Parser *parser);
void data_type(Parser *parser);
void identifier_list(Parser *parser);
void assign_stat(Parser *parser);

void program(Parser *parser) {
    eat(parser, "main()");
    eat(parser, "{");
    declarations(parser);
    assign_stat(parser);
    eat(parser, "}");
}

void declarations(Parser *parser) {
    while (strcmp(parser->tokens[parser->pos], "int") == 0 || strcmp(parser->tokens[parser->pos], "char") == 0) {
        data_type(parser);
        identifier_list(parser);
        eat(parser, ";");
    }
}

void data_type(Parser *parser) {
    if (strcmp(parser->tokens[parser->pos], "int") == 0 || strcmp(parser->tokens[parser->pos], "char") == 0) {
        eat(parser, parser->tokens[parser->pos]);
    } else {
        error(parser, "data-type");
    }
}

void identifier_list(Parser *parser) {
    eat(parser, "id");
    while (strcmp(parser->tokens[parser->pos], ",") == 0) {
        eat(parser, ",");
        eat(parser, "id");
    }
}

void assign_stat(Parser *parser) {
    if (strcmp(parser->tokens[parser->pos], "id") == 0) {
        eat(parser, "id");
        eat(parser, "=");
        if (strcmp(parser->tokens[parser->pos], "id") == 0 || strcmp(parser->tokens[parser->pos], "num") == 0) {
            eat(parser, parser->tokens[parser->pos]);
            eat(parser, ";");
        } else {
            error(parser, "id or num");
        }
    } else {
        error(parser, "id");
    }
}

int main() {
    char code[256];
    printf("Enter the code: ");
    fgets(code, sizeof(code), stdin);
    code[strcspn(code, "\n")] = 0;  // Remove newline character

    Parser parser;
    parser.pos =0;
    parser.row = 0;
    parser.col = 0;
    tokenize(code, &parser);
    program(&parser);

    printf("Parsing successful\n");
    return 0;
}
//input: main(){ int id; id=num; }
// output: Parsing Successful
