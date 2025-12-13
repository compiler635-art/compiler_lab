#include <stdio.h>
#include <ctype.h>
#include <string.h>

int isKeyword(char str[]) {
    char keywords[6][10] = {"int", "float", "if", "else", "while", "return"};
    for (int i = 0; i < 6; i++) {
        if (strcmp(str, keywords[i]) == 0)
            return 1;
    }
    return 0;
}

int main() {
    char input[200];
    char token[50];
    int i = 0, j = 0;
    int token_count = 0;

    printf("Enter an input string:\n");
    fgets(input, sizeof(input), stdin);

    printf("\nToken\t\tLexeme\n");
    printf("---------------------------\n");

    while (input[i] != '\0') {

        if (isspace(input[i])) {
            i++;
            continue;
        }

        if (strchr("+-*/=<>", input[i])) {
            printf("Operator\t%c\n", input[i]);
            token_count++;
            i++;
            continue;
        }

        if (isalpha(input[i]) || input[i] == '_') {
            j = 0;
            while (isalnum(input[i]) || input[i] == '_')
                token[j++] = input[i++];
            token[j] = '\0';

            if (isKeyword(token))
                printf("Keyword\t\t%s\n", token);
            else
                printf("Identifier\t%s\n", token);

            token_count++;
            continue;
        }

        if (isdigit(input[i])) {
            j = 0;
            while (isdigit(input[i]))
                token[j++] = input[i++];
            token[j] = '\0';

            printf("Number\t\t%s\n", token);
            token_count++;
            continue;
        }

        i++;
    }

    printf("\nTotal number of tokens = %d\n", token_count);
    return 0;
}
