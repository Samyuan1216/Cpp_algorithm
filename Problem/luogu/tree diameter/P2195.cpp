#include <bits/stdc++.h>

const int MAXN = 300010;
int head[MAXN], next[MAXN << 1], to[MAXN << 1];
int dist[MAXN], diameter[MAXN], father[MAXN];
int n, m, q, cnt;

void build(int n)
{
    cnt = 1;
    
    for (int i = 1; i <= n; i++)
    {
        father[i] = i;
    }
}

void add_edge(int u, int v)
{
    next[cnt] = head[u];
    to[cnt] = v;
    head[u] = cnt++;
}

int find(int i)
{
    if (i != father[i])
    {
        father[i] = find(father[i]);
    }

    return father[i];
}

void dfs(int u, int f)
{
    for (int ei = head[u], v; ei > 0; ei = next[ei])
    {
        v = to[ei];
        if (v != f)
        {
            dfs(v, u);
        }
    }

    for (int ei = head[u], v; ei > 0; ei = next[ei])
    {
        v = to[ei];
        if (v != f)
        {
            diameter[u] = std::max(diameter[u], std::max(diameter[v], dist[u] + dist[v] + 1));
            dist[u] = std::max(dist[u], dist[v] + 1);
        }
    }
}

int main()
{
    std::cin >> n >> m >> q;
    build(n);

    for (int i = 1, x, y; i <= m; i++)
    {
        std::cin >> x >> y;

        add_edge(x, y);
        add_edge(y, x);

        x = find(x), y = find(y);
        father[x] = y;
    }

    for (int i = 1; i <= n; i++)
    {
        if (i == father[i])
        {
            dfs(i, 0);
        }
    }

    for (int i = 1, op, x, y; i <= q; i++)
    {
        std::cin >> op;
        if (op == 1)
        {
            std::cin >> x;

            x = find(x);
            std::cout << diameter[x] << std::endl;
        }
        else
        {
            std::cin >> x >> y;
            
            x = find(x), y = find(y);
            if (x != y)
            {
                father[x] = y;
                diameter[y] = std::max((diameter[x] + 1) / 2 + (diameter[y] + 1) / 2 + 1, std::max(diameter[x], diameter[y]));
            }
        }
    }
}