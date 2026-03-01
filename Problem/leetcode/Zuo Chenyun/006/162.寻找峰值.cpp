/*
 * @lc app=leetcode.cn id=162 lang=cpp
 *
 * [162] 寻找峰值
 */

// @lc code=start
#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    int findPeakElement(vector<int>& nums)
    {
        int n = nums.size();
        if (n == 1 || nums[0] > nums[1])
        {
            return 0;
        }
        else if (nums[n - 1] > nums[n - 2])
        {
            return n - 1;
        }

        for (int l = 1, r = n - 2, m = 0; l <= r;)
        {
            m = (l + r) / 2;

            if (nums[m] < nums[m - 1])
            {
                r = m - 1;
            }
            else if (nums[m] < nums[m + 1])
            {
                l = m + 1;
            }
            else
            {
                return m;
            }
        }

        return -1;
    }
};
// @lc code=end

