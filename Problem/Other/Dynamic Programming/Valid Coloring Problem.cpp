#include <bits/stdc++.h>
using namespace std;

int main()
{
    int n = 0, m = 0;
    cin >> n >> m;

    const int mod = 1000000007;
    // vector<vector<int>> dp(n + 1, vector<int>(m + 1));
    // for (int i = 1; i <= n; i++)
    // {
    //     dp[i][1] = m;
    // }

    // for (int i = 2; i <= n; i++)
    // {
    //     for (int j = 2; j <= m; j++)
    //     {
    //         dp[i][j] = (int)(((long long)dp[i - 1][j] * j) % mod);
    //         dp[i][j] = (int)((((long long)dp[i - 1][j - 1] * (m - j + 1)) % mod + dp[i][j]) % mod);
    //     }
    // }

    // cout << dp[n][m] << endl;

    vector<int> dp(m + 1);
    dp[1] = m;

    for (int i = 2; i <= n; i++)
    {
        int left_up = dp[1], back_up = 0;
        for (int j = 2; j <= m; j++)
        {
            back_up = dp[j];
            dp[j] = (int)(((long long)back_up * j) % mod);
            dp[j] = (int)((((long long)left_up * (m - j + 1)) % mod + dp[j]) % mod);
            left_up = back_up;
        }
    }

    cout << dp[m] << endl;
}