#include <bits/stdc++.h>

const int MAXN = 400010;
int head[MAXN], next[MAXN << 1], to[MAXN << 1];
int size[MAXN], maxsub[MAXN], inner1[MAXN], inner2[MAXN], choose[MAXN], outer[MAXN];
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
            if (size[v] > size[maxsub[u]])
            {
                maxsub[u] = v;
            }

            int innersize = (size[v] <= n / 2? size[v]: inner1[v]);
            if (inner1[u] < innersize)
            {
                inner2[u] = inner1[u];
                inner1[u] = innersize;
                choose[u] = v;
            }
            else if (inner2[u] < innersize)
            {
                inner2[u] = innersize;
            }
        }
    }
}

void dfs2(int u, int f)
{
    for (int ei = head[u], v; ei > 0; ei = next[ei])
    {
        v = to[ei];
        if (v != f)
        {
            if (n - size[v] <= n / 2)
            {
                outer[v] = n - size[v];
            }
            else if (v != choose[u])
            {
                outer[v] = std::max(outer[u], inner1[u]);
            }
            else
            {
                outer[v] = std::max(outer[u], inner2[u]);
            }

            dfs2(v, u);
        }
    }
}

bool check(int i)
{
    if (size[maxsub[i]] > n / 2)
    {
        return size[maxsub[i]] - inner1[maxsub[i]] <= n / 2;
    }

    if (n - size[i] > n / 2)
    {
        return n - size[i] - outer[i] <= n / 2;
    }

    return true;
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

    for (int i = 1, status; i <= n; i++)
    {
        status = (check(i)? 1: 0);

        std::cout << status << " \n"[i == n];
    }
}