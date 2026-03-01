#include <bits/stdc++.h>
using namespace std;

using vi = vector<int>;
using vc = vector<char>;

const int MAXN = 100010;
vi p(MAXN << 1), l(MAXN << 1), r(MAXN << 1);
vc ss(MAXN << 1);
string s;
int n, ans;

void manacherss()
{
    n = s.length() * 2 + 1;
    for (int i = 0, j = 0; i < n; i++)
    {
        ss[i] = (i & 1? s[j++]: '#');
    }
}

void manacher()
{
    manacherss();
    for (int i = 0, c = 0, r = 0, len; i < n; i++)
    {
        len = (i < r? min(r - i, p[2 * c - i]): 1);
        while (i + len < n && i - len >= 0 && ss[i + len] == ss[i - len])
        {
            len++;
        }

        if (i + len > r)
        {
            r = i + len;
            c = i;
        }

        p[i] = len;
    }
}

int main()
{
    cin >> s;
    manacher();

    for (int i = 0, j = 0; i < n; i++)
    {
        while (i + p[i] > j)
        {
            l[j] = j - i;
            j += 2;
        }
    }

    for (int i = n - 1, j = n - 1; i >= 0; i--)
    {
        while (i - p[i] < j)
        {
            r[j] = i - j;
            j -= 2;
        }
    }

    for (int i = 2; i <= n - 3; i += 2)
    {
        ans = max(ans, l[i] + r[i]);
    }

    cout << ans << endl;
}