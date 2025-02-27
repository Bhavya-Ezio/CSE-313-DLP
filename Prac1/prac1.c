/*Code for checking string of REGEX: a*bb */
#include <stdio.h>
#include <string.h>
void main()
{
    printf("Enter a string: ");
    char str[10];
    scanf("%s", &str);

    int n = strlen(str) - 1;
    if (n >= 1 && (str[n] == 'b' && str[n - 1] == 'b'))
    {
        int isValid = 1;
        for (int i = 0; i < n - 1; i++)
        {
            if (str[i] != 'a')
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