#include <bits/stdc++.h>

const int MAXN = 300010;
int ehead[MAXN], enext[MAXN << 1], eto[MAXN << 1], eweight[MAXN << 1];
int qhead[MAXN], qnext[MAXN << 1], qto[MAXN << 1], qindex[MAXN << 1];
int num[MAXN], father[MAXN], quesu[MAXN], quesv[MAXN], lca[MAXN], distance[MAXN], cost[MAXN];
bool visited[MAXN];
int n, m, atleast, beyond, maxcost, ecnt, qcnt;

void build()
{
    ecnt = qcnt = 1;

    for (int i = 1; i <= n; i++)
    {
        father[i] = i;
    }
}

void add_edge(int u, int v, int w)
{
    enext[ecnt] = ehead[u];
    eto[ecnt] = v;
    eweight[ecnt] = w;
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

void tarjan(int u, int f, int w)
{
    visited[u] = true;
    distance[u] = distance[f] + w;

    for (int ei = ehead[u], v, wi; ei > 0; ei = enext[ei])
    {
        v = eto[ei], wi = eweight[ei];
        if (v != f)
        {
            tarjan(v, u, wi);
        }
    }

    for (int ei = qhead[u], v, qi; ei > 0; ei = qnext[ei])
    {
        v = qto[ei], qi = qindex[ei];
        if (visited[v])
        {
            lca[qi] = find(v);
            cost[qi] = distance[u] + distance[v] - 2 * distance[lca[qi]];
            maxcost = std::max(maxcost, cost[qi]);
        }
    }

    father[u] = f;
}

bool dfs(int u, int f, int w)
{
    for (int ei = ehead[u], v, wi; ei > 0; ei = enext[ei])
    {
        v = eto[ei], wi = eweight[ei];
        if (v != f)
        {
            if (dfs(v, u, wi))
            {
                return true;
            }

            num[u] += num[v];
        }
    }

    return (num[u] == beyond && w >= atleast);
}

bool check(int limit)
{
    std::fill(num + 1, num + n + 1, 0);

    atleast = maxcost - limit;
    beyond = 0;

    for (int i = 1; i <= m; i++)
    {
        if (cost[i] > limit)
        {
            num[quesu[i]]++;
            num[quesv[i]]++;
            num[lca[i]] -= 2;

            beyond++;
        }
    }

    return (beyond == 0 || dfs(1, 0, 0));
}

int main()
{
    std::cin >> n >> m;
    build();

    for (int i = 1, a, b, t; i < n; i++)
    {
        std::cin >> a >> b >> t;

        add_edge(a, b, t);
        add_edge(b, a, t);
    }

    for (int i = 1, u, v; i <= m; i++)
    {
        std::cin >> u >> v;
        quesu[i] = u, quesv[i] = v;

        add_query(u, v, i);
        add_query(v, u, i);
    }

    tarjan(1, 0, 0);

    int ans = 0, l = 0, r = maxcost, mid;
    while (l <= r)
    {
        mid = l + ((r - l) >> 1);
        if (check(mid))
        {
            ans = mid;
            r = mid - 1;
        }
        else
        {
            l = mid + 1;
        }
    }

    std::cout << ans << std::endl;
}