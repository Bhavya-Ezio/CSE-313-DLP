%option noyywrap
%{
#include <stdio.h>
%}

%%

"/*"([^*]|\*+[^*/])*\*+"/"          {}
\'(\\.|[^"\\])*\'                   {printf("String: %s\n",yytext);}
\"(\\.|[^"\\])*\"                   {printf("String: %s\n",yytext);}
"+"|"-"|"*"|"/"|"%"|"="|"."         {printf("Operator: %s\n",yytext);}
";"|"("|")"|"{"|"}"|","             {printf("Punctuation: %s\n",yytext);}
int|char|return|struct|void|float   {printf("Keyword: %s\n",yytext);}
[a-zA-Z_][a-zA-Z0-9_]*              {printf("Identifier: %s\n",yytext);}
[0-9.]*                             {printf("Constant: %s\n",yytext);}
[0-9][a-zA-Z0-9_]*                  {printf("Error Identifier: %s\n",yytext);}
"//".*                              {}
[ \t\n]                             {}
.                                   {printf("Error: %s\n",yytext);}

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

    fclose(file);
    return 0;
}
