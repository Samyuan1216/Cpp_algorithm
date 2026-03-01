/*
 * @lc app=leetcode.cn id=2646 lang=cpp
 *
 * [2646] 最小化旅行的价格总和
 */

// @lc code=start
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 51, MAXM = 110;
int ehead[MAXN], enext[MAXN << 1], eto[MAXN << 1];
int qhead[MAXN], qnext[MAXM << 1], qto[MAXM << 1], qindex[MAXM << 1];
int price[MAXN], num[MAXN], father[MAXN], father_node[MAXN], ans[MAXM];
bool visited[MAXN];
int ecnt, qcnt, yes, no;

class Solution
{
public:
    int minimumTotalPrice(int n, vector<vector<int>>& edges, vector<int>& pr, vector<vector<int>>& trips)
    {
        build(n);

        for (int i = 0; i < n; i++)
        {
            price[i + 1] = pr[i];
        }

        for (auto &edge: edges)
        {
            add_edge(edge[0] + 1, edge[1] + 1);
            add_edge(edge[1] + 1, edge[0] + 1);
        }

        int m = trips.size();
        for (int i = 0; i < m; i++)
        {
            add_query(trips[i][0] + 1, trips[i][1] + 1, i + 1);
            add_query(trips[i][1] + 1, trips[i][0] + 1, i + 1);
        }

        tarjan(1, 0);

        for (int i = 0, u, v, l, lf; i < m; i++)
        {
            u = trips[i][0] + 1, v = trips[i][1] + 1;
            l = ans[i + 1], lf = father_node[l];

            num[u]++;
            num[v]++;
            num[l]--;
            num[lf]--;
        }

        dfs(1, 0);
        dp(1, 0);

        return min(yes, no);
    }

    void build(int n)
    {
        fill(num + 1, num + n + 1, 0);
        fill(ehead + 1, ehead + n + 1, 0);
        fill(qhead + 1, qhead + n + 1, 0);
        fill(visited + 1, visited + n + 1, false);

        ecnt = qcnt = 1;

        for (int i = 1; i <= n; i++)
        {
            father[i] = i;
        }
    }

    void add_edge(int u, int v)
    {
        enext[ecnt] = ehead[u];
        eto[ecnt] = v;
        ehead[u] = ecnt++;
    }

    void add_query(int u, int v, int i)
    {
        qnext[qcnt] = qhead[u];
        qto[qcnt] = v;
        qindex[qcnt] = i;
        qhead[u] = qcnt++;
    }

    int find(int i)
    {
        if (i != father[i])
        {
            father[i] = find(father[i]);
        }

        return father[i];
    }

    void tarjan(int u, int f)
    {
        visited[u] = true;
        for (int ei = ehead[u], v; ei > 0; ei = enext[ei])
        {
            v = eto[ei];
            if (v != f)
            {
                tarjan(v, u);
            }
        }

        for (int ei = qhead[u], v, qi; ei > 0; ei = qnext[ei])
        {
            v = qto[ei], qi = qindex[ei];
            if (visited[v])
            {
                ans[qi] = find(v);
            }
        }

        father[u] = father_node[u] = f;
    }

    void dfs(int u, int f)
    {
        for (int ei = ehead[u], v; ei > 0; ei = enext[ei])
        {
            v = eto[ei];
            if (v != f)
            {
                dfs(v, u);

                num[u] += num[v];
            }
        }
    }

    void dp(int u, int f)
    {
        int y = (price[u] / 2) * num[u], n = price[u] * num[u];
        for (int ei = ehead[u], v; ei > 0; ei = enext[ei])
        {
            v = eto[ei];
            if (v != f)
            {
                dp(v, u);

                y += no;
                n += min(yes, no);
            }
        }

        yes = y;
        no = n;
    }
};
// @lc code=end

