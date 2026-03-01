/*
 * @lc app=leetcode.cn id=581 lang=cpp
 *
 * [581] 最短无序连续子数组
 */

// @lc code=start
#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    int findUnsortedSubarray(vector<int>& nums)
    {
        int n = nums.size();

        int right = -1, maxn = INT32_MIN;
        for (int i = 0; i < n; i++)
        {
            if (maxn > nums[i])
            {
                right = i;
            }

            maxn = max(maxn, nums[i]);
        }

        int left = n, minn = INT32_MAX;
        for (int i = n - 1; i >= 0; i--)
        {
            if (minn < nums[i])
            {
                left = i;
            }

            minn = min(minn, nums[i]);
        }

        return max(0, right - left + 1);
    }
};
// @lc code=end

