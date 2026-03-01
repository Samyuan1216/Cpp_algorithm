#include <bits/stdc++.h>
using namespace std;

using vi = vector<int>;

const int MAXN = 50010;

namespace ST
{
    vi pre(MAXN << 2), suf(MAXN << 2);

    void up(int l, int r, int i)
    {
        pre[i] = pre[i << 1];
        suf[i] = suf[i << 1 | 1];

        int mid = l + ((r - l) >> 1);
        if (pre[i << 1] == mid - l + 1)
        {
            pre[i] += pre[i << 1 | 1];
        }

        if (suf[i << 1 | 1] == r - mid)
        {
            suf[i] += suf[i << 1];
        }
    }

    void build(int l, int r, int i)
    {
        if (l == r)
        {
            pre[i] = suf[i] = 1;
        }
        else
        {
            int mid = l + ((r - l) >> 1);
            build(l, mid, i << 1);
            build(mid + 1, r, i << 1 | 1);

            up(l, r, i);
        }
    }

    void update(int jobi, int jobv, int l, int r, int i)
    {
        if (l == r)
        {
            pre[i] = suf[i] = jobv;
        }
        else
        {
            int mid = l + ((r - l) >> 1);
            if (jobi <= mid)
            {
                update(jobi, jobv, l, mid, i << 1);
            }
            else
            {
                update(jobi, jobv, mid + 1, r, i << 1 | 1);
            }

            up(l, r, i);
        }
    }

    int query(int jobi, int l, int r, int i)
    {
        if (l == r)
        {
            return pre[i];
        }
        else
        {
            int mid = l + ((r - l) >> 1);
            if (jobi <= mid)
            {
                if (jobi >= mid - suf[i << 1] + 1)
                {
                    return suf[i << 1] + pre[i << 1 | 1];
                }
                else
                {
                    return query(jobi, l, mid, i << 1);
                }
            }
            else
            {
                if (jobi <= mid + pre[i << 1 | 1])
                {
                    return suf[i << 1] + pre[i << 1 | 1];
                }
                else
                {
                    return query(jobi, mid + 1, r, i << 1 | 1);
                }
            }
        }
    }
}

vi sta(MAXN);
int n, m, x, tp;
char op;

int main()
{
    cin >> n >> m;
    ST::build(1, n, 1);

    while (m--)
    {
        cin >> op;
        if (op == 'D')
        {
            cin >> x;
            ST::update(x, 0, 1, n, 1);

            sta[tp++] = x;
        }
        else if (op == 'R')
        {
            ST::update(sta[--tp], 1, 1, n, 1);
        }
        else
        {
            cin >> x;
            cout << ST::query(x, 1, n, 1) << endl;
        }
    }
}