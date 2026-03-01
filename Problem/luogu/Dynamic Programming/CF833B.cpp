#include <bits/stdc++.h>

const int MAXN = 35010;
int arr[MAXN], dp[MAXN], pre[MAXN], max[MAXN << 2], ad[MAXN << 2];
int n, k;

void lazy(int i, int v)
{
    max[i] += v;
    ad[i] += v;
}

void up(int i)
{
    max[i] = std::max(max[i << 1], max[i << 1 | 1]);
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
        max[i] = dp[l];
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

void add(int jobl, int jobr, int jobv, int l, int r, int i)
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
            add(jobl, jobr, jobv, l, mid, i << 1);
        }
        
        if (mid + 1 <= jobr)
        {
            add(jobl, jobr, jobv, mid + 1, r, i << 1 | 1);
        }

        up(i);
    }
}

int query(int jobl, int jobr, int l, int r, int i)
{
    if (l >= jobl && r <= jobr)
    {
        return max[i];
    }

    int mid = l + (r - l) / 2;
    down(i);

    int ans = 0;
    if (mid >= jobl)
    {
        ans = std::max(ans, query(jobl, jobr, l, mid, i << 1));
    }

    if (mid + 1 <= jobr)
    {
        ans = std::max(ans, query(jobl, jobr, mid + 1, r, i << 1 | 1));
    }

    return ans;
}

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    std::cin >> n >> k;
    for (int i = 1; i <= n; i++)
    {
        std::cin >> arr[i];
    }

    for (int t = 1; t <= k; t++)
    {
        build(0, n, 1);
        std::fill(pre + 1, pre + n + 1, 0);

        for (int i = 1; i <= n; i++)
        {
            add(pre[arr[i]], i - 1, 1, 0, n, 1);
            if (i >= t)
            {
                dp[i] = query(0, i - 1, 0, n, 1);
            }

            pre[arr[i]] = i;
        }
    }

    std::cout << dp[n] << "\n";
}