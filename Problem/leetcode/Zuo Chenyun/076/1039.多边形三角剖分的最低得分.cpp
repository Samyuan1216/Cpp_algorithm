/*
 * @lc app=leetcode.cn id=1039 lang=cpp
 *
 * [1039] 多边形三角剖分的最低得分
 */

// @lc code=start
#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    int minScoreTriangulation(vector<int>& values)
    {
        int n = values.size();
        vector<vector<int>> dp(n, vector<int>(n));

        for (int l = n - 3; l >= 0; l--)
        {
            for (int r = l + 2; r < n; r++)
            {
                dp[l][r] = INT32_MAX;
                for (int m = l + 1; m < r; m++)
                {
                    dp[l][r] = min(dp[l][r], dp[l][m] + dp[m][r] + values[l] * values[r] * values[m]);
                }
            }
        }

        return dp[0][n - 1];
    }
};
// @lc code=end

