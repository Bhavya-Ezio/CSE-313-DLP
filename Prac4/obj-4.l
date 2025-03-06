%option noyywrap
%{
    
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int charL_count = 0;
int charU_count = 0;
int specialChar_count = 0;
int num_count = 0;


%}

%%

[A-Z]   { charU_count++; }
[a-z]   { charL_count++; }
[0-9]   { num_count++; }
[@#$!%^&*] { specialChar_count++; }
. {}
[\n]    { 
            int total = charL_count+charU_count+specialChar_count+num_count;
            if(charL_count > 0 && charU_count > 0 && specialChar_count > 0 && num_count > 0 && total > 7)
                printf("Valid password\n");
            else
                printf("Invalid password\n");
            charL_count = 0;
            charU_count = 0;
            specialChar_count = 0;
            num_count = 0;
            printf("\n\nEnter a password: ");
        }

%%

int main()
{
    printf("Enter a password: ");
    yylex();    
    return 0;
}
