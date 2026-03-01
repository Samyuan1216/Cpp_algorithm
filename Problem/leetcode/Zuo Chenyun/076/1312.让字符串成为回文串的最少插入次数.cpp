/*
 * @lc app=leetcode.cn id=1312 lang=cpp
 *
 * [1312] 让字符串成为回文串的最少插入次数
 */

// @lc code=start
#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    int minInsertions(string s)
    {
        int n = s.length();
        vector<int> dp(n);

        for (int l = n - 2, leftdown = 0; l >= 0; l--)
        {
            dp[l + 1] = (s[l] == s[l + 1]? 0: 1);
            leftdown = 0;

            for (int r = l + 2, temp = 0; r < n; r++)
            {
                temp = dp[r];
                if (s[l] == s[r])
                {
                    dp[r] = leftdown;
                }
                else
                {
                    dp[r] = min(dp[r], dp[r - 1]) + 1;
                }

                leftdown = temp;
            }
        }

        return dp[n - 1];
    }
};
// @lc code=end

