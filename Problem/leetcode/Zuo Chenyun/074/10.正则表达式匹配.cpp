/*
 * @lc app=leetcode.cn id=10 lang=cpp
 *
 * [10] 正则表达式匹配
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
        for (int i = m - 1; i >= 0; i--)
        {
            dp[n][i] = (i + 1 <= m) && (p[i + 1] == '*') && dp[n][i + 2];
        }

        for (int i = n - 1; i >= 0; i--)
        {
            for (int j = m - 1; j >= 0; j--)
            {
                if (j + 1 == m || p[j + 1] != '*')
                {
                    dp[i][j] = (s[i] == p[j] || p[j] == '.') && dp[i + 1][j + 1];
                }
                else
                {
                    dp[i][j] = dp[i][j + 2] || ((s[i] == p[j] || p[j] == '.') && dp[i + 1][j]);
                }
            }
        }

        return dp[0][0];
    }
};
// @lc code=end

