/*
 * @lc app=leetcode.cn id=2846 lang=cpp
 *
 * [2846] 边权重均等查询
 */

// @lc code=start
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 10010, MAXM = 20010, MAXW = 26;
int edge_head[MAXN], edge_next[MAXN << 1], edge_to[MAXN << 1], edge_weight[MAXN << 1];
int query_head[MAXN], query_next[MAXM << 1], query_to[MAXM << 1], query_index[MAXM << 1];
int weight_cnt[MAXN][MAXW + 1], father[MAXN], lca[MAXM];
bool visited[MAXN];
int ecnt, qcnt;

class Solution
{
public:
    vector<int> minOperationsQueries(int n, vector<vector<int>>& edges, vector<vector<int>>& queries)
    {
        build(n);

        for (int i = 0; i < n - 1; i++)
        {
            add_edge(edges[i][0], edges[i][1], edges[i][2]);
            add_edge(edges[i][1], edges[i][0], edges[i][2]);
        }

        dfs(0, 0, -1);

        int m = queries.size();
        for (int i = 0; i < m; i++)
        {
            add_query(queries[i][0], queries[i][1], i);
            add_query(queries[i][1], queries[i][0], i);
        }

        tarjan(0, -1);

        vector<int> ans(m);
        for (int i = 0, a, b, c; i < m; i++)
        {
            a = queries[i][0], b = queries[i][1], c = lca[i];

            int allcnt = 0, maxcnt = 0;
            for (int w = 1, wcnt; w <= MAXW; w++)
            {
                wcnt = weight_cnt[a][w] + weight_cnt[b][w] - 2 * weight_cnt[c][w];

                maxcnt = max(maxcnt, wcnt);
                allcnt += wcnt;
            }

            ans[i] = allcnt - maxcnt;
        }

        return ans;
    }

    void build(int n)
    {
        ecnt = qcnt = 1;

        fill(edge_head, edge_head + n, 0);
        fill(query_head, query_head + n, 0);
        fill(visited, visited + n, false);
        
        for (int i = 0; i < n; i++)
        {
            father[i] = i;
        }
    }

    void add_edge(int u, int v, int w)
    {
        edge_next[ecnt] = edge_head[u];
        edge_to[ecnt] = v;
        edge_weight[ecnt] = w;
        edge_head[u] = ecnt++;
    }

    void dfs(int u, int w, int f)
    {
        if (u == 0)
        {
            fill(weight_cnt[u], weight_cnt[u] + MAXW + 1, 0);
        }
        else
        {
            for (int i = 1; i <= MAXW; i++)
            {
                weight_cnt[u][i] = weight_cnt[f][i];
            }
            weight_cnt[u][w]++;
        }

        for (int ei = edge_head[u], v, wi; ei > 0; ei = edge_next[ei])
        {
            v = edge_to[ei], wi = edge_weight[ei];
            if (v != f)
            {
                dfs(v, wi, u);
            }
        }
    }

    void add_query(int u, int v, int i)
    {
        query_next[qcnt] = query_head[u];
        query_to[qcnt] = v;
        query_index[qcnt] = i;
        query_head[u] = qcnt++;
    }

    void tarjan(int u, int f)
    {
        visited[u] = true;
        for (int ei = edge_head[u], v; ei > 0; ei = edge_next[ei])
        {
            v = edge_to[ei];
            if (v != f)
            {
                tarjan(v, u);
            }
        }

        for (int ei = query_head[u], v, wi; ei > 0; ei = query_next[ei])
        {
            v = query_to[ei], wi = query_index[ei];
            if (visited[v])
            {
                lca[wi] = find(v);
            }
        }

        father[u] = f;
    }

    int find(int i)
    {
        if (i != father[i])
        {
            father[i] = find(father[i]);
        }

        return father[i];
    }
};
// @lc code=end

