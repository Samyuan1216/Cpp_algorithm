/*
 * @lc app=leetcode.cn id=1368 lang=cpp
 *
 * [1368] 使网格图至少有一条有效路径的最小代价
 */

// @lc code=start
#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    int minCost(vector<vector<int>>& grid)
    {
        vector<vector<int>> move = {{}, {0, 1}, {0, -1}, {1, 0}, {-1, 0}};

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

            for (int i = 1; i <= 4; i++)
            {
                int nx = x + move[i][0], ny = y + move[i][1];
                int weight = (grid[x][y] == i? 0: 1);
                if (nx >= 0 && ny >= 0 && nx < m && ny < n && distance[x][y] + weight < distance[nx][ny])
                {
                    distance[nx][ny] = distance[x][y] + weight;
                    if (weight == 0)
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

