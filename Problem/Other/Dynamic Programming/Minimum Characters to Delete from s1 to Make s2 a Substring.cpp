#include <bits/stdc++.h>
using namespace std;

int main()
{
    string s1, s2;
    cin >> s1 >> s2;

    int n = s1.length(), m = s2.length();
    // vector<vector<int>> dp(n + 1, vector<int>(m + 1));
    // for (int i = 1; i <= n; i++)
    // {
    //     dp[i][0] = i;
    //     for (int j = 1; j <= m; j++)
    //     {
    //         if (s1[i - 1] == s2[j - 1])
    //         {
    //             dp[i][j] = dp[i - 1][j - 1];
    //         }
    //         else
    //         {
    //             dp[i][j] = dp[i - 1][j] + 1;
    //         }
    //     }
    // }

    // cout << *min_element(dp[n].begin(), dp[n].end()) << endl;

    vector<int> dp(m + 1);
    for (int i = 1; i <= n; i++)
    {
        int left_up = dp[0], back_up = 0;
        dp[0] = i;
        for (int j = 1; j <= m; j++)
        {
            back_up = dp[j];
            if (s1[i - 1] == s2[j - 1])
            {
                dp[j] = left_up;
            }
            else
            {
                dp[j] = dp[j] + 1;
            }

            left_up = back_up;
        }
    }

    cout << *min_element(dp.begin(), dp.end()) << endl;
}