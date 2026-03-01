#include <bits/stdc++.h>

const int MAXN = 13, MOD = 100000000;
int graph[MAXN][MAXN], dp[MAXN][1 << MAXN];
int n, m, maxs;

int get(int s, int j)
{
    return (s >> j) & 1;
}

int set(int s, int j, int v)
{
    return (v == 0? s & (~(1 << j)): s | (1 << j));
}

int main()
{
    std::cin >> n >> m;
    maxs = 1 << m;

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            std::cin >> graph[i][j];
        }
    }

    std::fill(dp[0], dp[0] + maxs, 1);
    for (int i = n - 1; i >= 0; i--)
    {
        for (int s = 0; s < maxs; s++)
        {
            dp[m][s] = dp[0][s];
        }

        for (int j = m - 1, ans; j >= 0; j--)
        {
            for (int s = 0; s < maxs; s++)
            {
                ans = dp[j + 1][set(s, j, 0)];
                if (graph[i][j] == 1 && (j == 0 || get(s, j - 1) == 0) && get(s, j) == 0)
                {
                    ans = (ans + dp[j + 1][set(s, j, 1)]) % MOD;
                }

                dp[j][s] = ans;
            }
        }
    }

    std::cout << dp[0][0] << std::endl;
}