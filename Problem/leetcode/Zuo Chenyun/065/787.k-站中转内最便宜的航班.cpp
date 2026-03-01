/*
 * @lc app=leetcode.cn id=787 lang=cpp
 *
 * [787] K 站中转内最便宜的航班
 */

// @lc code=start
#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    int findCheapestPrice(int n, vector<vector<int>>& flights, int src, int dst, int k)
    {
        vector<int> cur(n, INT_MAX);
        cur[src] = 0;

        for (int i = 0; i <= k; i++)
        {
            vector<int> next(cur);
            for (auto &edge: flights)
            {
                if (cur[edge[0]] != INT_MAX)
                {
                    next[edge[1]] = min(next[edge[1]], cur[edge[0]] + edge[2]);
                }
            }

            cur = next;
        }

        return (cur[dst] == INT_MAX? -1: cur[dst]);
    }
};
// @lc code=end

