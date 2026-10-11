#include <bits/stdc++.h>
using namespace std;

using i64 = long long;

struct VBCC
{
    const std::vector<std::vector<std::array<int, 2>>> &g;
    std::vector<int> dfn, low, belong;
    std::vector<std::vector<int>> vbcc;
    std::vector<bool> cut;
    std::stack<int> esta, vsta;
    int cnt = 0;

    VBCC(const std::vector<std::vector<std::array<int, 2>>> &adj, int m): g(adj), dfn(std::ssize(adj), -1), low(std::ssize(adj)), belong(m), cut(std::ssize(adj))
    {
        for (int i = 0; i < std::ssize(g); ++i)
        {
            if (dfn[i] != -1)
            {
                continue;
            }

            if (std::ssize(g[i]) == 0)
            {
                vbcc.push_back({});
                vbcc.back().push_back(i);

                continue;
            }

            dfs(i, -1, true);
        }
    }

    void dfs(int u, int pre, bool root)
    {
        dfn[u] = low[u] = cnt++;
        vsta.push(u);

        int son = 0;
        for (auto &[v, id]: g[u])
        {
            if (id == pre)
            {
                continue;
            }

            if (dfn[v] == -1)
            {
                ++son;
                esta.push(id);

                dfs(v, id, false);

                low[u] = std::min(low[u], low[v]);
                if (int t; low[v] >= dfn[u])
                {
                    if (!root || son >= 2)
                    {
                        cut[u] = true;
                    }

                    do
                    {
                        t = esta.top();
                        esta.pop();

                        belong[t] = std::ssize(vbcc);
                    } while (t != id);
                    

                    vbcc.push_back({});
                    vbcc.back().push_back(u);

                    do
                    {
                        t = vsta.top();
                        vsta.pop();

                        vbcc.back().push_back(t);
                    } while (t != v);
                }
            }
            else if (dfn[v] < dfn[u])
            {
                esta.push(id);
                low[u] = std::min(low[u], dfn[v]);
            }
        }
    }
};

// @leet start
class Solution
{
public:
    long long minimumCost(vector<int>& cost, vector<vector<int>>& roads)
    {
        
    }
};
// @leet end
