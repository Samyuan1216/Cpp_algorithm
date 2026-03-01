#include <bits/stdc++.h>

using ll = long long;

const int MAXN = 500010, LIMIT = 20;
int st[MAXN][LIMIT], deep[MAXN];
int head[MAXN], next[MAXN << 1], to[MAXN << 1];
int n, m, power, cnt = 1;
ll cost;

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

void dfs(int u, int f)
{
    deep[u] = deep[f] + 1;

    st[u][0] = f;
    for (int p = 1; p <= power; p++)
    {
        st[u][p] = st[st[u][p - 1]][p - 1];
    }

    for (int ei = head[u], v; ei > 0; ei = next[ei])
    {
        v = to[ei];
        if (v != f)
        {
            dfs(v, u);
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
        if (deep[st[a][p]] >= deep[b])
        {
            a = st[a][p];
        }
    }

    if (a == b)
    {
        return a;
    }

    for (int p = power; p >= 0; p--)
    {
        if (st[a][p] != st[b][p])
        {
            a = st[a][p];
            b = st[b][p];
        }
    }

    return st[a][0];
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    std::cin >> n >> m;
    for (int i = 1, a, b; i < n; i++)
    {
        std::cin >> a >> b;
        add_edge(a, b);
        add_edge(b, a);
    }

    power = log2(n);
    dfs(1, 0);

    for (int i = 1, x, y, z, h1, h2, h3, high, low; i <= m; i++)
    {
        std::cin >> x >> y >> z;
        h1 = lca(x, y);
        h2 = lca(x, z);
        h3 = lca(y, z);

        high = (h1 != h2? (deep[h1] < deep[h2]? h1: h2): h1);
        low = (h1 != h2? (deep[h1] > deep[h2]? h1: h2): h3);

        cost = (ll)deep[x] + deep[y] + deep[z] - deep[low] - 2 * deep[high];
        std::cout << low << " " << cost << std::endl;
    }
}

        