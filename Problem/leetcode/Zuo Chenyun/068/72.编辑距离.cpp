/*
 * @lc app=leetcode.cn id=72 lang=cpp
 *
 * [72] 编辑距离
 */

// @lc code=start
#include <bits/stdc++.h>
using namespace std;

class Solution 
{
public:
    int minDistance(string word1, string word2) 
    {
        int n = word1.length(), m = word2.length();

        vector<vector<int>> dp(n + 1, vector<int>(m + 1));
        for (int i = 0; i <= m; i++)
        {
            dp[0][i] = i;
        }

        for (int i = 0; i <= n; i++)
        {
            dp[i][0] = i;
        }

        for (int i = 1; i <= n; i++)
        {
            for (int j = 1; j <= m; j++)
            {
                if (word1[i - 1] == word2[j - 1])
                {
                    dp[i][j] = dp[i - 1][j - 1];
                }
                else
                {
                    dp[i][j] = min(min(dp[i - 1][j - 1] + 1, dp[i][j - 1] + 1), dp[i - 1][j] + 1);
                }
            }
        }

        return dp[n][m];
    }


    int minDistance1(string word1, string word2) 
    {
        int n = word1.length(), m = word2.length();

        vector<int> dp(m + 1);
        for (int i = 0; i <= m; i++)
        {
            dp[i] = i;
        }

        for (int i = 1; i <= n; i++)
        {
            int left_up = dp[0], back_up = 0;
            dp[0] = i;

            for (int j = 1; j <= m; j++)
            {
                back_up = dp[j];

                if (word1[i - 1] == word2[j - 1])
                {
                    dp[j] = left_up;
                }
                else
                {
                    dp[j] = min(min(dp[j] + 1, left_up + 1), dp[j - 1] + 1);
                }

                left_up = back_up;
            }
        }

        return dp[m];
    }
};
// @lc code=end

