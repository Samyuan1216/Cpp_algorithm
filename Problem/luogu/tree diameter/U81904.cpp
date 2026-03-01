#include <bits/stdc++.h>

// dp
const int MAXN = 500010;
int head[MAXN], next[MAXN << 1], to[MAXN << 1], weight[MAXN << 1];
int dist[MAXN], ans[MAXN];
int n, diameter, cnt = 1;

void add_edge(int u, int v, int w)
{
    next[cnt] = head[u];
    to[cnt] = v;
    weight[cnt] = w;
    head[u] = cnt++;
}

void dp(int u, int f)
{
    for (int ei = head[u], v; ei > 0; ei = next[ei])
    {
        v = to[ei];
        if (v != f)
        {
            dp(v, u);
        }
    }

    for (int ei = head[u], v, w; ei > 0; ei = next[ei])
    {
        v = to[ei], w = weight[ei];
        if (v != f)
        {
            ans[u] = std::max(ans[u], dist[u] + dist[v] + w);
            dist[u] = std::max(dist[u], dist[v] + w);
        }
    }
}

int main()
{
    std::cin >> n;
    for (int i = 1, u, v, w; i < n; i++)
    {
        std::cin >> u >> v >> w;

        add_edge(u, v, w);
        add_edge(v, u, w);
    }

    dp(1, 0);

    for (int i = 1; i <= n; i++)
    {
        diameter = std::max(diameter, ans[i]);
    }

    std::cout << diameter << std::endl;
}

// dfs
// const int MAXN = 500010;
// int head[MAXN], next[MAXN << 1], to[MAXN << 1], weight[MAXN << 1];
// int dist[MAXN], last[MAXN];
// int n, start, end, diameter, cnt = 1;

// void add_edge(int u, int v, int w)
// {
//     next[cnt] = head[u];
//     to[cnt] = v;
//     weight[cnt] = w;
//     head[u] = cnt++;
// }

// void dfs(int u, int f, int w)
// {
//     last[u] = f;
//     dist[u] = dist[f] + w;

//     for (int ei = head[u], v, wi; ei > 0; ei = next[ei])
//     {
//         v = to[ei], wi = weight[ei];
//         if (v != f)
//         {
//             dfs(v, u, wi);
//         }
//     }
// }

// void road()
// {
//     dfs(1, 0, 0);

//     start = 1;
//     for (int i = 2; i <= n; i++)
//     {
//         if (dist[i] > dist[start])
//         {
//             start = i;
//         }
//     }

//     dfs(start, 0, 0);

//     end = 1;
//     for (int i = 2; i <= n; i++)
//     {
//         if (dist[i] > dist[end])
//         {
//             end = i;
//         }
//     }

//     diameter = dist[end];
// }

// int main()
// {
//     std::cin >> n;
//     for (int i = 1, u, v, w; i < n; i++)
//     {
//         std::cin >> u >> v >> w;

//         add_edge(u, v, w);
//         add_edge(v, u, w);
//     }

//     road();

//     std::cout << diameter << std::endl;
// }