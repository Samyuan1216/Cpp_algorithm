#include <bits/stdc++.h>

const int MAXN = 55, MAXM = 1310;
int grid[MAXN][MAXN], dp[MAXN][MAXM], max[MAXN][MAXM];
int n, m, ans;

void prepare(int row_limit)
{
    for (int col = 0; col <= m; col++)
    {
        for (int row = row_limit, suf = 0; row >= 0; row--)
        {
            suf = std::max(suf, dp[row][col]);
            max[row][col] = suf;
        }
    }
}

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    std::cin >> n >> m;
    for (int j = 1; j <= n; j++)
    {
        for (int i = n; i >= j; i--)
        {
            std::cin >> grid[i][j];
        }
    }

    for (int i = 1, cur = 0; i <= n; i++, cur = 0)
    {
        prepare(i - 1);
        for (int j = 0; j <= i; j++)
        {
            cur += grid[i][j];
            for (int k = (j + 1) * j / 2; k <= m; k++)
            {
                dp[j][k] = max[std::max(0, j - 1)][k - j] + cur;
                ans = std::max(ans, dp[j][k]);
            }
        }
    }

    std::cout << ans << "\n";
}