/*
 * @lc app=leetcode.cn id=629 lang=cpp
 *
 * [629] K 个逆序对数组
 */

// @lc code=start
#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    int kInversePairs(int n, int k)
    {
        int mod = 1000000007;
        
        vector<vector<int>> dp(n + 1, vector<int>(k + 1));
        dp[0][0] = 1;
        for (int i = 1, window; i <= n; i++)
        {
            dp[i][0] = 1;
            window = 1;
            for (int j = 1; j <= k; j++)
            {
                if (i > j)
                {
                    window = (window + dp[i - 1][j]) % mod;
                }
                else
                {
                    window = ((window + dp[i - 1][j]) % mod - dp[i - 1][j - i] + mod) % mod;
                }

                dp[i][j] = window;
            }
        }

        return dp[n][k];
    }
};
// @lc code=end

