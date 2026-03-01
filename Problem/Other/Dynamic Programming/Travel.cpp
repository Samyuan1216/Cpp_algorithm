#include <bits/stdc++.h>

const int MAXN = 10, MAXS = 59050;
int graph[MAXN][MAXN], dp[MAXN][MAXS], complete[1 << MAXN];
int n, m, maxs, size;

void dfs1(int i, int bit, int s)
{
    if (i == n)
    {
        complete[size++] = s;
    }
    else
    {
        dfs1(i + 1, bit * 3, s + bit);
        dfs1(i + 1, bit * 3, s + 2 * bit);
    }
}

void build()
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            graph[i][j] = INT32_MAX;
        }
    }

    maxs = (int)std::pow(3, n);
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < maxs; j++)
        {
            dp[i][j] = -1;
        }
    }

    size = 0;
    dfs1(0, 1, 0);
}

int dfs2(int i, int s)
{
    if (s == 0)
    {
        return 0;
    }

    if (dp[i][s] != -1)
    {
        return dp[i][s];
    }

    int ans = INT32_MAX;
    for (int j = 0, bit = 1, pre; j < n; j++, bit *= 3)
    {
        if ((s / bit) % 3 > 0)
        {
            pre = dfs2(j, s - bit);
            if (pre != INT32_MAX && graph[j][i] != INT32_MAX)
            {
                ans = std::min(ans, pre + graph[j][i]);
            }
        }
    
    }

    dp[i][s] = ans;
    return ans;
}

int main()
{
    while (std::cin >> n >> m)
    {
        build();

        for (int i = 1, u, v, w; i <= m; i++)
        {
            std::cin >> u >> v >> w;
            u--, v--;

            if (w < graph[u][v])
            {
                graph[u][v] = graph[v][u] = w;
            }
        }

        int ans = INT32_MAX;
        for (int k = 0; k < size; k++)
        {
            for (int i = 0, bit = 1; i < n; i++, bit *= 3)
            {
                ans = std::min(ans, dfs2(i, complete[k] - bit));
            }
        }

        if (ans == INT32_MAX)
        {
            ans = -1;
        }

        std::cout << ans << std::endl;
    }
}