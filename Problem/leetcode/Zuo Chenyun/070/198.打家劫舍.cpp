/*
 * @lc app=leetcode.cn id=198 lang=cpp
 *
 * [198] 打家劫舍
 */

// @lc code=start
#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    int rob(vector<int>& nums)
    {
        int cur = INT32_MIN, prev = 0, pp = 0;
        for (auto &x: nums)
        {
            cur = max(x, max(prev, pp + x));
            pp = prev;
            prev = cur;
        }

        return cur;
    }
};
// @lc code=end

