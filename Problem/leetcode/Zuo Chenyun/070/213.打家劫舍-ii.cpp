/*
 * @lc app=leetcode.cn id=213 lang=cpp
 *
 * [213] 打家劫舍 II
 */

// @lc code=start
#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    int rob(vector<int>& nums)
    {
        int n = nums.size();
        
        if (n == 1)
        {
            return nums[0];
        }

        return max(best(nums, 1, n - 1), best(nums, 2, n - 2) + nums[0]);
    }

    int best(vector<int> &nums, int l, int r)
    {
        if (l > r)
        {
            return 0;
        }
        else if (l == r)
        {
            return nums[l];
        }
        else if (l + 1 == r)
        {
            return max(nums[l], nums[r]);
        }

        int cur = INT32_MIN, pp = 0, p = 0;
        for (int i = l; i <= r; i++)
        {
            cur = max(nums[i], max(p, pp + nums[i]));
            pp = p;
            p = cur;
        }

        return cur;
    }
};
// @lc code=end

