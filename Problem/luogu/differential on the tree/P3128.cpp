#include <bits/stdc++.h>

const int MAXN = 50010, LIMIT = 17;
int head[MAXN], next[MAXN << 1], to[MAXN << 1];
int stjump[MAXN][LIMIT], deep[MAXN], num[MAXN];
int n, k, power, cnt = 1;

void add_edge(int u, int v)
{
    next[cnt] = head[u];
    to[cnt] = v;
    head[u] = cnt++;
}

int log2(int n)
{
    int ans = 0;
    while ((1 << ans) <= (n >> 1))
    {
        ans++;
    }

    return ans;
}

void dfs1(int u, int f)
{
    deep[u] = deep[f] + 1;

    stjump[u][0] = f;
    for (int p = 1; p <= power; p++)
    {
        stjump[u][p] = stjump[stjump[u][p - 1]][p - 1];
    }

    for (int ei = head[u], v; ei > 0; ei = next[ei])
    {
        v = to[ei];
        if (v != f)
        {
            dfs1(v, u);
        }
    }
}

int lca(int a, int b)
{
    if (deep[a] < deep[b])
    {
        std::swap(a, b);
    }

    for (int p = power; p >= 0; p--)
    {
        if (deep[stjump[a][p]] >= deep[b])
        {
            a = stjump[a][p];
        }
    }

    if (a == b)
    {
        return a;
    }

    for (int p = power; p >= 0; p--)
    {
        if (stjump[a][p] != stjump[b][p])
        {
            a = stjump[a][p];
            b = stjump[b][p];
        }
    }

    return stjump[a][0];
}

void dfs2(int u, int f)
{
    for (int ei = head[u], v; ei > 0; ei = next[ei])
    {
        v = to[ei];
        if (v != f)
        {
            dfs2(v, u);

            num[u] += num[v];
        }
    }
}

int main()
{
    std::cin >> n >> k;
    for (int i = 1, x, y; i < n; i++)
    {
        std::cin >> x >> y;

        add_edge(x, y);
        add_edge(y, x);
    }

    power = log2(n);
    dfs1(1, 0);

    for (int i = 1, s, t, l, lf; i <= k; i++)
    {
        std::cin >> s >> t;

        l = lca(s, t);
        lf = stjump[l][0];

        num[s]++;
        num[t]++;
        num[l]--;
        num[lf]--;
    }

    dfs2(1, 0);

    int ans = 0;
    for (int i = 1; i <= n; i++)
    {
        ans = std::max(ans, num[i]);
    }

    std::cout << ans << std::endl;
}