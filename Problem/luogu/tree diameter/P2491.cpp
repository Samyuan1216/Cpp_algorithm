#include <bits/stdc++.h>

const int MAXN = 300010;
int head[MAXN], next[MAXN << 1], to[MAXN << 1], weight[MAXN << 1];
int dist[MAXN], last[MAXN], pred[MAXN], max_dist[MAXN], queue[MAXN];
bool path[MAXN];
int n, s, start, end, diameter, suml, sumr, h, t, cnt = 1;

void add_edge(int u, int v, int w)
{
    next[cnt] = head[u];
    to[cnt] = v;
    weight[cnt] = w;
    head[u] = cnt++;
}

void dfs(int u, int f, int w)
{
    last[u] = f;
    dist[u] = dist[f] + w;
    pred[u] = w;

    for (int ei = head[u], v, wi; ei > 0; ei = next[ei])
    {
        v = to[ei], wi = weight[ei];
        if (v != f)
        {
            dfs(v, u, wi);
        }
    }
}

void road()
{
    dfs(1, 0, 0);

    start = 1;
    for (int i = 2; i <= n; i++)
    {
        if (dist[i] > dist[start])
        {
            start = i;
        }
    }

    dfs(start, 0, 0);

    end = 1;
    for (int i = 2; i <= n; i++)
    {
        if (dist[i] > dist[end])
        {
            end = i;
        }
    }

    diameter = dist[end];
}

int max_distance_except_diameter(int u, int f, int c)
{
    int ans = c;
    for (int ei = head[u], v, w; ei > 0; ei = next[ei])
    {
        v = to[ei], w = weight[ei];
        if (!path[v] && v != f)
        {
            ans = std::max(ans, max_distance_except_diameter(v, u, c + w));
        }
    }

    return ans;
}

void distance()
{
    for (int i = end; i != 0; i = last[i])
    {
        path[i] = true;
    }

    for (int i = end; i != 0; i = last[i])
    {
        max_dist[i] = max_distance_except_diameter(i, 0, 0);
    }
}

int main()
{
    std::cin >> n >> s;
    for (int i = 1, u, v, w; i < n; i++)
    {
        std::cin >> u >> v >> w;

        add_edge(u, v, w);
        add_edge(v, u, w);
    }

    road();
    distance();

    int ans = INT32_MAX;
    for (int l = end, r = end; l != 0; l = last[l])
    {
        while (r != 0 && sumr - suml + pred[r] <= s)
        {
            while (h < t && max_dist[r] >= max_dist[queue[t - 1]])
            {
                t--;
            }

            sumr += pred[r];
            queue[t++] = r;
            r = last[r];
        }

        ans = std::min(ans, std::max(max_dist[queue[h]], std::max(suml, diameter - sumr)));
        if (queue[h] == l)
        {
            h++;
        }
        
        suml += pred[l];
    }

    std::cout << ans << std::endl;
}