/*
 * @lc app=leetcode.cn id=741 lang=cpp
 *
 * [741] 摘樱桃
 */

// @lc code=start
#include <bits/stdc++.h>

using vi = std::vector<int>;
using vvi = std::vector<vi>;
using v3i = std::vector<vvi>;

class Solution
{
public:
    int cherryPickup(vvi& grid)
    {
        int n = grid.size();        
        v3i dp(n, vvi(n, vi(n, -2)));

        int ans = dfs(grid, dp, n, 0, 0, 0);
        return (ans == -1? 0: ans);
    }

    int dfs(vvi &grid, v3i &dp, int &n, int a, int b, int c)
    {
        int d = a + b - c;
        if (a == n || b == n || c == n || d == n || grid[a][b] == -1 || grid[c][d] == -1)
        {
            return -1;
        }

        if (a == n - 1 && b == n - 1)
        {
            return grid[a][b];
        }

        if (dp[a][b][c] != -2)
        {
            return dp[a][b][c];
        }

        int get = (a == c && b == d? grid[a][b]: (grid[a][b] + grid[c][d]));
        int next = dfs(grid, dp, n, a + 1, b, c + 1);
        next = std::max(next, dfs(grid, dp, n, a + 1, b, c));
        next = std::max(next, dfs(grid, dp, n, a, b + 1, c + 1));
        next = std::max(next, dfs(grid, dp, n, a, b + 1, c));

        int ans = -1;
        if (next != -1)
        {
            ans = get + next;
        }

        dp[a][b][c] = ans;
        return ans;
    }
};
// @lc code=end

