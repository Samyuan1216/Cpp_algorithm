#include <bits/stdc++.h>

using vi = std::vector<int>;
using vvi = std::vector<vi>;

const int MAXN = 100010, LIMIT = 17;
vvi st(MAXN, vi(LIMIT));
vi arr(MAXN), lg2(MAXN), bucket(MAXN), left(MAXN), right(MAXN);
int n, q;

void build()
{
    arr[0] = INT32_MIN;
    int cnt = 0;
    for (int i = 1; i <= n; i++)
    {
        if (arr[i - 1] != arr[i])
        {
            right[cnt] = i - 1;
            left[++cnt] = i;
        }

        bucket[i] = cnt;
    }
    right[cnt] = n;

    lg2[0] = -1;
    for (int i = 1; i <= cnt; i++)
    {
        lg2[i] = lg2[i >> 1] + 1;
        st[i][0] = right[i] - left[i] + 1;
    }

    for (int p = 1; p <= lg2[cnt]; p++)
    {
        for (int i = 1; i + (1 << p) - 1 <= n; i++)
        {
            st[i][p] = std::max(st[i][p - 1], st[i + (1 << (p - 1))][p - 1]);
        }
    }
}

int query(int l, int r)
{
    if (l > r)
    {
        std::swap(l, r);
    }

    int lbucket = bucket[l], rbucket = bucket[r];
    if (lbucket == rbucket)
    {
        return r - l + 1;
    }

    int a = right[lbucket] - l + 1, b = r - left[rbucket] + 1, c = 0;
    if (lbucket + 1 < rbucket)
    {
        int from = lbucket + 1, to = rbucket - 1;
        int p = lg2[to - from + 1];

        c = std::max(st[from][p], st[to - (1 << p) + 1][p]);
    }

    return std::max(std::max(a, b), c);
}

int main()
{
    while (1)
    {
        std::cin >> n;
        if (n == 0)
        {
            break;
        }
        std::cin >> q;

        for (int i = 1; i <= n; i++)
        {
            std::cin >> arr[i];
        }

        build();
        
        while (q--)
        {
            int i, j;
            std::cin >> i >> j;
            std::cout << query(i, j) << std::endl;
        }
    }
}