#include <iostream>
#include <bits/stdc++.h>
#include <fstream>
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

bool check_splitted()
{
    for (int i = 0; i < transition_matrix.size(); i++)
    {
        if (transition_matrix[i].second.second.size() != 1)
        {
            return false;
        }
    }
    return true;
}

int main(int argc, char** argv)
{
    string input_file = argv[1];
    string output_file = argv[2];

    string exp;

    std::ifstream file;
    file.open(input_file);
    file >> exp;
    file.close();

    // cout << exp;

    fill();

    string postfix = infix_to_postfix(exp);
    PI pi;
    pi.first = 0;
    pi.second.first = 1;
    pi.second.second = postfix;
    transition_matrix.push_back(pi);

    //cout << "/////////////" << endl;

    while (!check_splitted())
    {
        vector<PI> temp_matrix(transition_matrix.size());
        copy(transition_matrix.begin(), transition_matrix.end(), temp_matrix.begin());
        // cout << "xxxxxxxxxx" << endl;

        for (int i = 0; i < temp_matrix.size(); i++)
        {
            // cout << "i: " << i << endl;
            if (temp_matrix[i].second.second.size() > 1)
            {
                // std::cout << "temp_matrix[i].second.second.size(): " << temp_matrix[i].second.second.size()<<endl;
                PS ret = split(temp_matrix[i].second.second);

                PI temp = temp_matrix[i];

                vector<PI>::iterator it;
                it = transition_matrix.begin() + i;
                transition_matrix.erase(it);

                if (ret.second.second == '+')
                {
                    PI p;
                    p.first = temp.first;
                    p.second.first = temp.second.first;
                    p.second.second = ret.first;
                    transition_matrix.push_back(p);

                    p.second.second = ret.second.first;
                    transition_matrix.push_back(p);
                }

                if (ret.second.second == '.')
                {
                    state_count += 1;
                    states.push_back(state_count);

                    PI p;
                    p.first = temp.first;
                    p.second.first = state_count;
                    p.second.second = ret.first;
                    transition_matrix.push_back(p);

                    p.first = state_count;
                    p.second.first = temp.second.first;
                    p.second.second = ret.second.first;
                    transition_matrix.push_back(p);
                }
                if (ret.second.second == '*')
                {
                    state_count += 1;
                    states.push_back(state_count);
                    state_count += 1;
                    states.push_back(state_count);

                    PI p;

                    p.first = temp.first;
                    p.second.first = state_count - 1;
                    p.second.second = "E";
                    transition_matrix.push_back(p);

                    p.first = state_count;
                    p.second.first = temp.second.first;
                    p.second.second = "E";
                    transition_matrix.push_back(p);

                    p.first = state_count - 1;
                    p.second.first = state_count;
                    p.second.second = ret.first;
                    transition_matrix.push_back(p);

                    p.first = state_count;
                    p.second.first = state_count - 1;
                    p.second.second = "E";
                    transition_matrix.push_back(p);

                    p.first = temp.first;
                    p.second.first = temp.second.first;
                    p.second.second = "E";
                    transition_matrix.push_back(p);
                }
            }
        }
    }

    int n = states.size();
    int k = transition_matrix.size();
    int a = final_states.size();

    std::ofstream file2;
    file2.open(output_file);
    
    file2 << n << " " << k << " " << a << endl;
    for (int i = 0; i < a; i++)
    {
        file2 << final_states[i] << " ";
    }
    file2 << endl;
    for (int i = 0; i < transition_matrix.size(); i++)
    {
        PI x = transition_matrix[i];
        file2 << x.first << " " << x.second.second << " " << x.second.first << endl;
    }
    file2.close();

    return 0;
}