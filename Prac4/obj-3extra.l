%option noyywrap
%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int word_count = 0; 
int char_count = 0;
int line_count = 1;
int whiteSpace_count = 0;
int tabSpace_count = 0;
int specialChar_count = 0;
int num_count = 0;
%}

%%

[*@#$&]    { specialChar_count++; }
[\t]+      { tabSpace_count++; }
[ ]+       { whiteSpace_count++; }
[a-zA-Z]+  { char_count+=strlen(yytext);word_count++; }
[0-9]+     { num_count++ ;}
[\n]       { line_count++; }
.          {}

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

    printf("word count = %d\n",word_count);
    printf("char count = %d\n",char_count);
    printf("line count = %d\n",line_count);
    printf("whiteSpace count = %d\n",whiteSpace_count);
    printf("specialChar count = %d\n",specialChar_count);
    printf("number count = %d\n",num_count);
    printf("TabSpace count count = %d\n",num_count);
    
    
    fclose(file);
    return 0;
}
