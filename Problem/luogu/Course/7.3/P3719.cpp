#include <iostream>
#include <string>
#include <cmath>
using namespace std;

int rexp(string &s, int l, int r);

int where = 0;
int rexp(string &s);

int main()
{
    string s;
    cin >> s;

    cout << rexp(s) << endl;
}

int rexp(string &s, int l, int r)
{
    int cnt = 0;
    for (int i = l; i <= r; i++)
    {
        if (s[i] == '(')
        {
            cnt++;
        }
        else if (s[i] == ')')
        {
            cnt--;
        }
        else if (s[i] == '|' && cnt == 0)
        {
            return max(rexp(s, l, i - 1), rexp(s, i + 1, r));
        }
    }

    if (int left = s.find('(', l); left != string::npos && left <= r)
    {
        cnt = 1;
        for (int i = left + 1; ; i++)
        {
            if (s[i] == '(')
            {
                cnt++;
            }
            else if (s[i] == ')')
            {
                cnt--;

                if (cnt == 0)
                {
                    return rexp(s, l, left - 1) + rexp(s, left + 1, i - 1) + rexp(s, i + 1, r);
                }
            }
        }
    }

    return r - l + 1;
}

int rexp(string &s)
{
    int cnt = 0;
    while (where < s.length() && s[where] != ')')
    {
        if (s[where] == 'a')
        {
            cnt++;
        }
        else if (s[where] == '(')
        {
            where++;
            cnt += rexp(s);
        }
        else if (s[where] == '|')
        {
            where++;
            cnt = max(cnt, rexp(s));
            where--;
        }

        where++;
    }

    return cnt;
}