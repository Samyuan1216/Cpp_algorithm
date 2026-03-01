/*
 * @lc app=leetcode.cn id=1631 lang=cpp
 *
 * [1631] 最小体力消耗路径
 */

// @lc code=start
#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    int minimumEffortPath(vector<vector<int>>& heights)
    {
        vector<int> move{-1, 0, 1, 0, -1};

        int n = heights.size(), m = heights[0].size();
        vector<vector<int>> distance(n, vector<int>(m, INT_MAX));
        distance[0][0] = 0;

        priority_queue< vector<int>,
                        vector<vector<int>>,
                        decltype([](vector<int> a, vector<int> b)
                        {
                            return a[2] > b[2];
                        })> heap;
        heap.push(vector<int>{0, 0, 0});

        vector<vector<int>> visited(n, vector<int>(m));
        while (heap.empty() == false)
        {
            int x = heap.top()[0], y = heap.top()[1], c = heap.top()[2];
            heap.pop();

            if (x == n - 1 && y == m - 1)
            {
                return c;
            }

            visited[x][y] = 1;
            for (int i = 0; i < 4; i++)
            {
                int nx = x + move[i], ny = y + move[i + 1];
                if (nx >= 0 && ny >= 0 && nx < n && ny < m && visited[nx][ny] == 0)
                {
                    int nc = max(c, abs(heights[x][y] - heights[nx][ny]));
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

