/*
 * @lc app=leetcode.cn id=3718 lang=cpp
 *
 * [3718] 缺失的最小倍数
 */

// @lc code=start
#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    int missingMultiple(vector<int>& nums, int k)
    {
        int ans = 0;
        sort(nums.begin(), nums.end());
        for (auto &x: nums)
        {
            if (x == ans + k)
            {
                ans = x;
            }
        }

        return ans + k;
    }
};
// @lc code=end

