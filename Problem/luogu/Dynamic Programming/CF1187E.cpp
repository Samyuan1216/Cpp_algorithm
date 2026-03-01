#include <bits/stdc++.h>

using ll = long long;

const int MAXN = 200010;
int head[MAXN], next[MAXN << 1], to[MAXN << 1];
int size[MAXN], dp[MAXN];
int n, cnt = 1;

void add_edge(int u, int v)
{
    next[cnt] = head[u];
    to[cnt] = v;
    head[u] = cnt++;
}

void dfs1(int u, int f)
{
    size[u] = 1;
    for (int ei = head[u], v; ei > 0; ei = next[ei])
    {
        v = to[ei];
        if (v != f)
        {
            dfs1(v, u);

            size[u] += size[v];
            dp[u] += dp[v];
        }
    }

    dp[u] += size[u];
}

void dfs2(int u, int f)
{
    for (int ei = head[u], v; ei > 0; ei = next[ei])
    {
        v = to[ei];
        if (v != f)
        {
            dp[v] = dp[u] - size[v] + (n - size[v]);

            dfs2(v, u);
        }
    }
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

    dfs1(1, 0);
    dfs2(1, 0);

    ll ans = 0;
    for (int i = 1; i <= n; i++)
    {
        if (dp[i] > ans)
        {
            ans = dp[i];
        }
    }

    std::cout << ans << std::endl;
}