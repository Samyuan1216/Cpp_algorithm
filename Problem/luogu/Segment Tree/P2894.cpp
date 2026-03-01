#include <bits/stdc++.h>
using namespace std;

using vi = vector<int>;

const int MAXN = 50010;

namespace ST
{
    vi arr(MAXN), len(MAXN << 2), pre(MAXN << 2), suf(MAXN << 2), change(MAXN << 2);
    bool upd[MAXN << 2];

    void lazy(int i, int v, int n)
    {
        len[i] = pre[i] = suf[i] = (v == 1? n: 0);

        change[i] = v;
        upd[i] = true;
    }

    void up(int l, int r, int i)
    {
        len[i] = max(len[i << 1], len[i << 1 | 1]);
        pre[i] = pre[i << 1];
        suf[i] = suf[i << 1 | 1];

        int mid = l + ((r - l) >> 1);
        if (arr[mid] == 1 && arr[mid + 1] == 1)
        {
            len[i] = max(len[i], suf[i << 1] + pre[i << 1 | 1]);
            if (pre[i << 1] == mid - l + 1)
            {
                pre[i] += pre[i << 1 | 1];
            }

            if (suf[i << 1 | 1] == r - mid)
            {
                suf[i] += suf[i << 1];
            }
        }
    }

    void down(int i, int ln, int rn)
    {
        if (upd[i])
        {
            lazy(i << 1, change[i], ln);
            lazy(i << 1 | 1, change[i], rn);

            upd[i] = false;
        }
    }

    void build(int l, int r, int i)
    {
        if (l == r)
        {
            arr[l] = 1;
            len[i] = pre[i] = suf[i] = 1;
        }
        else
        {
            int mid = l + ((r - l) >> 1);
            build(l, mid, i << 1);
            build(mid + 1, r, i << 1 | 1);

            up(l, r, i);
        }

        upd[i] = false;
    }

    void update(int jobl, int jobr, int jobv, int l, int r, int i)
    {
        if (l >= jobl && r <= jobr)
        {
            lazy(i, jobv, r - l + 1);
        }
        else
        {
            int mid = l + ((r - l) >> 1);
            down(i, mid - l + 1, r - mid);

            if (jobl <= mid)
            {
                update(jobl, jobr, jobv, l, mid, i << 1);
            }

            if (jobr >= mid + 1)
            {
                update(jobl, jobr, jobv, mid + 1, r, i << 1 | 1);
            }

            up(l, r, i);
        }
    }

    int query(int jobx, int l, int r, int i)
    {
        int mid = l + ((r - l) >> 1);
        down(i, mid - l + 1, r - mid);

        if (len[i << 1] >= jobx)
        {
            return query(jobx, l, mid, i << 1);
        }

        if (suf[i << 1] + pre[i << 1 | 1] >= jobx)
        {
            return mid - suf[i << 1] + 1;
        }

        if (len[i << 1 | 1] >= jobx)
        {
            return query(jobx, mid + 1, r, i << 1 | 1);
        }

        return 0;
    }
}

int n, m, op, x, y;

int main()
{
    cin >> n >> m;
    ST::build(1, n, 1);

    while (m--)
    {
        cin >> op;
        if (op == 1)
        {
            cin >> x;
            int jobi = ST::query(x, 1, n, 1);
            cout << jobi << endl;

            if (jobi != 0)
            {
                ST::update(jobi, jobi + x - 1, 0, 1, n, 1);
            }
        }
        else
        {
            cin >> x >> y;
            ST::update(x, x + y - 1, 1, 1, n, 1);
        }
    }
}