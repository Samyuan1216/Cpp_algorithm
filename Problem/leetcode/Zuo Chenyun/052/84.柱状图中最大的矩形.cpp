/*
 * @lc app=leetcode.cn id=84 lang=cpp
 *
 * [84] 柱状图中最大的矩形
 */

// @lc code=start
#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    int largestRectangleArea(vector<int>& heights)
    {
        int n = heights.size(), r = -1, ans = 0;
        vector<int> s(n);

        for (int i = 0; i < n; i++)
        {
            while (r >= 0 && heights[s[r]] >= heights[i])
            {
                int cur = s[r--];
                int left = (r == -1? -1: s[r]);
                ans = max(ans, heights[cur] * (i - left - 1));
            }

            s[++r] = i;
        }

        while (r >= 0)
        {
            int cur = s[r--];
            int left = (r == -1? -1: s[r]);
            ans = max(ans, heights[cur] * (n - left - 1));
        }

        return ans;
    }
};
// @lc code=end

