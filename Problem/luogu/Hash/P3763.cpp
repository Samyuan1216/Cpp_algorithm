#include <bits/stdc++.h>
using namespace std;

using ull = unsigned long long;
using vull = vector<ull>;

const int MAXN = 100010, base = 499;
vull p(MAXN), ha1(MAXN), ha2(MAXN);
string s1, s2;
int t, n, m, k = 3;

void build()
{
    p[0] = 1;
    for (int i = 1; i < MAXN; i++)
    {
        p[i] = p[i - 1] * base;
    }

    ha1[0] = s1[0] - 'A' + 1;
    for (int i = 1; i < n; i++)
    {
        ha1[i] = ha1[i - 1] * base + s1[i] - 'A' + 1;
    }

    ha2[0] = s2[0] - 'A' + 1;
    for (int i = 1; i < m; i++)
    {
        ha2[i] = ha2[i - 1] * base + s2[i] - 'A' + 1;
    }
}

ull h(vull &ha_, int l, int r)
{
    ull ans = ha_[r];
    ans -= (l == 0? 0: ha_[l - 1] * p[r - l + 1]);

    return ans;
}

bool same(int l1, int l2, int len)
{
    return h(ha1, l1, l1 + len - 1) == h(ha2, l2, l2 + len - 1);
}

bool check(int l1, int r1)
{
    int diff = 0, l2 = 0;
    while (l1 <= r1 && diff <= k)
    {
        int l = 1, r = r1 - l1 + 1, md = 0, len = 0;
        while (l <= r)
        {
            md = l + ((r - l) >> 1);
            if (same(l1, l2, md))
            {
                len = md;
                l = md + 1;
            }
            else
            {
                r = md - 1;
            }
        }

        if (l1 + len <= r1)
        {
            diff++;
        }

        l1 += len + 1;
        l2 += len + 1;
    }

    return diff <= k;
}

void solve()
{
    cin >> s1 >> s2;
    n = s1.length(), m = s2.length();
    if (n < m)
    {
        cout << "0" << endl;
        return;
    }

    build();

    int ans = 0;
    for (int i = 0; i <= n - m; i++)
    {
        if (check(i, i + m - 1))
        {
            ans++;
        }
    }

    cout << ans << endl;
}

int main()
{
    cin >> t;
    while (t--)
    {
        solve();
    }
}