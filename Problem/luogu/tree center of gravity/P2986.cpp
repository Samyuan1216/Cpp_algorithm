#include <bits/stdc++.h>

using ll = long long;

const int MAXN = 100010;
int head[MAXN], next[MAXN << 1], to[MAXN << 1], weight[MAXN << 1];
int cow[MAXN], size[MAXN], maxsub[MAXN], path[MAXN];
int n, sum, center, cnt = 1;
ll ans;

void add_edge(int u, int v, int w)
{
    next[cnt] = head[u];
    to[cnt] = v;
    weight[cnt] = w;
    head[u] = cnt++;
}

void find_center(int u, int f)
{
    size[u] = cow[u];

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

    maxsub[u] = std::max(maxsub[u], sum - size[u]);
}

void find_path(int u, int f)
{
    for (int ei = head[u], v, w; ei > 0; ei = next[ei])
    {
        v = to[ei], w = weight[ei];
        if (v != f)
        {
            path[v] = path[u] + w;
            find_path(v, u);
        }
    }
}

int main()
{
    std::cin >> n;
    for (int i = 1; i <= n; i++)
    {
        std::cin >> cow[i];

        sum += cow[i];
    }

    for (int i = 1, a, b, l; i < n; i++)
    {
        std::cin >> a >> b >> l;

        add_edge(a, b, l);
        add_edge(b, a, l);
    }

    find_center(1, 0);
    
    for (int i = 1; i <= n; i++)
    {
        if (maxsub[i] <= sum / 2)
        {
            center = i;
            break;
        }
    }

    find_path(center, 0);

    for (int i = 1; i <= n; i++)
    {
        ans += (ll)cow[i] * path[i];
    }

    std::cout << ans << std::endl;
}