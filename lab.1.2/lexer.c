#include <stdio.h>
#include <ctype.h>
#include <string.h>
 
// Simple replacements for regex-based matching used in original code.
// We use direct string/character checks instead to avoid POSIX regex dependency.
 
int main(){
    FILE *f = fopen("input.c", "r");
    if (f == NULL) {
        printf("Error: Could not open input.c\n");
        return 1;
    }
    
    char c, t[100];
    int i, line = 1, n = 1;
    printf("Line\tNo.\tType\tLexeme\n");
    
    while((c = fgetc(f)) != EOF){
        if(isspace(c)){
            if(c == '\n') line++;
            continue;
        }
        
        i = 0;
        t[i++] = c;
        
        if(isalnum(c) || c == '_'){
            while((c = fgetc(f)) != EOF && (isalnum(c) || c == '_'))
                t[i++] = c;
            t[i] = 0;
            if(c != EOF) ungetc(c, f);

            if(strcmp(t, "int") == 0 || strcmp(t, "void") == 0 || strcmp(t, "if") == 0 ||
               strcmp(t, "else") == 0 || strcmp(t, "do") == 0 || strcmp(t, "while") == 0)
            {
                printf("%d\t%d\tKW\t%s\n", line, n++, t);
            }
            else if(isalpha((unsigned char)t[0]) || t[0] == '_'){
                printf("%d\t%d\tID\t%s\n", line, n++, t);
            }
            else {
                int allDigits = 1;
                for(int j = 0; t[j] != '\0'; ++j){
                    if(!isdigit((unsigned char)t[j])){ allDigits = 0; break; }
                }
                if(allDigits)
                    printf("%d\t%d\tNUM\t%s\n", line, n++, t);
                else
                    printf("%d\t%d\tOTHER\t%s\n", line, n++, t);
            }
        }
        else {
            t[i] = 0;
            if(strchr("+-*/=<>&|%", t[0]) != NULL)
                printf("%d\t%d\tOP\t%s\n", line, n++, t);
            else
                printf("%d\t%d\tOTHER\t%s\n", line, n++, t);
        }
    }
    
    fclose(f);
    return 0;
}
//run using gcc lexer.c -o lexer
//then ./lexer