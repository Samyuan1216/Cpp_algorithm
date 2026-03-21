#include <bits/stdc++.h>

using vi = std::vector<int>;

const int MAXN = 1000010;
vi za(MAXN), zb(MAXN), ea(MAXN), eb(MAXN);
std::string a, b;
int t, n, m, ans;

void z_array(vi &z, std::string &str, int n)
{
    z[0] = 0;
    for (int i = 1, r = 1, c = 1, len; i < n; i++)
    {
        len = (i < r? std::min(r - i, z[i - c]): 0);
        while (i + len < n && str[i + len] == str[len])
        {
            len++;
        }

        if (i + len > r)
        {
            c = i;
            r = i + len;
        }

        z[i] = len;
    }
}

void e_array(vi &e, vi &z, std::string &a, std::string &b, int n, int m)
{
    for (int i = 0, r = 0, c = 0, len; i < n; i++)
    {
        len = (i < r? std::min(r - i, z[i - c]): 0);
        while (i + len < n && len < m && a[i + len] == b[len])
        {
            len++;
        }

        if (i + len > r)
        {
            c = i;
            r = i + len;
        }

        e[i] = len;
    }

    e[n] = 0;
}

void solve()
{
    std::cin >> a >> b;
    n = a.length(), m = b.length(), ans = INT32_MAX;

    z_array(za, a, n);
    z_array(zb, b, m);

    e_array(ea, zb, a, b, n, m);
    e_array(eb, za, b, a, m, n);

    for (int i = 0; i < n; i++)
    {
        if (ea[i] == n - i && eb[n - i] == i)
        {
            ans = i;
            break;
        }
    }

    if (ans == INT32_MAX)
    {
        std::cout << -1 << std::endl;
    }
    else
    {
        std::cout << ans << std::endl;
    }
}

int main()
{
    std::cin >> t;
    while (t--)
    {
        solve();
    }
}