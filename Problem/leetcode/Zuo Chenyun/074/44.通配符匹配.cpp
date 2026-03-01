/*
 * @lc app=leetcode.cn id=44 lang=cpp
 *
 * [44] 通配符匹配
 */

// @lc code=start
#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    bool isMatch(string s, string p)
    {
        int n = s.length(), m = p.length();

        vector<vector<int>> dp(n + 1, vector<int>(m + 1));
        dp[n][m] = 1;

        for (int i = n - 1; i >= 0; i--)
        {
            if (p.length() > 0 && p.back() == '*')
            {
                dp[i][m] = 1;
            }
        }

        for (int i = m - 1; i >= 0; i--)
        {
            dp[n][i] = (p[i] == '*') && dp[n][i + 1];
        }

        for (int i = n - 1; i >= 0; i--)
        {
            for (int j = m - 1; j >= 0; j--)
            {
                if (p[j] != '*')
                {
                    dp[i][j] = (s[i] == p[j] || p[j] == '?') && dp[i + 1][j + 1];
                }
                else
                {
                    dp[i][j] = dp[i + 1][j] || dp[i][j + 1];
                }
            }
        }

        return dp[0][0];
    }
};
// @lc code=end

