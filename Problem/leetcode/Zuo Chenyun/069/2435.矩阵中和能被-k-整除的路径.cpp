/*
 * @lc app=leetcode.cn id=2435 lang=cpp
 *
 * [2435] 矩阵中和能被 K 整除的路径
 */

// @lc code=start
#include <bits/stdc++.h>
using namespace std;

class Solution
{
    const int mod = 1000000007;
public:
    int numberOfPaths(vector<vector<int>>& grid, int k)
    {
        int n = grid.size();
        int m = grid[0].size();

        vector<vector<vector<int>>> dp(n, vector<vector<int>>(m, vector<int>(k)));
        dp[n - 1][m - 1][grid[n - 1][m - 1] % k] = 1;

        for (int i = n - 2; i >= 0; i--)
        {
            for (int r = 0; r < k; r++)
            {
                dp[i][m - 1][r] = dp[i + 1][m - 1][(k + r - grid[i][m - 1] % k) % k];
            }
        }

        for (int i = m - 2; i >= 0; i--)
        {
            for (int r = 0; r < k; r++)
            {
                dp[n - 1][i][r] = dp[n - 1][i + 1][(k + r - grid[n - 1][i] % k) % k];
            }
        }

        for (int i = n - 2, need = 0; i >= 0; i--)
        {
            for (int j = m - 2; j >= 0; j--)
            {
                for (int r = 0; r < k; r++)
                {
                    need = (k + r - grid[i][j] % k) % k;
                    dp[i][j][r] = dp[i + 1][j][need];
                    dp[i][j][r] = (dp[i][j][r] + dp[i][j + 1][need]) % mod;
                }
            }
        }

        return dp[0][0][0];
    }
};
// @lc code=end

