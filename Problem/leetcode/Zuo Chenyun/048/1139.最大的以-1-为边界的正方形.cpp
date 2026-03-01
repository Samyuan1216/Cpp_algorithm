/*
 * @lc app=leetcode.cn id=1139 lang=cpp
 *
 * [1139] 最大的以 1 为边界的正方形
 */

// @lc code=start
#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    int largest1BorderedSquare(vector<vector<int>>& grid)
    {
        int n = grid.size();
        int m = grid[0].size();
        build(grid, n, m);
        
        if (sum(grid, 0, 0, n - 1, m - 1) == 0)
        {
            return 0;
        }

        int ans = 1;
        for (int a = 0; a < n; a++)
        {
            for (int b = 0; b < m; b++)
            {
                for (int c = a + ans, d = b + ans, k = ans + 1; c < n && d < m; c++, d++, k++)
                {
                    if (sum(grid, a, b, c, d) - sum(grid, a + 1, b + 1, c - 1, d - 1) == ((k - 1) << 2))
                    {
                        ans = k;
                    }
                }
            }
        }

        return ans * ans;
    }

    void build(vector<vector<int>> &grid, int n, int m)
    {
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < m; j++)
            {
                grid[i][j] += get(grid, i - 1, j) + get(grid, i, j - 1) - get(grid, i - 1, j - 1);
            }
        }
    }

    int sum(vector<vector<int>> &grid, int a, int b, int c, int d)
    {
        return (a > c? 0: grid[c][d] - get(grid, a - 1, d) - get(grid, c, b - 1) + get(grid, a - 1, b - 1));
    }

    int get(vector<vector<int>> &grid, int i, int j)
    {
        return ((i < 0 || j < 0)? 0: grid[i][j]);
    }
};
// @lc code=end

