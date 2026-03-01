#include <bits/stdc++.h>

const int MAXN = 50010;
int head[MAXN], next[MAXN << 1], to[MAXN << 1];
int size[MAXN], maxsub[MAXN], ans[2];
int n, m, minmaxsub = INT32_MAX, cnt = 1;

void add_edge(int u, int v)
{
    next[cnt] = head[u];
    to[cnt] = v;
    head[u] = cnt++;
}

void dfs(int u, int f)
{
    size[u] = 1;

    for (int ei = head[u], v; ei > 0; ei = next[ei])
    {
        v = to[ei];
        if (v != f)
        {
            dfs(v, u);
            size[u] += size[v];
            maxsub[u] = std::max(maxsub[u], size[v]);
        }
    }

    maxsub[u] = std::max(maxsub[u], n - size[u]);

    // 1
    // minmaxsub = std::min(minmaxsub, maxsub[u]);
}

int main()
{
    std::cin >> n;
    for (int i = 1, u, v; i < n; i++)
    {
        std::cin >> u >> v;

        add_edge(u, v);
        add_edge(v, u);
    }

    dfs(1, 0);

    // 2
    for (int i = 1; i <= n && m < 2; i++)
    {
        if (maxsub[i] <= n / 2)
        {
            ans[m++] = i;
        }
    }

    // 1
    // for (int i = 1; i <= n; i++)
    // {
    //     if (maxsub[i] == minmaxsub)
    //     {
    //         ans[m++] = i;
    //     }
    // }

    for (int i = 0; i < m; i++)
    {
        std::cout << ans[i] << " \n"[i == m - 1];
    }
}