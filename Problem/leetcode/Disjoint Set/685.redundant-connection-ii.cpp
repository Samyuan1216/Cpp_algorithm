// @leet start
#include <bits/stdc++.h>
using namespace std;

class DSU
{
    vector<int> father, size;
public:
    DSU(int n): father(n + 1), size(n + 1, 1)
    {
        for (int i = 1; i <= n; i++)
        {
            father[i] = i;
        }
    }

    int find(int i)
    {
        if (i != father[i])
        {
            father[i] = find(father[i]);
        }

        return father[i];
    }

    void merge(int x, int y)
    {
        int fx = find(x), fy = find(y);
        if (fx == fy)
        {
            return;
        }

        if (size[fx] < size[fy])
        {
            std::swap(fx, fy);
        }

        father[fy] = fx;
        size[fx] += size[fy];
    }

    int get_size(int i)
    {
        return size[find(i)];
    }

    bool same(int x, int y)
    {
        return find(x) == find(y);
    }
};

class Solution
{
public:
    vector<int> findRedundantDirectedConnection(vector<vector<int>>& edges)
    {
        int n = edges.size();
        DSU s(n);
        vector<int> parent(n + 1);
        for (int i = 1; i <= n; i++)
        {
            parent[i] = i;
        }

        bool status = false;

        int u = 0, v = 0, pu = 0;
        for (auto &edge: edges)
        {
            if (parent[edge[1]] != edge[1])
            {
                pu = parent[edge[1]], u = edge[0], v = edge[1];
            }
            else
            {
                parent[edge[1]] = edge[0];
                if (!s.same(edge[0], edge[1]))
                {
                    s.merge(edge[0], edge[1]);
                }
                else
                {
                    status = true;
                    if (pu == 0)
                    {
                        u = edge[0], v = edge[1];
                    }
                }
            }
        }

        if (status && pu != 0)
        {
            u = pu;
        }

        return vector<int>{u, v};
    }
};
// @leet end
