/*
 * @lc app=leetcode.cn id=435 lang=cpp
 *
 * [435] 无重叠区间
 */

// @lc code=start
#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    int eraseOverlapIntervals(vector<vector<int>>& intervals)
    {
        sort(intervals.begin(), intervals.end(), [](auto &a, auto &b)
        {
            return a[1] < b[1];
        });

        int n = intervals.size();
        int ans = 0;
        for (int i = 0, cur = -50010; i < n; i++)
        {
            if (cur <= intervals[i][0])
            {
                ans++;
                cur = intervals[i][1];
            }
        }

        return n - ans;
    }
};
// @lc code=end

