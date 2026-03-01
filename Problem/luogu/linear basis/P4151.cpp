#include <bits/stdc++.h>

using ll = long long;
using vi = std::vector<int>;
using vll = std::vector<ll>;

const int MAXN = 50010, MAXM = 200010, BIT = 60;
vi head(MAXN), next(MAXM), to(MAXM);
vll weight(MAXM), basis(BIT + 1), path(MAXN);
bool visited[MAXN];
int n, m, cnt = 1;

void add_edge(int u, int v, ll w)
{
    next[cnt] = head[u];
    to[cnt] = v;
    weight[cnt] = w;
    head[u] = cnt++;
}

bool insert(ll num)
{
    for (int i = BIT; i >= 0; i--)
    {
        if (num >> i == 1)
        {
            if (basis[i] == 0)
            {
                basis[i] = num;
                return true;
            }

            num ^= basis[i];
        }
    }

    return false;
}

void dfs(int u, int f, ll p)
{
    path[u] = p;
    visited[u] = true;

    for (int ei = head[u], v; ei > 0; ei = next[ei])
    {
        v = to[ei];
        if (v != f)
        {
            ll x = p ^ weight[ei];
            if (visited[v])
            {
                insert(x ^ path[v]);
            }
            else
            {
                dfs(v, u, x);
            }
        }
    }
}

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    std::cin >> n >> m;
    for (int i = 1; i <= m; i++)
    {
        int u, v;
        ll w;
        std::cin >> u >> v >> w;

        add_edge(u, v, w);
        add_edge(v, u, w);
    }

    dfs(1, 0, 0);

    ll ans = path[n];
    for (int i = BIT; i >= 0; i--)
    {
        ans = std::max(ans, ans ^ basis[i]);
    }

    std::cout << ans << "\n";
}