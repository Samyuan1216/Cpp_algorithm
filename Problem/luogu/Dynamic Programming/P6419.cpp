#include <bits/stdc++.h>

using ll = long long;

const int MAXN = 500010;
int head[MAXN], next[MAXN << 1], to[MAXN << 1], weight[MAXN << 1];
ll people[MAXN], incost[MAXN], inner1[MAXN], inner2[MAXN], choose[MAXN], outcost[MAXN], outer[MAXN];
int n, k, cnt = 1;

void add_edge(int u, int v, int w)
{
    next[cnt] = head[u];
    to[cnt] = v;
    weight[cnt] = w;
    head[u] = cnt++;
}

void dfs1(int u, int f)
{
    for (int ei = head[u], v, w; ei > 0; ei = next[ei])
    {
        v = to[ei], w = weight[ei];
        if (v != f)
        {
            dfs1(v, u);

            people[u] += people[v];
            if (people[v] > 0)
            {
                incost[u] += incost[v] + (ll)w * 2;

                if (inner1[v] + w > inner1[u])
                {
                    inner2[u] = inner1[u];
                    inner1[u] = inner1[v] + w;
                    choose[u] = v;
                }
                else if (inner1[v] + w > inner2[u])
                {
                    inner2[u] = inner1[v] + w;
                }
            }
        }
    }
}

void dfs2(int u, int f)
{
    for (int ei = head[u], v, w; ei > 0; ei = next[ei])
    {
        v = to[ei], w = weight[ei];
        if (v != f)
        {
            if (k - people[v] > 0)
            {
                if (people[v] == 0)
                {
                    outcost[v] = outcost[u] + incost[u] + (ll)w * 2;
                }
                else
                {
                    outcost[v] = outcost[u] + incost[u] - incost[v];
                }

                if (v != choose[u])
                {
                    outer[v] = std::max(outer[u], inner1[u]) + w;
                }
                else
                {
                    outer[v] = std::max(outer[u], inner2[u]) + w;
                }
            }

            dfs2(v, u);
        }
    }
}

int main()
{
    std::cin >> n >> k;
    for (int i = 1, x, y, z; i < n; i++)
    {
        std::cin >> x >> y >> z;

        add_edge(x, y, z);
        add_edge(y, x, z);
    }

    for (int i = 1, a; i <= k; i++)
    {
        std::cin >> a;

        people[a]++;
    }

    dfs1(1, 0);
    dfs2(1, 0);

    for (int i = 1; i <= n; i++)
    {
        std::cout << incost[i] + outcost[i] - std::max(outer[i], inner1[i]) << std::endl;
    }
}