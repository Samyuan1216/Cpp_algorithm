/*
 * @lc app=leetcode.cn id=1547 lang=cpp
 *
 * [1547] 切棍子的最小成本
 */

// @lc code=start
#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    int minCost(int n, vector<int>& cuts)
    {
        int m = cuts.size();
        sort(cuts.begin(), cuts.end());

        vector<int> arr(m + 2);
        arr[m + 1] = n;
        for (int i = 1; i <= m; i++)
        {
            arr[i] = cuts[i - 1];
        }

        vector<vector<int>> dp(m + 2, vector<int>(m + 2));
        for (int i = 1; i <= m; i++)
        {
            dp[i][i] = arr[i + 1] - arr[i - 1];
        }

        for (int l = m - 1, next = 0; l >= 1; l--)
        {
            for (int r = l + 1; r <= m; r++)
            {
                next = INT32_MAX;
                for (int k = l; k <= r; k++)
                {
                    next = min(next, dp[l][k - 1] + dp[k + 1][r]);
                }

                dp[l][r] = arr[r + 1] - arr[l - 1] + next;
            }
        }

        return dp[1][m];
    }
};
// @lc code=end

