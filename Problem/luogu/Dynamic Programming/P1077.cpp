#include <bits/stdc++.h>
using namespace std;

int main()
{
    ios::sync_with_stdio(false);

    const int mod = 1000007;

    int n = 0, m = 0;
    cin >> n >> m;

    vector<int> flr(n);
    for (auto &x: flr)
    {
        cin >> x;
    }

    vector<vector<int>> dp(n + 1, vector<int>(m + 1));
    dp[0][0] = 1;

    for (int i = 1; i <= n; i++)
    {
        for (int j = 0; j <= m; j++)
        {
            for (int k = 0; k <= j && k <= flr[i - 1]; k++)
            {
                dp[i][j] = (dp[i][j] + dp[i - 1][j - k]) % mod;
            }
        }
    }

    cout << dp[n][m] << endl;
}