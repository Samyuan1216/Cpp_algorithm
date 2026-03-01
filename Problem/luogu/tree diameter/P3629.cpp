#include <bits/stdc++.h>

const int MAXN = 100010;
int head[MAXN], next[MAXN << 1], to[MAXN << 1];
int dist[MAXN], last[MAXN];
bool path[MAXN];
int n, k, start, end, diameter1, diameter2, cnt = 1;

void add_edge(int u, int v)
{
    next[cnt] = head[u];
    to[cnt] = v;
    head[u] = cnt++;
}

void dfs(int u, int f, int w)
{
    last[u] = f;
    dist[u] = dist[f] + w;

    for (int ei = head[u], v; ei > 0; ei = next[ei])
    {
        v = to[ei];
        if (v != f)
        {
            dfs(v, u, 1);
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

    diameter1 = dist[end];
}

void dp(int u, int f)
{
    for (int ei = head[u], v; ei > 0; ei = next[ei])
    {
        v = to[ei];
        if (v != f)
        {
            dp(v, u);
        }
    }

    for (int ei = head[u], v, w; ei > 0; ei = next[ei])
    {
        v = to[ei];
        if (v != f)
        {
            w = (path[u] && path[v]? -1: 1);

            diameter2 = std::max(diameter2, dist[u] + dist[v] + w);
            dist[u] = std::max(dist[u], dist[v] + w);
        }
    }
}

int main()
{
    std::cin >> n >> k;
    for (int i = 1, a, b; i < n; i++)
    {
        std::cin >> a >> b;

        add_edge(a, b);
        add_edge(b, a);
    }

    road();

    if (k == 1)
    {
        std::cout << 2 * (n - 1) - diameter1 + 1 << std::endl;
    }
    else
    {
        for (int i = end; i != 0; i = last[i])
        {
            path[i] = true;
        }

        std::fill(dist + 1, dist + n + 1, 0);

        dp(1, 0);
        std::cout << 2 * (n - 1) - diameter1 - diameter2 + 2 << std::endl;
    }
}