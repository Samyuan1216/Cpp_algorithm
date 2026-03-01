/*
 * @lc app=leetcode.cn id=85 lang=cpp
 *
 * [85] 最大矩形
 */

// @lc code=start
#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    int maximalRectangle(vector<vector<char>>& matrix)
    {
        int n = matrix.size(), m = matrix[0].size();
        vector<int> height(m);

        int ans = 0;
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < m; j++)
            {
                height[j] = (matrix[i][j] == '0'? 0: height[j] + 1);
            }

            ans = max(ans, compute(height, m));
        }

        return ans;
    }

    int compute(vector<int> &height, int &m)
    {
        vector<int> st(m);
        int r = -1;

        int ans = 0;
        for (int i = 0; i < m; i++)
        {
            while (r >= 0 && height[i] <= height[st[r]])
            {
                int cur = st[r--];
                int left = (r == -1? -1: st[r]);

                ans = max(ans, height[cur] * (i - left - 1));
            }

            st[++r] = i;
        }

        while (r >= 0)
        {
            int cur = st[r--];
            int left = (r == -1? -1: st[r]);

            ans = max(ans, height[cur] * (m - left - 1));
        }

        return ans;
    }
};
// @lc code=end

