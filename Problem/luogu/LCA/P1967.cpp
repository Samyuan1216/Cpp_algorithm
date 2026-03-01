#include <bits/stdc++.h>

using vi = std::vector<int>;
using vvi = std::vector<vi>;

const int MAXN = 10010, MAXM = 50010, LIMIT = 21;
int head[MAXN], next[MAXN << 1], to[MAXN << 1] , weight[MAXN << 1];
int stjump[MAXN][LIMIT], stmin[MAXN][LIMIT], deep[MAXN];
int father[MAXN];
vvi edges(MAXM, vi(3));
bool visited[MAXN];
int n, m, q, power, cnt = 1;

int log2(int n)
{
    int ans = 0;
    while ((1 << ans) <= (n >> 1))
    {
        ans++;
    }

    return ans;
}

void build()
{
    for (int i = 1; i <= n; i++)
    {
        father[i] = i;
    }

    power = log2(n);
}

int find(int i)
{
    if (i != father[i])
    {
        father[i] = find(father[i]);
    }

    return father[i];
}

void add_edge(int u, int v, int w)
{
    next[cnt] = head[u];
    to[cnt] = v;
    weight[cnt] = w;
    head[u] = cnt++;
}

void kruskal()
{
    std::sort(edges.begin(), edges.begin() + m, [](vi &a, vi &b)
    {
        return a[2] > b[2];
    });

    for (int i = 0, a, b, c, fa, fb; i < m; i++)
    {
        a = edges[i][0], b = edges[i][1], c = edges[i][2];
        fa = find(a), fb = find(b);

        if (fa != fb)
        {
            father[fa] = fb;

            add_edge(a, b, c);
            add_edge(b, a, c);
        }
    }
}

void dfs(int u, int w, int f)
{
    visited[u] = true;
    if (f == 0)
    {
        deep[u] = 1;
        stjump[u][0] = u;
        stmin[u][0] = INT32_MAX;
    }
    else
    {
        deep[u] = deep[f] + 1;
        stjump[u][0] = f;
        stmin[u][0] = w;
    }

    for (int p = 1; p <= power; p++)
    {
        stjump[u][p] = stjump[stjump[u][p - 1]][p - 1];
        stmin[u][p] = std::min(stmin[u][p - 1], stmin[stjump[u][p - 1]][p - 1]);
    }

    for (int ei = head[u], v, wi; ei > 0; ei = next[ei])
    {
        v = to[ei], wi = weight[ei];
        if (!visited[v])
        {
            dfs(v, wi, u);
        }
    }
}

int lca(int a, int b)
{
    if (deep[a] < deep[b])
    {
        std::swap(a, b);
    }

    int ans = INT32_MAX;
    for (int p = power; p >= 0; p--)
    {
        if (deep[stjump[a][p]] >= deep[b])
        {
            ans = std::min(ans, stmin[a][p]);
            a = stjump[a][p];
        }
    }

    if (a == b)
    {
        return ans;
    }

    for (int p = power; p >= 0; p--)
    {
        if (stjump[a][p] != stjump[b][p])
        {
            ans = std::min(ans, std::min(stmin[a][p], stmin[b][p]));

            a = stjump[a][p];
            b = stjump[b][p];
        }
    }

    return std::min(ans, std::min(stmin[a][0], stmin[b][0]));
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::cin >> n >> m;
    for (int i = 0; i < m; i++)
    {
        std::cin >> edges[i][0] >> edges[i][1] >> edges[i][2];
    }

    build();
    kruskal();

    for (int i = 1; i <= n; i++)
    {
        if (!visited[i])
        {
            dfs(i, 0, 0);
        }
    }

    std::cin >> q;
    for (int i = 0, x, y; i < q; i++)
    {
        std::cin >> x >> y;
        if (find(x) != find(y))
        {
            std::cout << -1 << std::endl;
        }
        else
        {
            std::cout << lca(x, y) << std::endl;
        }
    }
}