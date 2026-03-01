/*
 * @lc app=leetcode.cn id=962 lang=cpp
 *
 * [962] 最大宽度坡
 */

// @lc code=start
#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    int maxWidthRamp(vector<int>& nums)
    {
        int n = nums.size();
        vector<int> st(n);
        int r = -1;

        for (int i = 0; i < n; i++)
        {
            if (r == -1 || nums[i] < nums[st[r]])
            {
                st[++r] = i;
            }
        }

        int ans = 0;
        for (int i = n - 1; i >= 0; i--)
        {
            while (r >= 0 && nums[i] >= nums[st[r]])
            {
                ans = max(ans, i - st[r--]);
            }
        }

        return ans;
    }
};
// @lc code=end

