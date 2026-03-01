/*
 * @lc app=leetcode.cn id=115 lang=cpp
 *
 * [115] 不同的子序列
 */

// @lc code=start
#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    int numDistinct(string s, string t)
    {
        int n = s.length(), m = t.length();

        vector<vector<int>> dp(n + 1, vector<int>(m + 1));
        for (auto &line: dp)
        {
            line[0] = 1;
        }

       for (int i = 1; i <= n; i++) 
       {
            for (int j = 1; j <= m; j++)
            {
                dp[i][j] = dp[i - 1][j];

                if (s[i - 1] == t[j - 1])
                {
                    dp[i][j] = (dp[i][j] + dp[i - 1][j - 1]) % 1000000007;
                }
            }
       }

       return dp[n][m];
    }


    int numDistinct1(string s, string t)
    {
        int n = s.length(), m = t.length();

        vector<int> dp(m + 1);
        dp[0] = 1;

        for (int i = 1; i <= n; i++)
        {
            for (int j = m; j >= 1; j--)
            {
                if (s[i - 1] == t[j - 1])
                {
                    dp[j] = (dp[j] + dp[j - 1]) % 1000000007;
                } 
            }
        }

        return dp[m];
    }
};
// @lc code=end