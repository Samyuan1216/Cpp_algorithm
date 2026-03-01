/*
 * @lc app=leetcode.cn id=918 lang=cpp
 *
 * [918] 环形子数组的最大和
 */

// @lc code=start
#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    int maxSubarraySumCircular(vector<int>& nums)
    {
        int n = nums.size();
        int maxn = nums[0], maxs = nums[0], minn = nums[0], mins = nums[0], all = nums[0];

        for (int i = 1; i < n; i++)
        {
            all += nums[i];

            maxs = max(nums[i], nums[i] + maxs);
            maxn = max(maxs, maxn);

            mins = min(nums[i], nums[i] + mins);
            minn = min(minn, mins);
        }

        return (all == minn)? maxn: max(maxn, all - minn);
    }
};
// @lc code=end

