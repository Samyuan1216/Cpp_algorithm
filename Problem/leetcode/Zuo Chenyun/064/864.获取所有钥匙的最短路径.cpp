/*
 * @lc app=leetcode.cn id=864 lang=cpp
 *
 * [864] 获取所有钥匙的最短路径
 */

// @lc code=start
#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    const int MAXN = 31, MAXM = 31, MAXK = 6;
    vector<int> moved = {-1, 0, 1, 0, -1};
    vector<vector<vector<int>>> visited = vector<vector<vector<int>>>(MAXN, vector<vector<int>>(MAXN, vector<int>(1 << MAXK)));
    vector<vector<int>> q = vector<vector<int>>(MAXN * MAXM * (1 << MAXK), vector<int>(3));
    int l = 0, r = 0, n = 0, m = 0, key = 0;

    int shortestPathAllKeys(vector<string>& grid)
    {
        n = grid.size();
        m = grid[0].size();

        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < m; j++)
            {
                if (grid[i][j] == '@')
                {
                    q[r][0] = i;
                    q[r][1] = j;
                    q[r++][2] = 0;
                }

                if (grid[i][j] >= 'a' && grid[i][j] <= 'f')
                {
                    key |= (1 << (grid[i][j] - 'a'));
                }
            }
        }

        int level = 1;
        while (l < r)
        {
            int size = r - l;
            for (int k = 0; k < size; k++)
            {
                int x = q[l][0], y = q[l][1], s = q[l++][2];
                for (int i = 0; i < 4; i++)
                {
                    int nx = x + moved[i], ny = y + moved[i + 1], ns = s;
                    if (nx < 0 || ny < 0 || nx >= n || ny >= m || grid[nx][ny] == '#')
                    {
                        continue;
                    }

                    if (grid[nx][ny] >= 'A' && grid[nx][ny] <= 'Z' && ((ns & (1 << (grid[nx][ny] - 'A'))) == 0))
                    {
                        continue;
                    }

                    if (grid[nx][ny] >= 'a' && grid[nx][ny] <= 'z')
                    {
                        ns |= (1 << (grid[nx][ny] - 'a'));
                    }

                    if (ns == key)
                    {
                        return level;
                    }

                    if (visited[nx][ny][ns] == 0)
                    {
                        visited[nx][ny][ns] = 1;

                        q[r][0] = nx;
                        q[r][1] = ny;
                        q[r++][2] = ns;
                    }
                }
            }

            level++;
        }

        return -1;
    }
};
// @lc code=end

