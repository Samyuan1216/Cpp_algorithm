#include <bits/stdc++.h>
using namespace std;

using vc = vector<char>;
using vi = vector<int>;

const int MAXN = 11000010;
vc ss(MAXN << 1);
vi p(MAXN << 1);
string s;
int n;

void manacherss()
{
    n = s.length() * 2 + 1;
    for (int i = 0, j = 0; i < n; i++)
    {
        ss[i] = ((i & 1)? s[j++]: '#');
    }
}

int manacher()
{
    manacherss();

    int maxn = 0;
    for (int i = 0, r = 0, c = 0, len; i < n; i++)
    {
        len = (i < r? min(p[2 * c - i], r - i): 1);
        while (i + len < n && i - len >= 0 && ss[i + len] == ss[i - len])
        {
            len++;
        }

        if (i + len > r)
        {
            r = i + len;
            c = i;
        }

        maxn = max(maxn, len);
        p[i] = len;
    }

    return maxn - 1;
}

int main()
{
    cin >> s;
    cout << manacher() << endl;
}