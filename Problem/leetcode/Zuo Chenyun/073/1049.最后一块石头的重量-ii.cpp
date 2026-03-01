/*
 * @lc app=leetcode.cn id=1049 lang=cpp
 *
 * [1049] 最后一块石头的重量 II
 */

// @lc code=start
#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    int lastStoneWeightII(vector<int>& stones)
    {
        int sum = 0;
        for (auto &x: stones)
        {
            sum += x;
        }

        vector<int> dp(sum / 2 + 1);
        for (auto &x: stones)
        {
            for (int j = sum / 2; j >= x; j--)
            {
                dp[j] = max(dp[j], dp[j - x] + x);
            }
        }

        return sum - dp[sum / 2] - dp[sum / 2];
    }
};
// @lc code=end

