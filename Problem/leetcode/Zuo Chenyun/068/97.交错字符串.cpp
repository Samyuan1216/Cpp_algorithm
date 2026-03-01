/*
 * @lc app=leetcode.cn id=97 lang=cpp
 *
 * [97] 交错字符串
 */

// @lc code=start
#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    bool isInterleave1(string s1, string s2, string s3)
    {
        if (s1.length() + s2.length() != s3.length())
        {
            return false;
        }

        int n = s1.length(), m = s2.length();

        vector<vector<bool>> dp(n + 1, vector<bool>(m + 1));
        dp[0][0] = true;

        for (int i = 1; i <= n; i++)
        {
            if (s1[i - 1] != s3[i - 1])
            {
                break;
            }

            dp[i][0] = true;
        }

        for (int i = 1; i <= m; i++)
        {
            if (s2[i - 1] != s3[i - 1])
            {
                break;
            }

            dp[0][i] = true;
        }
        
        for (int i = 1; i <= n; i++)
        {
            for (int j = 1; j <= m; j++)
            {
                dp[i][j] = (s1[i - 1] == s3[i + j - 1] && dp[i - 1][j]) || (s2[j - 1] == s3[i + j - 1] && dp[i][j - 1]);
            }
        }

        return dp[n][m];
    }


    bool isInterleave(string s1, string s2, string s3)
    {
        if (s1.length() + s2.length() != s3.length())
        {
            return false;
        }

        int n = s1.length(), m = s2.length();
        vector<bool> dp(m + 1);
        dp[0] = true;

        for (int i = 1; i <= m; i++)
        {
            if (s2[i - 1] != s3[i - 1])
            {
                break;
            }

            dp[i] = true;
        }

        for (int i = 1; i <= n; i++)
        {
            dp[0] = (s1[i - 1] == s3[i - 1]) && dp[0];
            
            for (int j = 1; j <= m; j++)
            {
                dp[j] = (s1[i - 1] == s3[i + j - 1] && dp[j]) || (s2[j - 1] == s3[i + j - 1] && dp[j - 1]);
            }
        }

        return dp[m];
    }
};
// @lc code=end

