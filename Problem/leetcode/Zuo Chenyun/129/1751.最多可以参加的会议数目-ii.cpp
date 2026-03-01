/*
 * @lc app=leetcode.cn id=1751 lang=cpp
 *
 * [1751] 最多可以参加的会议数目 II
 */

// @lc code=start
#include <bits/stdc++.h>

using vi = std::vector<int>;
using vvi = std::vector<vi>;

class Solution
{
public:
    int maxValue(vvi &events, int k)
    {
        int n = events.size();
        std::sort(events.begin(), events.end(), [](vi &a, vi &b)
        {
            return a[1] < b[1];
        });

        vvi dp(n, vi(k + 1));
        std::fill(dp[0].begin() + 1, dp[0].end(), events[0][2]);

        for (int i = 1, pre; i < n; i++)
        {
            pre = find(events, i - 1, events[i][0]);
            for (int j = 1; j <= k; j++)
            {
                dp[i][j] = std::max(dp[i - 1][j], (pre == -1? 0: dp[pre][j - 1]) + events[i][2]);
            }
        }

        return dp[n - 1][k];
    }

    int find(vvi &events, int i, int s)
    {
        int l = 0, r = i, mid, ans = -1;
        while (l <= r)
        {
            mid = l + (r - l) / 2;
            if (events[mid][1] < s)
            {
                ans = mid;
                l = mid + 1;
            }
            else
            {
                r = mid - 1;
            }
        }

        return ans;
    }
};
// @lc code=end

