/*
 * @lc app=leetcode.cn id=1504 lang=cpp
 *
 * [1504] 统计全 1 子矩形
 */

// @lc code=start
#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    int numSubmat(vector<vector<int>>& mat)
    {
        int n = mat.size(), m = mat[0].size();
        vector<int> height(m);

        int ans = 0;
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < m; j++)
            {
                height[j] = (mat[i][j] == 0? 0: height[j] + 1);
            }

            ans += compute(height, m);
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
                if (height[i] < height[cur])
                {
                    int left = (r == -1? -1: st[r]);
                    int len = i - left - 1;
                    int bottom = max((left == -1? 0: height[left]), height[i]);
                    
                    ans += (height[cur] - bottom) * len * (len + 1) / 2;
                }
            }

            st[++r] = i;
        }

        while (r >= 0)
        {
            int cur = st[r--];
            int left = (r == -1? -1: st[r]);
            int len = m - left - 1;
            int bottom = (left == -1? 0: height[left]);

            ans += (height[cur] - bottom) * len * (len + 1) / 2;
        }

        return ans;
    }
};
// @lc code=end

