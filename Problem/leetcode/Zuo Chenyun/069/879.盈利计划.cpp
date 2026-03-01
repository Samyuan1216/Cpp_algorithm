/*
 * @lc app=leetcode.cn id=879 lang=cpp
 *
 * [879] 盈利计划
 */

// @lc code=start
#include <bits/stdc++.h>
using namespace std;

class Solution
{
    const int mod = 1000000007;
public:
    int profitableSchemes1(int n, int minProfit, vector<int>& group, vector<int>& profit)
    {
        int len = group.size();
        vector<vector<vector<int>>> dp(len + 1, vector<vector<int>>(n + 1, vector<int>(minProfit + 1)));
        for (auto &line: dp[len])
        {
            line[0] = 1;
        }

        for (int i = len - 1; i >= 0; i--)
        {
            for (int r = 0; r <= n; r++)
            {
                for (int s = 0; s <= minProfit; s++)
                {
                    int p1 = dp[i + 1][r][s];
                    int p2 = 0;

                    if (group[i] <= r)
                    {
                        p2 = dp[i + 1][r - group[i]][max(s - profit[i], 0)];
                    }

                    dp[i][r][s] = (p1 + p2) % mod;
                }
            }
        }

        return dp[0][n][minProfit];
    }

        int profitableSchemes(int n, int minProfit, vector<int>& group, vector<int>& profit)
        {
            int len = group.size();
            vector<vector<int>> dp(n + 1, vector<int>(minProfit + 1));
            for (auto &line: dp)
            {
                line[0] = 1;
            }

            for (int i = len - 1; i >= 0; i--)
            {
                for (int r = n; r >= group[i]; r--)
                {
                    for (int s = minProfit; s >= 0; s--)
                    {
                        dp[r][s] = (dp[r][s] + dp[r - group[i]][max(s - profit[i], 0)]) % mod;
                    }
                }
            }

            return dp[n][minProfit];
        }
};
// @lc code=end

