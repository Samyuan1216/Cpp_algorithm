#include <iostream>
using namespace std;

#include <cmath>

int Logo(string &s, int &i);

int main()
{
    string s;
    getline(cin, s);

    int i = 0;
    cout << abs(Logo(s, i)) << endl;
}

int Logo(string &s, int &i)
{
    string temp;
    int length = 0, num = 0;

    while (i < s.length() && s[i] != ']')
    {
        if (s[i] >= 'A' && s[i] <= 'Z')
        {
            temp.push_back(s[i]);
        }
        else if (s[i] >= '0' && s[i] <= '9')
        {
            num = num * 10 + s[i] - '0';
        }
        else if (s[i] == ' ' && (!temp.empty()) && num > 0)
        {
            length += (temp == "FD"? num: -num);

            num = 0;
            temp.clear();
        }
        else if (s[i] == '[')
        {
            i++;
            length += num * Logo(s, i);

            temp.clear();
            num = 0;
        }

        i++;
    }

    if ((!temp.empty()) && num > 0)
    {
        length += (temp == "FD"? num: -num);

        num = 0;
        temp.clear();
    }

    return length;
}