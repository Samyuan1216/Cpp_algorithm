#include <bits/stdc++.h>
using namespace std;

using vi = vector<int>;
using vvi = vector<vi>;

const int MAXN = 1000010;
vvi st(MAXN, vi(2));
vi ne(MAXN);
string s, t, ans;
int top = -1, x, y;

void next_array()
{
    ne[0] = -1;
    ne[1] = 0;

    int i = 2, cn = 0;
    while (i < t.length())
    {
        if (t[i - 1] == t[cn])
        {
            ne[i++] = ++cn;
        }
        else if (cn > 0)
        {
            cn = ne[cn];
        }
        else
        {
            ne[i++] = 0;
        }
    }
}

int main()
{
    cin >> s >> t;
    next_array();

    while (x < s.length())
    {
        if (s[x] == t[y])
        {
            st[++top][0] = x;
            st[top][1] = y;

            x++;
            y++;
        }
        else if (y == 0)
        {
            st[++top][0] = x;
            st[top][1] = -1;

            x++;
        }
        else
        {
            y = ne[y];
        }

        if (y == t.length())
        {
            top -= t.length();
            if (top >= 0)
            {
                y = st[top][1] + 1;
            }
            else
            {
                y = 0;
            }
        }
    }

    for (int i = 0; i <= top; i++)
    {
        ans += s[st[i][0]];
    }

    cout << ans << endl;
}