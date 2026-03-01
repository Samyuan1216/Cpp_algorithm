/*
 * @lc app=leetcode.cn id=546 lang=cpp
 *
 * [546] 移除盒子
 */

// @lc code=start
#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    int removeBoxes(vector<int>& boxes)
    {
        int n = boxes.size();
        vector<vector<vector<int>>> dp(n, vector<vector<int>>(n, vector<int>(n)));

        return f(boxes, dp, 0, n - 1, 0);
    }

    int f(vector<int> &boxes, vector<vector<vector<int>>> &dp, int l, int r, int k)
    {
        if (l > r)
        {
            return 0;
        }

        if (dp[l][r][k] > 0)
        {
            return dp[l][r][k];
        }

        int s = l;
        while (s + 1 <= r && boxes[l] == boxes[s + 1])
        {
            s++;
        }

        int cnt = k + s - l + 1;
        int ans = cnt * cnt + f(boxes, dp, s + 1, r, 0);

        for (int m = s + 2; m <= r; m++)
        {
            if (boxes[m] == boxes[l] && boxes[m] != boxes[m - 1])
            {
                ans = max(ans, f(boxes, dp, s + 1, m - 1, 0) + f(boxes, dp, m, r, cnt));
            }
        }

        dp[l][r][k] = ans;
        
        return ans;
    }
};
// @lc code=end

