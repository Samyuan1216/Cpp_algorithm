/*
 * @lc app=leetcode.cn id=200 lang=cpp
 *
 * [200] 岛屿数量
 */

// @lc code=start
#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    int numIslands(vector<vector<char>>& grid)
    {
        int n = grid.size(), m = grid[0].size();

        auto index = [&](int a, int b) -> int
        {
            return a * m + b;
        };

        int sets = 0;
        vector<int> father(n * m);
        for (int a = 0; a < n; a++)
        {
            for (int b = 0, i = 0; b < m; b++)
            {
                if (grid[a][b] == '1')
                {
                    i = index(a, b);
                    father[i] = i;
                    sets++;
                }
            }
        }

        function<int (int)> find = [&](int i) -> int
        {
            if (i != father[i])
            {
                father[i] = find(father[i]);
            }

            return father[i];
        };

        auto un = [&](int a, int b, int c, int d) -> void
        {
            int ua = find(index(a, b)), ub = find(index(c, d));
            if (ua != ub)
            {
                father[ua] = ub;
                sets--;
            }
        };

        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < m; j++)
            {
                if (grid[i][j] == '1')
                {
                    if (j > 0 && grid[i][j - 1] == '1')
                    {
                        un(i, j, i, j - 1);
                    }

                    if (i > 0 && grid[i - 1][j] == '1')
                    {
                        un(i, j, i - 1, j);
                    }
                }
            }
        }

        return sets;
    }
};
// @lc code=end

