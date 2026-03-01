/*
 * @lc app=leetcode.cn id=719 lang=cpp
 *
 * [719] 找出第 K 小的数对距离
 */

// @lc code=start
#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    int smallestDistancePair(vector<int>& nums, int k)
    {
        int n = nums.size();
        sort(nums.begin(), nums.end());

        int ans = 0;
        for (int l = 0, r = nums[n - 1] - nums[0], m = 0; l <= r;)
        {
            m = l + ((r - l) >> 1);
            if (f(nums, m) >= k)
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
        int ans = 0;
        for (int l = 0, r = 0; l < nums.size(); l++)
        {
            while (r + 1 < nums.size() && nums[r + 1] - nums[l] <= limit)
            {
                r++;
            }

            ans += r - l;
        }

        return ans;
    }
};
// @lc code=end

