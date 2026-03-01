#include <iostream>
#include <string>
using namespace std;

string p(string &s, int &i);

int main()
{
    string s;
    cin >> s;

    int i = 0;
    cout << p(s, i) << endl;
}

string p(string &s, int &i)
{
    string temp;
    int cnt = 0;

    while (i < s.length() && s[i] != ']')
    {
        if (s[i] >= 'A' && s[i] <= 'Z')
        {
            temp.push_back(s[i]);
        }
        else if (s[i] == '[')
        {
            i++;
            temp.append(p(s, i));
        }
        else if (s[i] >= '0' && s[i] <= '9')
        {
            cnt = cnt * 10 + s[i] - '0';
        }

        i++;
    }

    string cpy = temp;
    for (int t = 1; t < cnt; t++)
    {
        temp += cpy;
    }

    return temp;
}