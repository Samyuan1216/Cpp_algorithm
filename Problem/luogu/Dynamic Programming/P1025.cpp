#include <bits/stdc++.h>

const int MAXN = 210, MAXK = 7;
int dp[MAXN][MAXK];
int n, k;

int dfs(int n, int k)
{
    if (n == 0)
    {
        return 1;
    }

    if (k == 0)
    {
        return 0;
    }

    if (dp[n][k] != -1)
    {
        return dp[n][k];
    }

    int ans;
    if (n < k)
    {
        ans = dfs(n, n);
    }
    else
    {
        ans = dfs(n, k - 1) + dfs(n - k, k);
    }

    dp[n][k] = ans;
    return ans;
}

int main()
{
    std::cin >> n >> k;
    for (int i = 0; i <= n; i++)
    {
        for (int j = 0; j <= k; j++)
        {
            dp[i][j] = -1;
        }
    }

    n -= k;
    std::cout << dfs(n, k) << std::endl;
}