%option noyywrap
%{
#include <stdio.h>
%}

%%

[0-9]+  { printf("%s\n", yytext); }
.      { printf("");}


%%

int main() {
    printf("Enter a string: ");
    yylex();
    return 0;
}
