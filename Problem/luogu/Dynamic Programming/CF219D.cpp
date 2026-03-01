#include <bits/stdc++.h>

const int MAXN = 200010;
int head[MAXN], next[MAXN << 1], to[MAXN << 1], weight[MAXN << 1];
int reverse[MAXN], dp[MAXN];
int n, cnt = 1;

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

            reverse[u] += reverse[v] + w;
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
            dp[v] = dp[u] + (w == 0? 1: -1);

            dfs2(v, u);
        }
    }
}

int main()
{
    std::cin >> n;
    for (int i = 1, s, t; i < n; i++)
    {
        std::cin >> s >> t;

        add_edge(s, t, 0);
        add_edge(t, s, 1);
    }

    dfs1(1, 0);

    dp[1] = reverse[1];
    dfs2(1, 0);

    int minn = INT32_MAX;
    for (int i = 1; i <= n; i++)
    {
        if (dp[i] < minn)
        {
            minn = dp[i];
        }
    }
    std::cout << minn << std::endl;

    for (int i = 1; i <= n; i++)
    {
        if (dp[i] == minn)
        {
            std::cout << i << " ";
        }
    }
    std::cout << std::endl;
}