// @leet start
#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    vector<vector<int>> criticalConnections(int n, vector<vector<int>>& connections)
    {
        int m = std::ssize(connections), cntg = 0;
        std::vector<int> head(n, -1), to(m << 1), next(m << 1);

        auto add_edge = [&](int u, int v) -> void
        {
            next[cntg] = head[u];
            to[cntg] = v;
            head[u] = cntg++;
        };

        for (auto &e: connections)
        {
            add_edge(e[0], e[1]);
            add_edge(e[1], e[0]);
        }

        std::vector<int> dfn(n, -1), low(n);
        std::vector<std::vector<int>> ans;
        int cntd = 0;

        [&](this auto &&dfs, int u, int pre) -> void
        {
            dfn[u] = low[u] = cntd++;
            for (int ei = head[u], v; ei != -1; ei = next[ei])
            {
                if ((ei ^ 1) == pre)
                {
                    continue;
                }

                v = to[ei];
                if (dfn[v] == -1)
                {
                    dfs(v, ei);

                    low[u] = std::min(low[u], low[v]);
                    if (low[v] > dfn[u])
                    {
                        ans.push_back(connections[ei >> 1]);
                    }
                }
                else
                {
                    low[u] = std::min(low[u], dfn[v]);
                }
            }
        } (0, -1);

        return ans;
    }
};
// @leet end
