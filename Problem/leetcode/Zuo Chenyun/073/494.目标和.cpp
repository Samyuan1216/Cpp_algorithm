/*
 * @lc app=leetcode.cn id=494 lang=cpp
 *
 * [494] 目标和
 */

// @lc code=start
#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    int findTargetSumWays(vector<int>& nums, int target)
    {
        int s = 0;
        for (auto &x: nums)
        {
            s += x;
        }

        if (s < -target || s < target)
        {
            return 0;
        }
        else if ((s & 1) != (target & 1))
        {
            return 0;
        }

        vector<int> dp((s + target) / 2 + 1);

        dp[0] = 1;
        for (auto &x: nums)
        {
            for (int j = (s + target) / 2; j >= x; j--)
            {
                dp[j] += dp[j - x];
            }
        }

        return dp[(s + target) / 2];
    }
};
// @lc code=end

