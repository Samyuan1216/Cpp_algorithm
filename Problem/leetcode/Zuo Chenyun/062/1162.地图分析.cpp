/*
 * @lc app=leetcode.cn id=1162 lang=cpp
 *
 * [1162] 地图分析
 */

// @lc code=start
#include <bits/stdc++.h>
using namespace std;
class Solution
{
public:
    int maxDistance(vector<vector<int>>& grid)
    {
        int n = grid.size();
        vector<vector<int>> q(n * n, vector<int>(2)), visited(n, vector<int>(n));
        int l = 0, r = 0, seas = 0;
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                if (grid[i][j] == 1)
                {
                    visited[i][j] = 1;
                    q[r][0] = i;
                    q[r++][1] = j;
                }
                else
                {
                    seas++;
                }
            }
        }

        if (seas == 0 || seas == n * n)
        {
            return -1;
        }

        vector<int> move = {-1, 0, 1, 0, -1};
        int level = 0;
        while (l < r)
        {
            level++;

            int size = r - l;
            for (int k = 0, x = 0, y = 0, nx = 0, ny = 0; k < size; k++)
            {
                x = q[l][0];
                y = q[l++][1];

                for (int i = 0; i < 4; i++)
                {
                    nx = x + move[i];
                    ny = y + move[i + 1];

                    if (nx >= 0 && nx < n && ny >= 0 && ny < n && visited[nx][ny] == 0)
                    {
                        visited[nx][ny] = 1;
                        q[r][0] = nx;
                        q[r++][1] = ny;
                    }
                }
            }
        }

        return level - 1;
    }
};
// @lc code=end

