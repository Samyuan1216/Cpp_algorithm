#include <bits/stdc++.h>

const int MAXN = 100010;
int head[MAXN], next[MAXN << 1], to[MAXN << 1];
int size[MAXN], maxsub[MAXN], centers[2];
int t, n, leaf, leaf_father, cnt;

void build(int n)
{
    cnt = 1;

    std::fill(head + 1, head + n + 1, 0);
}

void add_edge(int u, int v)
{
    next[cnt] = head[u];
    to[cnt] = v;
    head[u] = cnt++;
}

void find_center(int u, int f)
{
    size[u] = 1, maxsub[u] = 0;

    for (int ei = head[u], v; ei > 0; ei = next[ei])
    {
        v = to[ei];
        if (v != f)
        {
            find_center(v, u);

            size[u] += size[v];
            maxsub[u] = std::max(maxsub[u], size[v]);
        }
    }

    maxsub[u] = std::max(maxsub[u], n - size[u]);
}

int center_cnt()
{
    int m = 0;
    for (int i = 1; i <= n && m < 2; i++)
    {
        if (maxsub[i] <= n / 2)
        {
            centers[m++] = i;
        }
    }

    return m;
}

void find_leaf(int u, int f)
{
    for (int ei = head[u], v; ei > 0; ei = next[ei])
    {
        v = to[ei];
        if (v != f)
        {
            find_leaf(v, u);
            return;
        }
    }

    leaf = u;
    leaf_father = f;
}

void solve()
{
    std::cin >> n;
    build(n);

    for (int i = 1, x, y; i < n; i++)
    {
        std::cin >> x >> y;

        add_edge(x, y);
        add_edge(y, x);
    }

    find_center(1, 0);

    if (center_cnt() == 1)
    {
        std::cout << centers[0] << " " << to[head[centers[0]]] << std::endl;
        std::cout << centers[0] << " " << to[head[centers[0]]] << std::endl;
    }
    else
    {
        find_leaf(centers[1], centers[0]);

        std::cout << leaf_father << " " << leaf << std::endl;
        std::cout << centers[0] << " " << leaf << std::endl;
    }
}

int main()
{
    std::cin >> t;
    while (t--)
    {
        solve();
    }
}