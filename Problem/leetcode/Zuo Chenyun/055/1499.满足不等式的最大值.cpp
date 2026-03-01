/*
 * @lc app=leetcode.cn id=1499 lang=cpp
 *
 * [1499] 满足不等式的最大值
 */

// @lc code=start
#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    int findMaxValueOfEquation(vector<vector<int>>& points, int k)
    {
        int n = points.size();
        vector<vector<int>> dq(n, vector<int>(2));
        int h = 0, t = 0;

        int ans = INT32_MIN;
        for (int i = 0; i < n; i++)
        {
            int x = points[i][0], y = points[i][1];
            while (h < t && dq[h][0] + k < x)
            {
                h++;
            }

            if (h < t)
            {
                ans = max(ans, x + y + dq[h][1] - dq[h][0]);
            }

            while (h < t && dq[t - 1][1] - dq[t - 1][0] <= y - x)
            {
                t--;
            }

            dq[t][0] = x;
            dq[t++][1] = y;
        }

        return ans;
    }
};
// @lc code=end

