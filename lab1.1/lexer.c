#include <stdio.h>
#include <ctype.h>
#include <string.h>
 
int main() {
    FILE *input;
    int line = 1;
    int token_no = 1;
 
    input = fopen("input.c", "r");
    if (!input) {
        printf("Error opening file\n");
        return 1;
    }
 
    char ch, ch1;
    char str[50];
    int i;
 
    char keyword[10][20] = {"int", "void", "if", "else", "do", "while"};
 
    printf("Line no.\tToken no.\tToken\t\tLexeme\n");
 
    while ((ch = fgetc(input)) != EOF) {
 
 
        if (ch == '/') {
            ch1 = fgetc(input);
 
            if (ch1 == '/') {
                while ((ch = fgetc(input)) != '\n' && ch != EOF);
                line++;
                continue;
            }
 
            else if (ch1 == '*') {
                char prev = 0;
                while ((ch = fgetc(input)) != EOF) {
                    if (ch == '\n')
                        line++;
                    if (prev == '*' && ch == '/')
                        break;
                    prev = ch;
                }
                continue;
            }
 
            else {
                ungetc(ch1, input);
            }
        }
 
 
        if (ch=='+' || ch=='-' || ch=='*' || ch=='/' || ch=='>' ||
            ch=='<' || ch=='=' || ch=='%' || ch=='&' || ch=='|') {
 
            printf("%7d\t%10d\tOperator\t%7c\n", line, token_no++, ch);
            continue;
        }
 
 
        if (isalpha(ch) || ch == '_') {
            i = 0;
            str[i++] = ch;
 
            while ((ch = fgetc(input)) != EOF && (isalnum(ch) || ch == '_'))
                str[i++] = ch;
 
            str[i] = '\0';
            ungetc(ch, input);
 
            int flag = 0;
            for (int k = 0; k < 6; k++) {
                if (strcmp(str, keyword[k]) == 0) {
                    flag = 1;
                    break;
                }
            }
 
            if (flag)
                printf("%7d\t%10d\tKeyword\t\t%s\n", line, token_no++, str);
            else
                printf("%7d\t%10d\tIdentifier\t%s\n", line, token_no++, str);
 
            continue;
        }
 
 
        if (isdigit(ch)) {
            i = 0;
            str[i++] = ch;
 
            while ((ch = fgetc(input)) != EOF && isdigit(ch))
                str[i++] = ch;
 
            str[i] = '\0';
            ungetc(ch, input);
 
            printf("%7d\t%10d\tNumber\t\t%s\n", line, token_no++, str);
            continue;
        }
 
 
        if (ch == '\n')
            line++;
 
    }
 
    fclose(input);
    return 0;
}
//run using gcc lexer.c -o lexer
//then ./lexer