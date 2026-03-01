/*
 * @lc app=leetcode.cn id=2290 lang=cpp
 *
 * [2290] 到达角落需要移除障碍物的最小数目
 */

// @lc code=start
#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    int minimumObstacles(vector<vector<int>>& grid)
    {
        vector<int> move = {-1, 0, 1, 0, -1};

        int m = grid.size(), n = grid[0].size();
        vector<vector<int>> distance(m, vector<int>(n, INT_MAX));

        deque<pair<int, int>> dq;
        dq.push_front(make_pair(0, 0));
        distance[0][0] = 0;

        while (dq.empty() == false)
        {
            pair<int, int> record = dq.front();
            dq.pop_front();
            
            int x = record.first, y = record.second;
            if (x == m - 1 && y == n - 1)
            {
                return distance[x][y];
            }

            for (int i = 0; i < 4; i++)
            {
                int nx = x + move[i], ny = y + move[i + 1];
                if (nx >= 0 && ny >= 0 && nx < m && ny < n && distance[x][y] + grid[nx][ny] < distance[nx][ny])
                {
                    distance[nx][ny] = distance[x][y] + grid[nx][ny];
                    if (grid[nx][ny] == 0)
                    {
                        dq.push_front(make_pair(nx, ny));
                    }
                    else
                    {
                        dq.push_back(make_pair(nx, ny));
                    }
                }
            }
        }

        return -1;
    }
};
// @lc code=end

