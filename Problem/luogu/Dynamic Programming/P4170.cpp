#include <bits/stdc++.h>
using namespace std;

const int MAXN = 55;
vector<vector<int>> dp(MAXN, vector<int>(MAXN));
string s;
int n = 0;

int main()
{
    cin >> s;

    int n = s.length();
    for (int i = 0; i < n - 1; i++)
    {
        dp[i][i] = 1;
        dp[i][i + 1] = (s[i] == s[i + 1]? 1: 2);
    }

    dp[n - 1][n - 1] = 1;
    for (int l = n - 3; l >= 0; l--)
    {
        for (int r = l + 2; r < n; r++)
        {
            if (s[l] == s[r])
            {
                dp[l][r] = dp[l][r - 1];
            }
            else
            {
                int ans = INT32_MAX;
                for (int m = l; m < r; m++)
                {
                    ans = min(ans, dp[l][m] + dp[m + 1][r]);
                }

                dp[l][r] = ans;
            }
        }
    }

    cout << dp[0][n - 1] << endl;
}