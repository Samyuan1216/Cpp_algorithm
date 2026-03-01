/*
 * @lc app=leetcode.cn id=2218 lang=cpp
 *
 * [2218] 从栈中取出 K 个硬币的最大面值和
 */

// @lc code=start
#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    int maxValueOfCoins(vector<vector<int>>& piles, int k)
    {
        int n = piles.size();
        vector<int> dp(k + 1);

        for (int i = 0; i < n; i++)
        {
            vector<int> presum(piles[i].size());
            presum[0] = piles[i][0];

            for (int j = 1; j < presum.size(); j++)
            {
                presum[j] = presum[j - 1] + piles[i][j];
            }

            for (int j = k; j >= 0; j--)
            {
                for (int p = 1; p <= presum.size(); p++)
                {
                    if (j - p >= 0)
                    {
                        dp[j] = max(dp[j], dp[j - p] + presum[p - 1]);
                    }
                }
            }
        }

        return dp[k];
    }
};
// @lc code=end

