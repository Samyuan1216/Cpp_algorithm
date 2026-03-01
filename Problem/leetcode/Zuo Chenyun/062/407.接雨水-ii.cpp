/*
 * @lc app=leetcode.cn id=407 lang=cpp
 *
 * [407] 接雨水 II
 */

// @lc code=start
#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    int trapRainWater(vector<vector<int>>& heightMap)
    {
        vector<int> move = {-1, 0, 1, 0, -1};

        int m = heightMap.size(), n = heightMap[0].size();
        priority_queue< vector<int>,
                        vector<vector<int>>,
                        decltype([](vector<int> a, vector<int> b)
                        {
                            return a[2] > b[2];
                        })> pq;
        vector<vector<int>> visited(m, vector<int>(n));
        for (int i = 0; i < m; i++)
        {
            for (int j = 0; j < n; j++)
            {
                if (i == 0 || j == 0 || i == m - 1 || j == n - 1)
                {
                    pq.push(vector<int>{i, j, heightMap[i][j]});
                    visited[i][j] = 1;
                }
            }
        }

        int ans = 0;
        while (pq.empty() == false)
        {
            vector<int> record = pq.top();
            pq.pop();
            
            int r = record[0], c = record[1], w = record[2];
            ans += w - heightMap[r][c];

            for (int i = 0; i < 4; i++)
            {
                int nr = r + move[i], nc = c + move[i + 1];
                if (nr >= 0 && nc >= 0 && nr < m && nc < n && visited[nr][nc] == 0)
                {
                    pq.push(vector<int>{nr, nc, max(heightMap[nr][nc], w)});
                    visited[nr][nc] = 1;
                }
            }
        }

        return ans;
    }
};
// @lc code=end

