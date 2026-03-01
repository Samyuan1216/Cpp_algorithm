/*
 * @lc app=leetcode.cn id=486 lang=cpp
 *
 * [486] 预测赢家
 */

// @lc code=start
#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    bool predictTheWinner(vector<int>& nums)
    {
        int sum = 0;
        for (auto &x: nums)
        {
            sum += x;
        }

        int n = nums.size();
        vector<vector<int>> dp(n, vector<int>(n));
        for (int i = 0; i < n - 1; i++)
        {
            dp[i][i] = nums[i];
            dp[i][i + 1] = max(nums[i], nums[i + 1]);
        }

        dp[n - 1][n - 1] = nums[n - 1];
        for (int l = n - 3; l >= 0; l--)
        {
            for (int r = l + 2; r < n; r++)
            {
                dp[l][r] = max(nums[l] + min(dp[l + 2][r], dp[l + 1][r - 1]), nums[r] + min(dp[l][r - 2], dp[l + 1][r - 1]));
            }
        }

        int first = dp[0][n - 1];
        int second = sum - first;

        return first >= second;
    }
};
// @lc code=end

