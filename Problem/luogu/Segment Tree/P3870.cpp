#include <bits/stdc++.h>
using namespace std;

using vi = vector<int>;

const int MAXN = 100010;
int n, m, c, a, b;

namespace ST
{
    vi sum(MAXN << 2);
    bool upd[MAXN << 2];

    void lazy(int i, int n)
    {
        sum[i] = n - sum[i];
        upd[i] = !upd[i];
    }

    void up(int i)
    {
        sum[i] = sum[i << 1] + sum[i << 1 | 1];
    }

    void down(int i, int ln, int rn)
    {
        if (upd[i])
        {
            lazy(i << 1, ln);
            lazy(i << 1 | 1, rn);

            upd[i] = false;
        }
    }

    void build(int l, int r, int i)
    {
        if (l == r)
        {
            sum[i] = 0;
        }
        else
        {
            int mid = l + ((r - l) >> 1);
            build(l, mid, i << 1);
            build(mid + 1, r, i << 1 | 1);

            up(i);
        }

        upd[i] = false;
    }

    int query(int &jobl, int &jobr, int l, int r, int i)
    {
        if (l >= jobl && r <= jobr)
        {
            return sum[i];
        }

        int mid = l + ((r - l) >> 1);
        down(i, mid - l + 1, r - mid);

        int ans = 0;
        if (jobl <= mid)
        {
            ans += query(jobl, jobr, l, mid, i << 1);
        }

        if (jobr >= mid + 1)
        {
            ans += query(jobl, jobr, mid + 1, r, i << 1 | 1);
        }

        return ans;
    }

    void update(int &jobl, int &jobr, int l, int r, int i)
    {
        if (l >= jobl && r <= jobr)
        {
            lazy(i, r - l + 1);
        }
        else
        {
            int mid = l + ((r - l) >> 1);
            down(i, mid - l + 1, r - mid);

            if (jobl <= mid)
            {
                update(jobl, jobr, l, mid, i << 1);
            }

            if (jobr >= mid + 1)
            {
                update(jobl, jobr, mid + 1, r, i << 1 | 1);
            }

            up(i);
        }
    }
}

int main()
{
    cin >> n >> m;
    ST::build(1, n, 1);

    while (m--)
    {
        cin >> c >> a >> b;
        if (c == 0)
        {
            ST::update(a, b, 1, n, 1);
        }
        else
        {
            cout << ST::query(a, b, 1, n, 1) << endl;
        }
    }
}