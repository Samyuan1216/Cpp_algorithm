#include <bits/stdc++.h>

const int MAXN = 20010;
int dist[MAXN], fix[MAXN], range[MAXN], warranty[MAXN], left[MAXN], right[MAXN], dp[MAXN];
int head[MAXN], next[MAXN], to[MAXN];
int min[MAXN << 2], ad[MAXN << 2];
int n, k, cnt = 1;

int find(int v)
{
    int ans = 0, l = 1, r = n, mid;
    while (l <= r)
    {
        mid = l + (r - l) / 2;
        if (dist[mid] >= v)
        {
            ans = mid;
            r = mid - 1;
        }
        else
        {
            l = mid + 1;
        }
    }

    return ans;
}

void add_edge(int u, int v)
{
    next[cnt] = head[u];
    to[cnt] = v;
    head[u] = cnt++;
}

void lazy(int i, int v)
{
    min[i] += v;
    ad[i] += v;
}

void up(int i)
{
    min[i] = std::min(min[i << 1], min[i << 1 | 1]);
}

void down(int i)
{
    if (ad[i] != 0)
    {
        lazy(i << 1, ad[i]);
        lazy(i << 1 | 1, ad[i]);

        ad[i] = 0;
    }
}

void build(int l, int r, int i)
{
    if (l == r)
    {
        min[i] = dp[l];
    }
    else
    {
        int mid = l + (r - l) / 2;
        build(l, mid, i << 1);
        build(mid + 1, r, i << 1 | 1);

        up(i);
    }

    ad[i] = 0;
}

void update(int jobl, int jobr, int jobv, int l, int r, int i)
{
    if (l >= jobl && r <= jobr)
    {
        lazy(i, jobv);
    }
    else
    {
        int mid = l + (r - l) / 2;
        down(i);

        if (mid >= jobl)
        {
            update(jobl, jobr, jobv, l, mid, i << 1);
        }

        if (mid + 1 <= jobr)
        {
            update(jobl, jobr, jobv, mid + 1, r, i << 1 | 1);
        }

        up(i);
    }
}

int query(int jobl, int jobr, int l, int r, int i)
{
    if (l >= jobl && r <= jobr)
    {
        return min[i];
    }

    int mid = l + (r - l) / 2;
    down(i);

    int ans = INT32_MAX;
    if (mid >= jobl)
    {
        ans = std::min(ans, query(jobl, jobr, l, mid, i << 1));
    }

    if (mid + 1 <= jobr)
    {
        ans = std::min(ans, query(jobl, jobr, mid + 1, r, i << 1 | 1));
    }

    return ans;
}

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    std::cin >> n >> k;
    for (int i = 2; i <= n; i++)
    {
        std::cin >> dist[i];
    }

    for (int i = 1; i <= n; i++)
    {
        std::cin >> fix[i];
    }

    for (int i = 1; i <= n; i++)
    {
        std::cin >> range[i];
    }

    for (int i = 1; i <= n; i++)
    {
        std::cin >> warranty[i];
    }

    dist[++n] = INT32_MAX;
    for (int i = 1; i <= n; i++)
    {
        left[i] = find(dist[i] - range[i]);
        right[i] = find(dist[i] + range[i]);
        if (dist[right[i]] > dist[i] + range[i])
        {
            right[i]--;
        }

        add_edge(right[i], i);
    }

    for (int i = 1, w = 0; i <= n; i++)
    {
        dp[i] = w + fix[i];
        for (int ei = head[i]; ei > 0; ei = next[ei])
        {
            w += warranty[to[ei]];
        }
    }

    for (int t = 2; t <= k + 1; t++)
    {
        build(1, n, 1);
        for (int i = 1; i <= n; i++)
        {
            if (i >= t)
            {
                dp[i] = std::min(dp[i], query(1, i - 1, 1, n, 1) + fix[i]);
            }

            for (int ei = head[i], uncover; ei > 0; ei = next[ei])
            {
                uncover = to[ei];
                if (left[uncover] > 1)
                {
                    update(1, left[uncover] - 1, warranty[uncover], 1, n, 1);
                }
            }
        }
    }

    std::cout << dp[n] << "\n";
}