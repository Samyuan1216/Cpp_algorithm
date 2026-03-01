#include <bits/stdc++.h>

const int MAXN = 500010;
int head[MAXN], next[MAXN << 1], to[MAXN << 1];
int dist[MAXN], last[MAXN], ans[MAXN];
bool path[MAXN];
int n, start, end, diameter, cnt = 1;

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
        if (dist[i] >= dist[start])
        {
            start = i;
        }
    }

    dfs(start, 0, 0);

    end = 1;
    for (int i = 2; i <= n; i++)
    {
        if (dist[i] >= dist[end])
        {
            end = i;
        }
    }

    diameter = dist[end];
}

void dfs_ans(int u, int f, int p)
{
    ans[u] = p;

    for (int ei = head[u], v; ei > 0; ei = next[ei])
    {
        v = to[ei];
        if (!path[v] && v != f)
        {
            dfs_ans(v, u, p);
        }
    }
}

void distance()
{
    for (int i = end; i != 0; i = last[i])
    {
        path[i] = true;
    }

    for (int i = end, d = 0, p; i != 0; i = last[i], d++)
    {
        if (d * 2 == diameter)
        {
            p = std::max(start, end);
        }
        else if (d * 2 < diameter)
        {
            p = start;
        }
        else
        {
            p = end;
        }

        dfs_ans(i, 0, p);
    }
}

int main()
{
    std::cin >> n;
    for (int i = 1, a, b; i < n; i++)
    {
        std::cin >> a >> b;

        add_edge(a, b);
        add_edge(b, a);
    }

    road();
    distance();

    for (int i = 1; i <= n; i++)
    {
        std::cout << ans[i] << std::endl;
    }
}