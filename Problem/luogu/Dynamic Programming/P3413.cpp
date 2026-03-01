#include <bits/stdc++.h>
using namespace std;

using vi = vector<int>;
using vvi = vector<vi>;
using vvvi = vector<vvi>;
using vvvvi = vector<vvvi>;

const int MAXN = 1010, MOD = 1000000007;
vvvvi dp(MAXN, vvvi(11, vvi(11, vi(2))));
string l, r;

void build(int n)
{
    for (int a = 0; a < n; a++)
    {
        for (int b = 0; b <= 10; b++)
        {
            for (int c = 0; c <= 10; c++)
            {
                for (int d = 0; d <= 1; d++)
                {
                    dp[a][b][c][d] = -1;
                }
            }
        }
    }
}

int f(string &num, int i, int pp, int p, int free)
{
    if (i == num.length())
    {
        return 1;
    }

    if (dp[i][pp][p][free] != -1)
    {
        return dp[i][pp][p][free];
    }

    int ans = 0;
    if (free == 0)
    {
        if (p == 10)
        {
            ans = (ans + f(num, i + 1, 10, 10, 1)) % MOD;
            for (int cur = 1; cur < num[i] - '0'; cur++)
            {
                ans = (ans + f(num, i + 1, p, cur, 1)) % MOD;
            }
            ans = (ans + f(num, i + 1, p, num[i] - '0', 0)) % MOD;
        }
        else
        {
            for (int cur = 0; cur < num[i] - '0'; cur++)
            {
                if (cur != pp && cur != p)
                {
                    ans = (ans + f(num, i + 1, p, cur, 1)) % MOD;
                }
            }

            if (num[i] - '0' != pp && num[i] - '0' != p)
            {
                ans = (ans + f(num, i + 1, p, num[i] - '0', 0)) % MOD;
            }
        }
    }
    else
    {
        if (p == 10)
        {
            ans = (ans + f(num, i + 1, 10, 10, 1)) % MOD;
            for (int cur = 1; cur <= 9; cur++)
            {
                ans = (ans + f(num, i + 1, p, cur, 1)) % MOD;
            }
        }
        else
        {
            for (int cur = 0; cur <= 9; cur++)
            {
                if (cur != p && cur != pp)
                {
                    ans = (ans + f(num, i + 1, p, cur, 1)) % MOD;
                }
            }
        }
    }

    dp[i][pp][p][free] = ans;
    return ans;
}

int cnt(string &num)
{
    if (num[0] == '0')
    {
        return 0;
    }

    int n = num.length();
    long long all = 0, base = 1;
    for (int i = n - 1; i >= 0; i--)
    {
        all = (all + base * (num[i] - '0')) % MOD;
        base = (base * 10) % MOD;
    }

    build(n);
    return (int)(all - f(num, 0, 10, 10, 0) + MOD) % MOD;
}

bool check(string &num)
{
    for (int pp = -2, p = -1, i = 0; i < num.length(); pp++, p++, i++)
    {
        if (pp >= 0 && num[pp] == num[i])
        {
            return true;
        }

        if (p >= 0 && num[p] == num[i])
        {
            return true;
        }
    }

    return false;
}

int main()
{
    cin >> l >> r;

    int ans = (cnt(r) - cnt(l) + MOD) % MOD;
    if (check(l))
    {
        ans = (ans + 1) % MOD;
    }

    cout << ans << endl;
}