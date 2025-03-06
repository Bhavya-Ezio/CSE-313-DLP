%option noyywrap
%{
#include <stdio.h>
%}

%%

"charusat"  { printf("university"); }
"Charusat"  { printf("University"); }
"CHARUSAT"  { printf("UNIVERSITY"); }
.      { printf("%s",yytext);}


%%

int main() {
    printf("Enter a string: ");
    yylex();
    return 0;
}
