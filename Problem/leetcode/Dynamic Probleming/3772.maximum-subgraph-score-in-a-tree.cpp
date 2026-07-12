#include <bits/stdc++.h>
using namespace std;

// @leet start
class Solution
{
public:
    vector<int> maxSubgraphScore(int n, vector<vector<int>>& edges, vector<int>& good)
    {
        for (auto &x: good)
        {
            if (x == 0)
            {
                x = -1;
            }
        }

        vector<vector<int>> g(n);
        for (auto &e: edges)
        {
            g[e[0]].push_back(e[1]);
            g[e[1]].push_back(e[0]);
        }

        auto score = good;
        [&](this auto &&dfs, int u, int f) -> void
        {
            for (auto &v: g[u])
            {
                if (v == f)
                {
                    continue;
                }

                dfs(v, u);
                score[u] += std::max(0, score[v]);
            }
        } (0, -1);

        vector<int> ans(n);
        [&](this auto &&dfs, int u, int f, int ps) -> void
        {
            ans[u] = std::max(ps, 0) + score[u];
            for (auto &v: g[u])
            {
                if (v == f)
                {
                    continue;
                }

                dfs(v, u, ans[u] - std::max(0, score[v]));
            }
        } (0, -1, 0);

        return ans;
    }
};
// @leet end
