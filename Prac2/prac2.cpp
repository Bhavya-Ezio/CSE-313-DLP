#include <iostream>
#include <unordered_map>
#include <vector>
#include <algorithm>
using namespace std;

int main()
{
    int inSymbol, state;
    char currState, finalState;
    cout << "Enter the number of Input Symbols: ";
    cin >> inSymbol;
    vector<char> symbols(inSymbol);
    cout << "Enter the Symbols: ";
    for (char &symbol : symbols)
        cin >> symbol;

    cout << "Enter the number of States: ";
    cin >> state;
    vector<char> states(state);
    cout << "Enter the States: ";
    for (char &stateChar : states)
        cin >> stateChar;

    cout << "Enter the Initial State: ";
    cin >> currState;
    int numFinalStates;
    cout << "Enter the number of Final States: ";
    cin >> numFinalStates;
    vector<char> finalStates(numFinalStates);
    cout << "Enter the Final States: ";
    for (char &finalStateChar : finalStates)
        cin >> finalStateChar;

    unordered_map<string, char> table;
    for (const char &stateChar : states)
    {
        for (const char &symbol : symbols)
        {
            char nextState;
            cout << stateChar << " -> " << symbol << " ";
            cin >> nextState;
            table[string(1, stateChar) + symbol] = nextState;
        }
    }

    string inpString;
    cout << "Enter input String: ";
    cin >> inpString;

    for (char inputChar : inpString)
        currState = table[string(1, currState) + inputChar];

    cout << (find(finalStates.begin(), finalStates.end(), currState) != finalStates.end() ? "String is Valid" : "String is Invalid");
    return 0;
}