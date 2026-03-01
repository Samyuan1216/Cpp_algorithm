/*
 * @lc app=leetcode.cn id=2560 lang=cpp
 *
 * [2560] 打家劫舍 IV
 */

// @lc code=start
#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    int minCapability(vector<int>& nums, int k)
    {
        int n = nums.size();
        int l = *min_element(nums.begin(), nums.end()), r = *max_element(nums.begin(), nums.end());

        int m = 0, ans = 0;
        while (l <= r)
        {
            m = l + ((r - l) >> 1);
            if (most_rob2(nums, n, m) >= k)
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

    int most_rob1(vector<int> &nums, int n, int m)
    {
        if (n == 1)
        {
            return (nums[0] <= m? 1: 0);
        }
        else if (n == 2)
        {
            return (nums[0] <= m || nums[1] <= m? 1: 0);
        }

        int cur = 0, p = 0, pp = 0;
        for (auto &x: nums)
        {
            cur = max(p, pp + (x <= m? 1: 0));
            pp = p;
            p = cur;
        }

        return cur;
    }

    int most_rob2(vector<int> &nums, int n, int m)
    {
        int ans = 0;
        for (int i = 0; i < n; i++)
        {
            if (nums[i] <= m)
            {
                ans++;
                i++;
            }
        }

        return ans;
    }
};
// @lc code=end

