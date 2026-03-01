#include <bits/stdc++.h>

const int MAXN = 4010;
int dp[MAXN][MAXN], q[MAXN];
int n, m, k, t, l, r, ans = INT32_MIN;

void add(int i, int j)
{
    if (j <= m)
    {
        while (l < r && dp[i][q[r - 1]] <= dp[i][j])
        {
            r--;
        }

        q[r++] = j;
    }
}

void del(int j)
{
    if (l < r && q[l] == j)
    {
        l++;
    }
}

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    std::cin >> n >> m >> k >> t;
    for (int i = 1, x, y, v; i <= k; i++)
    {
        std::cin >> x >> y >> v;

        dp[x][y] = v;
    }

    for (int i = 2; i <= n; i++)
    {
        l = r = 0;
        for (int j = 1; j <= t; j++)
        {
            add(i - 1, j);
        }

        for (int j = 1; j <= m; j++)
        {
            add(i - 1, j + t);
            del(j - t - 1);

            dp[i][j] += dp[i - 1][q[l]];
        }
    }

    for (int j = 1; j <= m; j++)
    {
        ans = std::max(ans, dp[n][j]);
    }

    std::cout << ans << "\n";
}