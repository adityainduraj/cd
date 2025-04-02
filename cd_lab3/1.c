#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_BUFFER 1000

bool isValidDelimiter(char ch) {
   return (ch == ' ' || ch == '+' || ch == '-' || ch == '*' ||
           ch == '/' || ch == ',' || ch == ';' || ch == '>' ||
           ch == '<' || ch == '=' || ch == '(' || ch == ')' ||
           ch == '[' || ch == ']' || ch == '{' || ch == '}');
}

bool isValidOperator(char ch) {
   return (ch == '+' || ch == '-' || ch == '*' ||
           ch == '/' || ch == '>' || ch == '<' ||
           ch == '=');
}

bool isValidIdentifier(char* str) {
   if (str[0] >= '0' && str[0] <= '9' || isValidDelimiter(str[0]))
      return false;
   return true;
}

bool isValidKeyword(char* str) {
   const char* keywords[] = {"if", "else", "while", "do", "break", "continue", "int",
                             "double", "float", "return", "char", "case", "sizeof", "long", "short", 
                             "typedef", "switch", "unsigned", "void", "static", "struct", "goto"};
   for (int i = 0; i < sizeof(keywords) / sizeof(keywords[0]); i++) {
      if (strcmp(str, keywords[i]) == 0)
         return true;
   }
   return false;
}

bool isValidInteger(char* str) {
   int len = strlen(str);
   if (len == 0) return false;
   for (int i = 0; i < len; i++) {
      if ((str[i] < '0' || str[i] > '9') || (str[i] == '-' && i > 0))
         return false;
   }
   return true;
}

bool isRealNumber(char* str) {
   int len = strlen(str);
   bool hasDecimal = false;
   if (len == 0) return false;
   for (int i = 0; i < len; i++) {
      if ((str[i] < '0' || str[i] > '9') && str[i] != '.' || (str[i] == '-' && i > 0))
         return false;
      if (str[i] == '.') hasDecimal = true;
   }
   return hasDecimal;
}

char* subString(char* str, int left, int right) {
   char* subStr = (char*)malloc(sizeof(char) * (right - left + 2));
   for (int i = left; i <= right; i++)
      subStr[i - left] = str[i];
   subStr[right - left + 1] = '\0';
   return subStr;
}

void detectTokens(char* str) {
   int left = 0, right = 0;
   int length = strlen(str);
   while (right <= length && left <= right) {
      if (!isValidDelimiter(str[right])) right++;
      if (isValidDelimiter(str[right]) && left == right) {
         if (isValidOperator(str[right]))
            printf("Valid operator : '%c'\n", str[right]);
         right++;
         left = right;
      } else if (isValidDelimiter(str[right]) && left != right || (right == length && left != right)) {
         char* subStr = subString(str, left, right - 1);
         if (isValidKeyword(subStr))
            printf("Valid keyword : '%s'\n", subStr);
         else if (isValidInteger(subStr))
            printf("Valid Integer : '%s'\n", subStr);
         else if (isRealNumber(subStr))
            printf("Real Number : '%s'\n", subStr);
         else if (isValidIdentifier(subStr) && !isValidDelimiter(str[right - 1]))
            printf("Valid Identifier : '%s'\n", subStr);
         else if (!isValidIdentifier(subStr) && !isValidDelimiter(str[right - 1]))
            printf("Invalid Identifier : '%s'\n", subStr);
         free(subStr);
         left = right;
      }
   }
}

int main() {
   FILE *file = fopen("input.c", "r");
   if (!file) {
      printf("Error: Could not open file input.c\n");
      return 1;
   }
   
   char str[MAX_BUFFER];
   fread(str, sizeof(char), MAX_BUFFER - 1, file);
   fclose(file);
   
   str[MAX_BUFFER - 1] = '\0'; // Ensure null termination
   printf("The Program is :\n%s\n", str);
   printf("All Tokens are : \n");
   detectTokens(str);
   
   return 0;
}
