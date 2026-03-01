/*
 * @lc app=leetcode.cn id=1438 lang=cpp
 *
 * [1438] 绝对差不超过限制的最长连续子数组
 */

// @lc code=start
#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    int longestSubarray(vector<int>& nums, int limit)
    {
        int n = nums.size(), maxh = 0, maxt = 0, minh = 0, mint = 0, ans = 0;
        vector<int> max_dq(n + 1), min_dq(n + 1);

        auto ok = [&](int limit, int number) -> bool
        {
            int maxn = (maxh < maxt? max(nums[max_dq[maxh]], number): number);
            int minn = (minh < mint? min(nums[min_dq[minh]], number): number);

            return maxn - minn <= limit;
        };

        auto push = [&](int r) -> void
        {
            while (maxh < maxt && nums[max_dq[maxt - 1]] <= nums[r])
            {
                maxt--;
            }
            
            max_dq[maxt++] = r;
            
            while (minh < mint && nums[min_dq[mint - 1]] >= nums[r])
            {
                mint--;
            }
            
            min_dq[mint++] = r;
        };

        auto pop = [&](int l) -> void
        {
            if (maxh < maxt && max_dq[maxh] == l)
            {
                maxh++;
            }

            if (minh < mint && min_dq[minh] == l)
            {
                minh++;
            }
        };

        for (int l = 0, r = 0; l < n; l++)
        {
            while (r < n && ok(limit, nums[r]))
            {
                push(r++);
            }

            ans = max(ans, r - l);
            pop(l);
        }

        return ans;
    }
};
// @lc code=end

