/*
 * @lc app=leetcode.cn id=688 lang=cpp
 *
 * [688] 骑士在棋盘上的概率
 */

// @lc code=start
#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    double knightProbability(int n, int k, int row, int column)
    {
        vector<vector<vector<double>>> dp(k + 1, vector<vector<double>>(n, vector<double>(n)));
        for (auto &line: dp[0])
        {
            for (auto &x: line)
            {
                x = 1;
            }
        }

        for (int i = 1; i <= k; i++)
        {
            for (int p = 0; p < n; p++)
            {
                for (int q = 0; q < n; q++)
                {
                    if (p >= 2 && q >= 1)
                    {
                        dp[i][p][q] += dp[i - 1][p - 2][q - 1] / 8;
                    }

                    if (p < n - 2 && q >= 1)
                    {
                        dp[i][p][q] += dp[i - 1][p + 2][q - 1] / 8;
                    }

                    if (p >= 2 && q < n - 1)
                    {
                        dp[i][p][q] += dp[i - 1][p - 2][q + 1] / 8;
                    }

                    if (p < n - 2 && q < n - 1)
                    {
                        dp[i][p][q] += dp[i - 1][p + 2][q + 1] / 8;
                    }

                    if (p >= 1 && q >= 2)
                    {
                        dp[i][p][q] += dp[i - 1][p - 1][q - 2] / 8;
                    }

                    if (p < n - 1 && q >= 2)
                    {
                        dp[i][p][q] += dp[i - 1][p + 1][q - 2] / 8;
                    }

                    if (p >= 1 && q < n - 2)
                    {
                        dp[i][p][q] += dp[i - 1][p - 1][q + 2] / 8;
                    }

                    if (p < n - 1 && q < n - 2)
                    {
                        dp[i][p][q] += dp[i - 1][p + 1][q + 2] / 8;
                    }
                }
            }
        }

        return dp[k][row][column];
    }
};
// @lc code=end

