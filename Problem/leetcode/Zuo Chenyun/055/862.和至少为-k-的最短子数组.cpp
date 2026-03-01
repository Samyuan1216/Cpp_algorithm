/*
 * @lc app=leetcode.cn id=862 lang=cpp
 *
 * [862] 和至少为 K 的最短子数组
 */

// @lc code=start
#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    int shortestSubarray(vector<int>& nums, int k)
    {
        int n = nums.size();
        vector<long long> sum(n + 1);

        for (int i = 1; i <= n; i++)
        {
            sum[i] = nums[i - 1] + sum[i - 1];
        }

        vector<int> dq(n + 1);
        int h = 0, t = 0;

        int ans = INT32_MAX;
        for (int i = 0; i <= n; i++)
        {
            while (h < t && sum[i] - sum[dq[h]] >= k)
            {
                ans = min(ans, i - dq[h++]);
            }

            while (h < t && sum[dq[t - 1]] >= sum[i])
            {
                t--;
            }

            dq[t++] = i;
        }

        if (ans == INT32_MAX)
        {
            ans = -1;
        }

        return ans;
    }
};
// @lc code=end

