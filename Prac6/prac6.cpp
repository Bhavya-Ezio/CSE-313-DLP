#include <bits/stdc++.h>
using namespace std;
void S();
void L();
void L1();

char l;

void match(char c)
{
    if (l == c)
        l = getchar();
    else
    {
        cout << "\nInvalid String\n";
        exit(0);
    }
}

void L1()
{
    if (l == ',')
    {
        match(',');
        S();
        L1();
    }
    else
    {
        return;
    }
}

void S()
{
    if (l == '(')
    {
        match('(');
        L();
        match(')');
    }
    else if (l == 'a')
    {
        match('a');
    }
    else
    {
        cout << "\nInvalid String\n";
        exit(0);
    }
}

void L()
{
    S();
    L1();
}

int main()
{
    string input;
    cout << "Enter String with $ at the end\n";
    l = getchar();
    S();
    if (l == '$')
    {
        cout << "\nValid String\n";
    }
    else
    {
        cout << "\nInvalid String\n";
    }
    return 0;
}