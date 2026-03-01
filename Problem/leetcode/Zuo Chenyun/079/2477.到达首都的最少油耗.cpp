/*
 * @lc app=leetcode.cn id=2477 lang=cpp
 *
 * [2477] 到达首都的最少油耗
 */

// @lc code=start
#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    long long minimumFuelCost(vector<vector<int>>& roads, int seats)
    {
        int n = roads.size() + 1;
        vector<vector<int>> graph(n, vector<int>());

        for (auto &r: roads)
        {
            graph[r[0]].push_back(r[1]);
            graph[r[1]].push_back(r[0]);
        }

        vector<int> size(n);
        vector<long long> cost(n);

        f(graph, seats, 0, -1, size, cost);

        return cost[0];
    }

    void f(vector<vector<int>> &graph, int seats, int u, int p, vector<int> &size, vector<long long> &cost)
    {
        size[u] = 1;
        for (auto &v: graph[u])
        {
            if (v != p)
            {
                f(graph, seats, v, u, size, cost);

                size[u] += size[v];
                cost[u] += cost[v] + (size[v] + seats - 1) / seats;
            }
        }
    }
};
// @lc code=end

