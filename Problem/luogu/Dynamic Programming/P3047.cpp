#include <bits/stdc++.h>

const int MAXN = 100010, MAXK = 21;
int head[MAXN], next[MAXN << 1], to[MAXN << 1];
int sum[MAXN][MAXK], dp[MAXN][MAXK];
int n, k, cnt = 1;

void add_edge(int u, int v)
{
    next[cnt] = head[u];
    to[cnt] = v;
    head[u] = cnt++;
}

void dfs1(int u, int f)
{
    for (int ei = head[u], v; ei > 0; ei = next[ei])
    {
        v = to[ei];
        if (v != f)
        {
            dfs1(v, u);

            for (int i = 1; i <= k; i++)
            {
                sum[u][i] += sum[v][i - 1];
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
            dp[v][0] = sum[v][0];
            dp[v][1] = sum[v][1] + dp[u][0];
            for (int i = 2; i <= k; i++)
            {
                dp[v][i] = sum[v][i] + dp[u][i - 1] - sum[v][i - 2];
            }

            dfs2(v, u);
        }
    }
}

int main()
{
    std::cin >> n >> k;
    for (int i = 1, u, v; i < n; i++)
    {
        std::cin >> u >> v;

        add_edge(u, v);
        add_edge(v, u);
    }

    for (int i = 1; i <= n; i++)
    {
        std::cin >> sum[i][0];
    }

    dfs1(1, 0);

    for (int i = 0; i <= k; i++)
    {
        dp[1][i] = sum[1][i];
    }

    dfs2(1, 0);

    for (int i = 1, ans; i <= n; i++)
    {
        ans = 0;
        for (int j = 0; j <= k; j++)
        {
            ans += dp[i][j];
        }

        std::cout << ans << std::endl;
    }
}