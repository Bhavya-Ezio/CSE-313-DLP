#include <bits/stdc++.h>
using namespace std;

vector<pair<char, string>> grammar;
map<char, set<string>> first;
map<char, set<string>> follow;
map<char, map<char, string>> parsingTable;

void displayParsingTable();

void computeFirst(char nonTerminal)
{
    for (auto &rule : grammar)
    {
        if (rule.first == nonTerminal)
        {
            if (isupper(rule.second[0]))
            {
                computeFirst(rule.second[0]);
                first[nonTerminal].insert(first[rule.second[0]].begin(), first[rule.second[0]].end());

                if (first[rule.second[0]].count("#") > 0 && rule.second.size() > 1)
                {
                    char nextSymbol = rule.second[1];
                    if (isupper(nextSymbol))
                    {
                        computeFirst(nextSymbol);
                        first[nonTerminal].insert(first[nextSymbol].begin(), first[nextSymbol].end());
                    }
                    else
                    {
                        first[nonTerminal].insert(string(1, nextSymbol));
                    }
                }
            }
            else if (rule.second[0] == '#')
            {
                first[nonTerminal].insert("#");
            }
            else
            {
                first[nonTerminal].insert(string(1, rule.second[0]));
            }
        }
    }
}

void computeFollow(char nonTerminal)
{
    if (nonTerminal == 'S')
    {
        follow[nonTerminal].insert("$");
    }
    for (auto &rule : grammar)
    {
        size_t pos = rule.second.find(nonTerminal);
        while (pos != string::npos)
        {
            if (pos + 1 < rule.second.size())
            {
                char nextSymbol = rule.second[pos + 1];
                if (isupper(nextSymbol))
                {
                    for (auto i : first[nextSymbol])
                        if (i != "#")
                            follow[nonTerminal].insert(i);
                }
                else
                {
                    follow[nonTerminal].insert(string(1, nextSymbol));
                }
            }
            else
            {
                if (rule.first != nonTerminal)
                {
                    computeFollow(rule.first);
                    follow[nonTerminal].insert(follow[rule.first].begin(), follow[rule.first].end());
                }
            }
            pos = rule.second.find(nonTerminal, pos + 1);
        }
    }
}

bool checkLL1()
{
    set<string> allFirsts;
    for (const auto &rule : grammar)
    {
        char nonTerminal = rule.first;
        set<string> currentFirsts = first[nonTerminal];
        
        // Check for overlap with previously collected firsts
        for (const auto &firstSymbol : currentFirsts)
        {
            if (allFirsts.find(firstSymbol) != allFirsts.end())
            {
                return false; // Overlap found
            }
            allFirsts.insert(firstSymbol);
        }
    }
    for (auto i : first)
    {
        bool hasEpsilon = false;
        for (auto &j : i.second)
            if (j == "#")
                hasEpsilon = true;
        if (hasEpsilon)
        {
            char curr = i.first;
            for (auto x : follow[curr])
            {
                // if x is present in first of curr
                if (first[curr].find(x) != first[curr].end())
                    return false;
            }
        }
    }
    return true;
}

void displayParsingTable()
{
    cout << "Parsing Table:" << endl;
    for (const auto &entry : parsingTable)
    {
        char nonTerminal = entry.first;
        cout << nonTerminal << " -> ";
        for (const auto &prod : entry.second)
        {
            cout << prod.first << " : " << prod.second << ", ";
        }
        cout << endl;
    }
}

void constructParsingTable()
{
    for (auto &rule : grammar)
    {
        char nonTerminal = rule.first;
        string production = rule.second;

        set<string> firstSet;
        if (isupper(production[0]))
        {
            firstSet = first[production[0]];
        }
        else
        {
            firstSet.insert(string(1, production[0]));
        }

        for (auto &terminal : firstSet)
        {
            if (terminal != "#")
            {
                if (parsingTable[nonTerminal][terminal[0]].length() == 0)
                    parsingTable[nonTerminal][terminal[0]] = production;
            }
        }

        if (firstSet.count("#") > 0)
        {
            for (auto &terminal : follow[nonTerminal])
            {
                parsingTable[nonTerminal][terminal[0]] = production;
            }
        }
    }
    displayParsingTable();
}

bool parseString(const string &input)
{
    stack<char> parseStack;
    parseStack.push('$');
    parseStack.push('S');

    int index = 0;
    cout << "\nParsing sequence and actions\n";
    cout << "STACK\t\t\tINPUT\t\t\tACTION\n";
    cout << "------------------------------------------------------------\n";

    while (!parseStack.empty())
    {
        // Display current stack
        stack<char> tempStack = parseStack;
        string stackStr;
        while (!tempStack.empty())
        {
            stackStr = tempStack.top() + stackStr;
            tempStack.pop();
        }
        cout << stackStr << "\t\t\t";

        // Display remaining input
        string remainingInput = input.substr(index);
        cout << remainingInput << "\t\t\t";

        char top = parseStack.top();
        parseStack.pop();

        if (top == '$' && index == input.size())
        {
            cout << "Accept\n";
            return true;
        }

        if (isupper(top))
        {
            char currentInput = input[index];
            if (parsingTable[top].count(currentInput) > 0)
            {
                string production = parsingTable[top][currentInput];
                cout << "Output " << top << " -> " << production << "\n";

                for (auto it = production.rbegin(); it != production.rend(); ++it)
                {
                    if (*it != '#')
                    {
                        parseStack.push(*it);
                    }
                }
            }
            else
            {
                cout << "Error: No production found for " << top << " with input " << currentInput << "\n";
                return false;
            }
        }
        else if (top == input[index])
        {
            cout << "Match " << top << "\n";
            index++;
        }
        else
        {
            cout << "Error: Expected " << top << " but got " << input[index] << "\n";
            return false;
        }
    }
    return true;
}

int main()
{
    grammar.push_back({'S', "ABC"});
    grammar.push_back({'S', "D"});
    grammar.push_back({'A', "a"});
    grammar.push_back({'A', "#"});
    grammar.push_back({'B', "b"});
    grammar.push_back({'B', "#"});
    grammar.push_back({'C', "(S)"});
    grammar.push_back({'C', "c"});
    grammar.push_back({'D', "AC"});

    for (auto &rule : grammar)
        computeFirst(rule.first);

    for (auto &rule : grammar)
        computeFollow(rule.first);

    bool isLL1 = checkLL1();

    if (!isLL1)
    {
        cout << "Grammar is not LL(1), parsing will not work\n";
        return 0;
    }

    constructParsingTable();

    string inp;
    cout << endl
         << "Enter a string to validate: ";
    cin >> inp;

    bool isValid = parseString(inp + "$");
    cout << "\nFinal Result: String is " << (isValid ? "Valid" : "Invalid") << endl;

    return 0;
}