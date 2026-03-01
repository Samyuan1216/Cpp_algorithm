#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1010, MOD = 19650827;
vector<vector<int>> dp(MAXN, vector<int>(2));
vector<int> diff(MAXN);
int n = 0;

int main()
{
    cin >> n;
    for (int i = 1; i <= n; i++)
    {
        cin >> diff[i];
    }

    if (diff[n - 1] < diff[n])
    {
        dp[n][0] = dp[n][1] = 1;
    }

    for (int l = n - 2; l >= 1; l--)
    {
        if (diff[l] < diff[l + 1])
        {
            dp[l + 1][0] = dp[l + 1][1] = 1;
        }
        else
        {
            dp[l + 1][0] = dp[l + 1][1] = 0;
        }

        for (int r = l + 2; r <= n; r++)
        {
            int a = 0, b = 0;
            if (diff[l] < diff[l + 1])
            {
                a = (a + dp[r][0]) % MOD;
            }

            if (diff[l] < diff[r])
            {
                a = (a + dp[r][1]) % MOD;
            }

            if (diff[r] > diff[l])
            {
                b = (b + dp[r - 1][0]) % MOD;
            }

            if (diff[r] > diff[r - 1])
            {
                b = (b + dp[r - 1][1]) % MOD;
            }

            dp[r][0] = a;
            dp[r][1] = b;
        }
    }

    cout << (dp[n][0] + dp[n][1]) % MOD << endl;
}