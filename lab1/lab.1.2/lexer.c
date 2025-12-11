#include <stdio.h>
#include <ctype.h>
#include <regex.h>
 
int match(const char *p, const char *s){
    regex_t r;
    int ret = regcomp(&r, p, REG_EXTENDED);
    
    if (ret != 0) {
        return 0;
    }
    
    int ok = !regexec(&r, s, 0, NULL, 0);
    regfree(&r);
    return ok;
}
 
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
            
            if(match("^(int|void|if|else|do|while)$", t))
                printf("%d\t%d\tKW\t%s\n", line, n++, t);
            else if(match("^[A-Za-z_][A-Za-z0-9_]*$", t))
                printf("%d\t%d\tID\t%s\n", line, n++, t);
            else if(match("^[0-9]+$", t))
                printf("%d\t%d\tNUM\t%s\n", line, n++, t);
        }
        else {
            t[i] = 0;
            if(match("^[+\\-*/=<>&|%]$", t))
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