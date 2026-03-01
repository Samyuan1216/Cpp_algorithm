/*
 * @lc app=leetcode.cn id=87 lang=cpp
 *
 * [87] 扰乱字符串
 */

// @lc code=start
#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    bool isScramble(string s1, string s2)
    {
        int n = s1.length();
        vector<vector<vector<bool>>> dp(n, vector<vector<bool>>(n, vector<bool>(n + 1)));
        for (int l1 = 0; l1 < n; l1++)
        {
            for (int l2 = 0; l2 < n; l2++)
            {
                dp[l1][l2][1] = (s1[l1] == s2[l2]);
            }
        }

        for (int len = 2; len <= n; len++)
        {
            for (int l1 = 0; l1 <= n - len; l1++)
            {
                for (int l2 = 0; l2 <= n - len; l2++)
                {
                    for (int k = 1; k < len; k++)
                    {
                        if (dp[l1][l2][k] && dp[l1 + k][l2 + k][len - k])
                        {
                            dp[l1][l2][len] = true;
                            break;
                        }
                    }

                    if (dp[l1][l2][len] == false)
                    {
                        for (int i = l1 + 1, j = l2 + len - 1, k = 1; k < len; i++, j--, k++)
                        {
                            if (dp[l1][j][k] && dp[i][l2][len - k])
                            {
                                dp[l1][l2][len] = true;
                                break;
                            }
                        }
                    }
                }
            }
        }

        return dp[0][0][n];
    }
};
// @lc code=end

