/*
 * @lc app=leetcode.cn id=42 lang=cpp
 *
 * [42] 接雨水
 */

// @lc code=start
#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    int trap(vector<int>& height)
    {
        int n = height.size();
        vector<int> st(n);
        int r = -1;

        int ans = 0;
        for (int i = 0; i < n; i++)
        {
            while (r >= 0 && height[i] >= height[st[r]])
            {
                int cur = st[r--];
                int left = (r == -1? -1: st[r]);
                int width = (left == -1? 0: i - left - 1);
                
                if (width > 0)
                {
                    ans += width * (min(height[st[r]], height[i]) - height[cur]);
                }
            }

            st[++r] = i;
        }

        return ans;
    }
};
// @lc code=end

