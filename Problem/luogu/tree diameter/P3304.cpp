#include <bits/stdc++.h>

using ll = long long;

const int MAXN = 200010;
int head[MAXN], next[MAXN << 1], to[MAXN << 1], weight[MAXN << 1];
int last[MAXN];
ll dist[MAXN];
bool path[MAXN];
int n, start, end, common_edges, cnt = 1;
ll diameter;

void add_edge(int u, int v, int w)
{
    next[cnt] = head[u];
    to[cnt] = v;
    weight[cnt] = w;
    head[u] = cnt++;
}

void dfs(int u, int f, int w)
{
    last[u] = f;
    dist[u] = dist[f] + w;

    for (int ei = head[u], v, wi; ei > 0; ei = next[ei])
    {
        v = to[ei], wi = weight[ei];
        if (v != f)
        {
            dfs(v, u, wi);
        }
    }
}

void road()
{
    dfs(1, 0, 0);

    start = 1;
    for (int i = 2; i <= n; i++)
    {
        if (dist[i] > dist[start])
        {
            start = i;
        }
    }

    dfs(start, 0, 0);

    end = 1;
    for (int i = 2; i <= n; i++)
    {
        if (dist[i] > dist[end])
        {
            end = i;
        }
    }

    diameter = dist[end];
}

ll max_distance_except_diameter(int u, int f, int c)
{
    ll ans = c;
    for (int ei = head[u], v, w; ei > 0; ei = next[ei])
    {
        v = to[ei], w = weight[ei];
        if (!path[v] && v != f)
        {
            ans = std::max(ans, max_distance_except_diameter(v, u, c + w));
        }
    }

    return ans;
}

int main()
{
    std::cin >> n;
    for (int i = 1, u, v, w; i < n; i++)
    {
        std::cin >> u >> v >> w;

        add_edge(u, v, w);
        add_edge(v, u, w);
    }

    road();

    std::cout << diameter << std::endl;

    for (int i = end; i != 0; i = last[i])
    {
        path[i] = true;
    }

    int l = start, r = end;
    ll max_dist;
    for (int i = last[end]; i != 0; i = last[i])
    {
        max_dist = max_distance_except_diameter(i, 0, 0);
        if (max_dist == diameter - dist[i])
        {
            r = i;
        }

        if (max_dist == dist[i] && l == start)
        {
            l = i;
        }
    }

    if (l != r)
    {
        common_edges = 1;
        for (int i = last[r]; i != l; i = last[i])
        {
            common_edges++;
        }
    }

    std::cout << common_edges << std::endl;
}