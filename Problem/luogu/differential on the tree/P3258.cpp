#include <bits/stdc++.h>

const int MAXN = 300010;
int ehead[MAXN], enext[MAXN << 1], eto[MAXN << 1];
int qhead[MAXN], qnext[MAXN << 1], qto[MAXN << 1], qindex[MAXN << 1];
int travel[MAXN], num[MAXN], father[MAXN], father_node[MAXN], ans[MAXN];
bool visited[MAXN];
int n, ecnt, qcnt;

void build()
{
    ecnt = qcnt = 1;

    for (int i = 1; i <= n; i++)
    {
        father[i] = i;
    }
}

void add_query(int u, int v, int i)
{
    qnext[qcnt] = qhead[u];
    qto[qcnt] = v;
    qindex[qcnt] = i;
    qhead[u] = qcnt++;
}

void add_edge(int u, int v)
{
    enext[ecnt] = ehead[u];
    eto[ecnt] = v;
    ehead[u] = ecnt++;
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

int main()
{
    std::cin >> n;
    build();

    for (int i = 1; i <= n; i++)
    {
        std::cin >> travel[i];
    }

    for (int i = 1, u, v; i < n; i++)
    {
        u = travel[i], v = travel[i + 1];
        add_query(u, v, i);
        add_query(v, u, i);
    }

    for (int i = 1, x, y; i < n; i++)
    {
        std::cin >> x >> y;

        add_edge(x, y);
        add_edge(y, x);
    }

    tarjan(1, 0);

    for (int i = 1, u, v, l, lf; i < n; i++)
    {
        u = travel[i], v = travel[i + 1], l = ans[i], lf = father_node[l];

        num[u]++;
        num[v]++;
        num[l]--;
        num[lf]--;
    }

    dfs(1, 0);

    for (int i = 2; i <= n; i++)
    {
        num[travel[i]]--;
    }

    for (int i = 1; i <= n; i++)
    {
        std::cout << num[i] << std::endl;
    }
}