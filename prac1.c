#include <stdio.h>
#include <string.h>
void main()
{
    printf("Enter a string: ");
    char str[10];
    scanf("%s", &str);

    if (strlen(str) < 2)
        printf("Invalid");

    else if (strlen(str) == 2){
        if (str[0] == 'b' && str[1] == 'b')
            printf("Valid");
        else
            printf("Invalid");
    }else{
        int n = strlen(str) - 1;
        int isValid = 1;
        if (str[n] == 'b' && str[n - 1] == 'b')
        {
            for (int i = 0; i < n - 1; i++)
            {
                if (str[i] == 'a')
                    continue;
                else
                {
                    isValid = 0;
                    break;
                }
            }
            if (isValid == 1)
                printf("Valid");
            else
                printf("Invalid");
        }
        else
        {
            printf("Invalid");
        }
    }
}