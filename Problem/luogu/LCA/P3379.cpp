#include <bits/stdc++.h>

// tarjan
const int MAXN = 500010;
int edge_head[MAXN], edge_next[MAXN << 1], edge_to[MAXN << 1];
int query_head[MAXN], query_next[MAXN << 1], query_to[MAXN << 1], query_index[MAXN << 1];
int father[MAXN], ans[MAXN];
bool visited[MAXN];
int n, m, s, ecnt = 1, qcnt = 1;

void add_edge(int u, int v)
{
    edge_next[ecnt] = edge_head[u];
    edge_to[ecnt] = v;
    edge_head[u] = ecnt++;
}

void add_query_edge(int u, int v, int i)
{
    query_next[qcnt] = query_head[u];
    query_to[qcnt] = v;
    query_index[qcnt] = i;
    query_head[u] = qcnt++;
}

int find(int i)
{
    if (i != father[i])
    {
        father[i] = find(father[i]);
    }

    return father[i];
}

void tarjan(int u, int f)
{
    visited[u] = true;
    for (int ei = edge_head[u], v; ei > 0; ei = edge_next[ei])
    {
        v = edge_to[ei];
        if (v != f)
        {
            tarjan(v, u);
            father[v] = u;
        }
    }

    for (int ei = query_head[u], v; ei > 0; ei = query_next[ei])
    {
        v = query_to[ei];
        if (visited[v])
        {
            ans[query_index[ei]] = find(v);
        }
    }
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    std::cin >> n >> m >> s;
    for (int i = 1, x, y; i < n; i++)
    {
        std::cin >> x >> y;
        add_edge(x, y);
        add_edge(y, x);
    }

    for (int i = 1; i <= n; i++)
    {
        father[i] = i;
    }

    for (int i = 1, a, b; i <= m; i++)
    {
        std::cin >> a >> b;
        add_query_edge(a, b, i);
        add_query_edge(b, a, i);
    }

    tarjan(s, 0);

    for (int i = 1; i <= m; i++)
    {
        std::cout << ans[i] << std::endl;
    }
}

// 树上倍增
// using vi = std::vector<int>;
// using vvi = std::vector<vi>;

// const int MAXN = 500010, LIMIT = 20;
// // vvi st(MAXN, vi(LIMIT));
// // vi deep(MAXN), head(MAXN), next(MAXN << 1), to(MAXN << 1);
// int n, m, s, power, cnt = 1;

// int st[MAXN][LIMIT], deep[MAXN], head[MAXN], next[MAXN << 1], to[MAXN << 1];

// int log2(int n)
// {
//     int ans = 0;
//     while ((1 << ans) <= (n >> 1))
//     {
//         ans++;
//     }

//     return ans;
// }

// void add_edge(int u, int v)
// {
//     next[cnt] = head[u];
//     to[cnt] = v;
//     head[u] = cnt++;

//     next[cnt] = head[v];
//     to[cnt] = u;
//     head[v] = cnt++;
// }

// void dfs(int u, int f)
// {
//     deep[u] = deep[f] + 1;

//     st[u][0] = f;
//     for (int p = 1; p <= power; p++)
//     {
//         st[u][p] = st[st[u][p - 1]][p - 1];
//     }

//     for (int ei = head[u], v; ei > 0; ei = next[ei])
//     {
//         v = to[ei];
//         if (v != f)
//         {
//             dfs(v, u);
//         }
//     }
// }

// // vvi uef(MAXN, vi(3));
// // int stack_size, u, e, f;

// // void push(int u, int e, int f)
// // {
// //     uef[stack_size][0] = u;
// //     uef[stack_size][1] = e;
// //     uef[stack_size++][2] = f;
// // }

// // void pop()
// // {
// //     u = uef[--stack_size][0];
// //     e = uef[stack_size][1];
// //     f = uef[stack_size][2];
// // }

// // void dfs()
// // {
// //     push(s, -1, 0);
// //     while (stack_size > 0)
// //     {
// //         pop();
// //         if (e == -1)
// //         {
// //             deep[u] = deep[f] + 1;

// //             st[u][0] = f;
// //             for (int p = 1; p <= power; p++)
// //             {
// //                 st[u][p] = st[st[u][p - 1]][p - 1];
// //             }

// //             e = head[u];
// //         }
// //         else
// //         {
// //             e = next[e];
// //         }

// //         if (e > 0)
// //         {
// //             push(u, e, f);
// //             if (to[e] != f)
// //             {
// //                 push(to[e], -1, u);
// //             }
// //         }
// //     }
// // }

// int lca(int a, int b)
// {
//     if (deep[a] < deep[b])
//     {
//         std::swap(a, b);
//     }

//     for (int p = power; p >= 0; p--)
//     {
//         if (deep[st[a][p]] >= deep[b])
//         {
//             a = st[a][p];
//         }
//     }

//     if (a == b)
//     {
//         return a;
//     }

//     for (int p = power; p >= 0; p--)
//     {
//         if (st[a][p] != st[b][p])
//         {
//             a = st[a][p];
//             b = st[b][p];
//         }
//     }

//     return st[a][0];
// }

// int main()
// {
//     std::ios::sync_with_stdio(false);
//     std::cin.tie(nullptr);
//     std::cout.tie(nullptr);

//     std::cin >> n >> m >> s;
//     for (int i = 1, x, y; i < n; i++)
//     {
//         std::cin >> x >> y;
//         add_edge(x, y);
//     }

//     power = log2(n);

//     dfs(s, 0);

//     while (m--)
//     {
//         int a, b;
//         std::cin >> a >> b;
//         std::cout << lca(a, b) << std::endl;
//     }
// }