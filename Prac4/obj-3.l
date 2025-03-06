%option noyywrap
%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int word_count = 0; 
int char_count = 0;
int line_count = 1;
%}

%%

.          { char_count++; }
[a-zA-Z]+  { char_count+=strlen(yytext);word_count++; }
\n         { line_count++; }

%%

int main(int argc, char **argv)
{
    FILE *file = fopen("input.txt", "r");
    if (!file)
    {
        printf("could not open the file\n");
        exit(1);
    }
    yyin = file;
    yylex();

    printf("Characters = %d\nWords = %d\nLines = %d\n", char_count, word_count, line_count);
    fclose(file);
    return 0;
}
