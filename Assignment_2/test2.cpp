#include <iostream>
#include <bits/stdc++.h>
using namespace std;

#define PI pair<int, pair<int, string>>
#define PS pair<string, pair<string, char>>

vector<char> OPERATORS;
vector<PI> transition_matrix;
vector<int> states;
vector<int> start_states;
vector<int> final_states;
vector<string> alphabets;
int state_count = 1;

void fill()
{
    OPERATORS.push_back('+');
    OPERATORS.push_back('.');
    OPERATORS.push_back('*');
    states.push_back(0);
    states.push_back(1);
    start_states.push_back(0);
    final_states.push_back(1);
}

bool check(char c, vector<char> v)
{
    for (int i = 0; i < v.size(); i++)
    {
        if (v[i] == c)
        {
            return true;
        }
    }
    return false;
}

bool compare(char c2, char ch)
{
    int a, b;
    for (int i = 0; i < OPERATORS.size(); i++)
    {
        if (OPERATORS[i] == c2)
        {
            a = i;
            break;
        }
    }
    for (int i = 0; i < OPERATORS.size(); i++)
    {
        if (OPERATORS[i] == ch)
        {
            b = i;
            break;
        }
    }

    if (b > a)
    {
        return true;
    }
    return false;
}

string infix_to_postfix(string exp)
{
    vector<char> opening_brackets;
    opening_brackets.push_back('(');
    opening_brackets.push_back('[');
    opening_brackets.push_back('{');

    vector<char> closing_brackets;
    closing_brackets.push_back(')');
    closing_brackets.push_back(']');
    closing_brackets.push_back('}');

    for (int i = 0; i < exp.size() - 1; i++)
    {
        if ((isalnum(exp[i]) || exp[i] == '*' || check(exp[i], closing_brackets)) && (isalnum(exp[i + 1]) || check(exp[i + 1], opening_brackets)))
        {
            string z = ".";
            exp.insert(i + 1, z);
        }
    }

    string shunt;
    stack<char> stack;

    for (int i = 0; i < exp.size(); i++)
    {
        char ch;
        ch = exp[i];

        if (std::find(OPERATORS.begin(), OPERATORS.end(), ch) != OPERATORS.end())
        {
            while (!stack.empty())
            {
                char c2 = stack.top();
                if (check(c2, opening_brackets) || compare(c2, ch))
                {
                    break;
                }
                else
                {
                    stack.pop();
                    shunt += c2;
                }
            }
            stack.push(ch);
        }
        else if (check(ch, opening_brackets))
        {
            stack.push(ch);
        }
        else if (check(ch, closing_brackets))
        {
            while (!stack.empty() && !check(stack.top(), opening_brackets))
            {
                ch = stack.top();
                stack.pop();
                shunt += ch;
            }
            if (check(stack.top(), opening_brackets))
            {
                stack.pop();
            }
        }
        else
        {
            shunt += ch;
        }
    }

    while (!stack.empty())
    {
        char ch = stack.top();
        stack.pop();
        shunt += ch;
    }
    return shunt;
}

PS split(string postfix)
{
    int flag = 0;
    char last_ch = postfix[postfix.size() - 1];

    if (last_ch == '.' || last_ch == '+')
    {
        flag = 1;
    }

    int i = postfix.size() - 1;
    while (flag != 0)
    {
        i -= 1;
        if (i == -1)
        {
            if (postfix[postfix.size() - 1] == '.' || postfix[postfix.size() - 1] == '+')
            {
                flag += 1;
            }
        }
        else if (postfix[i] == '.' || postfix[i] == '+')
        {
            flag += 1;
        }
        else if (isalnum(postfix[i]))
        {
            flag -= 1;
        }
    }

    PS p;
    p.second.second = postfix[postfix.size() - 1];
    postfix.erase(postfix.size()-1);
    p.first = postfix.substr(0, i);
    p.second.first = postfix.substr(i, postfix.size());

    return p;
}

int main()
{
    string exp;
    cin >> exp;
    fill();
    PS ret = split(exp);
    cout << ret.first;
}