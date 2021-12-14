#include <iostream>
#include <bits/stdc++.h>
using namespace std;

void step1(int n, int k, int a, set<int> &s1, set<int> &s2, vector<int> v)
{
    for (int i = 0; i < n; i++)
    {
        if (std::find(v.begin(), v.end(), i) != v.end())
        {
            s1.insert(i);
        }
        else
        {
            s2.insert(i);
        }
    }
}

int dimag_kharab_bc(int s, vector<set<int>> &v)
{
    for (int i = 0; i < v.size(); i++)
    {
        set<int> x = v[i];
        if (x.count(s))
        {
            return i;
        }
    }
    return -1;
}

int kya_hai_ye_yaar(int s1, int s2, vector<set<int>> &p, vector<pair<int, pair<char, int>>> &tf, set<char> &ls)
{
    for (auto l : ls)
    {
        int i1 = -1;
        int i2 = -1;

        for (int i = 0; i < tf.size(); i++)
        {
            pair<int, pair<char, int>> p1 = tf[i];

            if (p1.first == s1 && p1.second.first == l)
            {
                i1 = dimag_kharab_bc(p1.second.second, p);
            }
            if (p1.first == s2 && p1.second.first == l)
            {
                i2 = dimag_kharab_bc(p1.second.second, p);
            }
        }
        if (i1 != i2)
        {
            return 0;
        }
    }
    return 1;
}

vector<pair<int, pair<char, int>>> v;

int search_x(int a, int b)
{
    for (int i = 0; i < v.size(); i++)
    {
        if (v[i].first == a and v[i].second.first == b)
            return v[i].second.second;
    }
}

int main(int argc, char **argv)
{
    string input_file = argv[1];
    string output_file = argv[2];

    int n, k, a;
    // cin >> n >> k >> a;
    set<int> s1, s2;
    set<char> letters;
    vector<int> accept_states;

    std::ifstream file;
    file.open(input_file);
    file >> n >> k >> a;
    for (int i = 0; i < a; i++)
    {
        int x;
        file >> x;
        accept_states.push_back(x);
    }
    for (int i = 0; i < k; i++)
    {
        int a, b;
        char c;
        file >> a >> c >> b;
        pair<int, pair<char, int>> p;
        p.first = a;
        p.second.first = c;
        p.second.second = b;
        v.push_back(p);
        letters.insert(c);
    }
    file.close();

    step1(n, k, a, s1, s2, accept_states);
    vector<set<int>> blem;
    blem.push_back(s1);
    blem.push_back(s2);

    int f = 0;

    while (!f)
    {
        f = 1;
        vector<set<int>> newv;
        for (int i = 0; i < blem.size(); i++)
        {
            set<int> x = blem[i];

            for (auto s : x)
            {
                if (dimag_kharab_bc(s, newv) == -1)
                {
                    set<int> new_s;
                    new_s.insert(s);

                    for (auto s2 : x)
                    {
                        if (dimag_kharab_bc(s2, newv) == -1)
                        {
                            if (kya_hai_ye_yaar(s, s2, blem, v, letters))
                            {
                                new_s.insert(s2);
                            }
                        }
                    }
                    newv.push_back(new_s);
                }
            }
        }

        for (int i = 0; i < newv.size(); i++)
        {
            set<int> x = newv[i];
            if (!(std::find(blem.begin(), blem.end(), x) != blem.end()))
            {
                f = 0;
            }
        }
        blem = newv;
    }

    vector<int> grp_no(n);
    set<int> accept_states2;
    int transition_matrix_count = 0, accept_state_count = 0;
    for (int i = 0; i < blem.size(); i++)
    {
        bool check = false;
        set<int> y = blem[i];
        int j = 0;
        for (auto a : y)
        {
            for (int xx = 0; xx < accept_states.size(); xx++)
            {
                if (accept_states[xx] == a)
                    check = true;
            }
            grp_no[a] = i;
            transition_matrix_count++;
        }
        if (check == true)
        {
            accept_state_count++;
            accept_states2.insert(i);
        }
    }

    int count = 0;
    std::ofstream file2;
    file2.open(output_file);
    set<char>::iterator it2;
    for (int i = 0; i < blem.size(); i++)
    {
        for (it2 = letters.begin(); it2 != letters.end(); it2++)
        {
            // file2 << i << " " << char(*it) << " " << grp_no[search_x(i, *it)] << "\n";
            count++;
        }
    }
    file2 << blem.size() << " " << count << " " << accept_state_count << '\n';
    set<char>::iterator it;
    for (int i = 0; i < accept_state_count; i++)
    {
        file2 << i << ' ';
    }
    file2 << endl;
    for (int i = 0; i < blem.size(); i++)
    {
        for (it = letters.begin(); it != letters.end(); it++)
        {
            file2 << i << " " << char(*it) << " " << grp_no[search_x(i, *it)] << "\n";
        }
    }
    file2.close();

    return 0;
}
