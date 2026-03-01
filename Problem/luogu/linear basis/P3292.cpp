#include <bits/stdc++.h>

using ll = long long;
using vi = std::vector<int>;
using v2i = std::vector<vi>;
using vll = std::vector<ll>;
using v2ll = std::vector<vll>;

const int MAXN = 200010, LIMIT = 16, BIT = 60;
vi head(MAXN), next(MAXN << 1), to(MAXN << 1), deep(MAXN);
v2i stjump(MAXN, vi(LIMIT)), levels(MAXN, vi(BIT + 1));
vll arr(MAXN), basis(BIT + 1);
v2ll bases(MAXN, vll(BIT + 1));
int n, q, cnt, power;

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
    cnt = 1;
    power = log2(n);
}

void add_edge(int u, int v)
{
    next[cnt] = head[u];
    to[cnt] = v;
    head[u] = cnt++;
}

bool insert_replace(ll curv, int curl, vll &basis, vi &level)
{
    for (int i = BIT; i >= 0; i--)
    {
        if (curv >> i == 1)
        {
            if (basis[i] == 0)
            {
                basis[i] = curv;
                level[i] = curl;

                return true;
            }

            if (curl > level[i])
            {
                std::swap(curv, basis[i]);
                std::swap(curl, level[i]);
            }

            curv ^= basis[i];
        }
    }

    return false;
}

void dfs(int u, int f)
{
    deep[u] = deep[f] + 1;
    stjump[u][0] = f;

    for (int p = 1; p <= power; p++)
    {
        stjump[u][p] = stjump[stjump[u][p - 1]][p - 1];
    }

    for (int i = 0; i <= BIT; i++)
    {
        bases[u][i] = bases[f][i];
        levels[u][i] = levels[f][i];
    }

    insert_replace(arr[u], deep[u], bases[u], levels[u]);

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

ll query(int x, int y)
{
    int l = lca(x, y);
    vll &basisx = bases[x], &basisy = bases[y];
    vi &levelx = levels[x], &levely = levels[y];

    std::fill(basis.begin(), basis.end(), 0);

    for (int i = BIT; i >= 0; i--)
    {
        ll num = basisx[i];
        if (levelx[i] >= deep[l] && num != 0)
        {
            basis[i] = num;
        }
    }

    for (int i = BIT; i >= 0; i--)
    {
        ll num = basisy[i];
        if (levely[i] >= deep[l] && num != 0)
        {
            for (int j = i; j >= 0; j--)
            {
                if (num >> j == 1)
                {
                    if (basis[j] == 0)
                    {
                        basis[j] = num;
                        break;
                    }

                    num ^= basis[j];
                }
            }
        }
    }

    ll ans = 0;
    for (int i = BIT; i >= 0; i--)
    {
        ans = std::max(ans, ans ^ basis[i]);
    }

    return ans;
}

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    std::cin >> n >> q;
    build();

    for (int i = 1; i <= n; i++)
    {
        std::cin >> arr[i];
    }

    for (int i = 1, u, v; i < n; i++)
    {
        std::cin >> u >> v;

        add_edge(u, v);
        add_edge(v, u);
    }

    dfs(1, 0);

    for (int i = 1, x, y; i <= q; i++)
    {
        std::cin >> x >> y;
        std::cout << query(x, y) << "\n";
    }
}