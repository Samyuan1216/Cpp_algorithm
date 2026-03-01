/*
 * @lc app=leetcode.cn id=410 lang=cpp
 *
 * [410] 分割数组的最大值
 */

// @lc code=start
#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    int splitArray(vector<int>& nums, int k)
    {
        long long sum = 0;
        for (auto &x: nums)
        {
            sum += x;
        }

        long long ans = 0;
        for (int l = 0, r = sum, m = 0, cur = 0; l <= r;)
        {
            m = l + ((r - l) >> 1);
            cur = f(nums, m);

            if (cur <= k)
            {
                ans = m;
                r = m - 1;
            }
            else
            {
                l = m + 1;
            }
        }

        return ans;
    }

    int f(vector<int> &nums, int limit)
    {
        int parts = 1, sum = 0;
        for (auto &x: nums)
        {
            if (x > limit)
            {
                return INT32_MAX;
            }

            if (sum + x > limit)
            {
                parts++;
                sum = x;
            }
            else
            {
                sum += x;
            }
        }

        return parts;
    }
};
// @lc code=end

