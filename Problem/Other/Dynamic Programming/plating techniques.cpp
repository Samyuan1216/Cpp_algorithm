#include <bits/stdc++.h>

using ll = long long;
using vi = std::vector<int>;
using vvi = std::vector<vi>;

const int MOD = 1000000007;

int dfs1(int i, int k)
{
    if (i == 0)
    {
        return 1;
    }

    if (i == 1)
    {
        return k - 1;
    }

    ll p1 = dfs1(i - 1, k), p2 = dfs1(i - 2, k);
    return (int)(((p1 + p2) * (k - 1)) % MOD);
}

int dp1(int n, int k)
{
    if (n == 1)
    {
        return k;
    }

    return (int)((((ll) dfs1(n - 1, k) + dfs1(n - 2, k)) * k) % MOD);
}

int dp2(int n, int k)
{
    if (n == 1)
    {
        return k;
    }

    vi dp(n);
    dp[0] = 1, dp[1] = k - 1;
    
    for (int i = 2; i < n; i++)
    {
        ll p1 = dp[i - 1], p2 = dp[i - 2];
        dp[i] = (int)(((p1 + p2) * (k - 1)) % MOD);
    }

    return (int)((((ll)dp[n - 1] + dp[n - 2]) * k) % MOD);
}

vvi multiply(vvi a, vvi b)
{
    int n = a.size(), m = b[0].size(), k = a[0].size();
    vvi ans(n, vi(m));
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            for (int c = 0; c < k; c++)
            {
                ans[i][j] = (int)(((ll)ans[i][j] + (ll)a[i][c] * b[c][j]) % MOD);
            }
        }
    }

    return ans;
}

vvi power(vvi m, int p)
{
    int n = m.size();
    vvi ans(n, vi(n));
    for (int i = 0; i < n; i++)
    {
        ans[i][i] = 1;
    }

    while (p != 0)
    {
        if ((p & 1) != 0)
        {
            ans = multiply(ans, m);
        }

        m = multiply(m, m);
        p >>= 1;
    }

    return ans;
}

int dp3(int n, int k)
{
    if (n == 1)
    {
        return k;
    }

    int s = k - 1;
    vvi start{{1, s}}, base{{0, s}, {1, s}};
    vvi ans = multiply(start, power(base, n - 2));

    return (int)((((ll)ans[0][0] + ans[0][1]) * k) % MOD);
}

int dfs2(vi &path, int i, int k)
{
    if (i == path.size())
    {
        int len = 1;
        for (int j = 1; j < path.size(); j++)
        {
            if (path[j - 1] == path[j])
            {
                len++;
            }
            else
            {
                len = 1;
            }

            if (len > 2)
            {
                return 0;
            }
        }

        return len > 2 ? 0 : 1;
    }
    else
    {
        int ans = 0;
        for (int j = 0; j < k; j++)
        {
            path[i] = j;
            ans += dfs2(path, i + 1, k);
        }
        
        return ans;
    }
}

int right(int n, int k)
{
    vi path(n);
    return dfs2(path, 0, k);
}

int main()
{
    std::cout << "测试开始" << std::endl;
    for (int n = 1; n <= 8; n++)
    {
        for (int k = 1; k <= 8; k++)
        {
            int ans1 = dp1(n, k);
            int ans2 = dp2(n, k);
            int ans3 = dp3(n, k);
            int ans4 = right(n, k);
            if (ans1 != ans2 || ans1 != ans3 || ans1 != ans4)
            {
                std::cout << "出错了" << std::endl;
            }
        }
    }
    std::cout << "测试结束" << std::endl;
}