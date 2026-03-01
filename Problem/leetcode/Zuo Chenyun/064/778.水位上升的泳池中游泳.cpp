/*
 * @lc app=leetcode.cn id=778 lang=cpp
 *
 * [778] 水位上升的泳池中游泳
 */

// @lc code=start
#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    int swimInWater(vector<vector<int>>& grid)
    {
        vector<int> moved{-1, 0, 1, 0, -1};

        int n = grid.size();
        vector<vector<int>> distance(n, vector<int>(n, INT_MAX));
        distance[0][0] = grid[0][0];

        priority_queue< vector<int>,
                        vector<vector<int>>,
                        decltype([](vector<int> &a, vector<int> &b)
                        {
                            return a[2] > b[2];
                        })> heap;
        heap.push(vector<int>{0, 0, distance[0][0]});

        vector<vector<int>> visited(n, vector<int>(n));
        while (heap.empty() == false)
        {
            int x = heap.top()[0], y = heap.top()[1], c = heap.top()[2];
            heap.pop();

            if (x == n - 1 && y == n - 1)
            {
                return c;
            }

            visited[x][y] = 1;
            for (int i = 0; i < 4; i++)
            {
                int nx = x + moved[i], ny = y + moved[i + 1];
                if (nx >= 0 && ny >= 0 && nx < n && ny < n && visited[nx][ny] == 0)
                {
                    int nc = max(c, grid[nx][ny]);
                    if (nc < distance[nx][ny])
                    {
                        distance[nx][ny] = nc;
                        heap.push(vector<int>{nx, ny, nc});
                    }
                }
            }
        }

        return -1;
    }
};
// @lc code=end

