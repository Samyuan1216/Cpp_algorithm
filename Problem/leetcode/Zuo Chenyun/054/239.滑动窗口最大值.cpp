/*
 * @lc app=leetcode.cn id=239 lang=cpp
 *
 * [239] 滑动窗口最大值
 */

// @lc code=start
#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    vector<int> maxSlidingWindow(vector<int>& nums, int k)
    {
        vector<int> dq(nums.size() + 1);
        int h = 0, t = 0;

        for (int i = 0; i < k; i++)
        {
            while (h < t && nums[dq[t - 1]] <= nums[i])
            {
                t--;
            }

            dq[t++] = i;
        }

        int m = nums.size() - k + 1;
        vector<int> ans(m);

        for (int l = 0, r = k - 1; l < m; l++, r++)
        {
            while (h < t && nums[dq[t - 1]] <= nums[r])
            {
                t--;
            }

            dq[t++] = r;

            ans[l] = nums[dq[h]];
            if (dq[h] == l)
            {
                h++;
            }
        }

        return ans;
    }
};
// @lc code=end

