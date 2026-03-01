#include <bits/stdc++.h>
using namespace std;

using vi = vector<int>;

const int MAXN = 100010;
vi arr(MAXN);

namespace ST
{
    vi len1(MAXN << 2), pre1(MAXN << 2), suf1(MAXN << 2);
    vi len0(MAXN << 2), pre0(MAXN << 2), suf0(MAXN << 2);
    vi sum(MAXN << 2), change(MAXN << 2);
    bool upd[MAXN << 2], rev[MAXN << 2];

    void update_lazy(int i, int v, int n)
    {
        sum[i] = v * n;

        len1[i] = pre1[i] = suf1[i] = (v == 1? n: 0);
        len0[i] = pre0[i] = suf0[i] = (v == 0? n: 0);

        change[i] = v;
        upd[i] = true;
        rev[i] = false;
    }

    void reverse_lazy(int i, int n)
    {
        sum[i] = n - sum[i];

        swap(len1[i], len0[i]);
        swap(pre1[i], pre0[i]);
        swap(suf1[i], suf0[i]);

        rev[i] = !rev[i];
    }

    void up(int i, int ln, int rn)
    {
        int l = i << 1, r = i << 1 | 1;
        sum[i] = sum[l] + sum[r];

        len1[i] = max(max(len1[l], len1[r]), suf1[l] + pre1[r]);
        pre1[i] = (len1[l] < ln? pre1[l]: (pre1[l] + pre1[r]));
        suf1[i] = (len1[r] < rn? suf1[r]: (suf1[l] + suf1[r]));

        len0[i] = max(max(len0[l], len0[r]), suf0[l] + pre0[r]);
        pre0[i] = (len0[l] < ln? pre0[l]: (pre0[l] + pre0[r]));
        suf0[i] = (len0[r] < rn? suf0[r]: (suf0[l] + suf0[r]));
    }

    void down(int i, int ln, int rn)
    {
        if (upd[i])
        {
            update_lazy(i << 1, change[i], ln);
            update_lazy(i << 1 | 1, change[i], rn);

            upd[i] = false;
        }

        if (rev[i])
        {
            reverse_lazy(i << 1, ln);
            reverse_lazy(i << 1 | 1, rn);

            rev[i] = false;
        }
    }

    void build(int l, int r, int i)
    {
        if (l == r)
        {
            sum[i] = arr[l];

            len1[i] = pre1[i] = suf1[i] = (arr[l] == 1? 1: 0);
            len0[i] = pre0[i] = suf0[i] = (arr[l] == 0? 1: 0);
        }
        else
        {
            int mid = l + ((r - l) >> 1);
            build(l, mid, i << 1);
            build(mid + 1, r, i << 1 | 1);

            up(i, mid - l + 1, r - mid);
        }

        upd[i] = false;
        rev[i] = false;
    }

    void update(int jobl, int jobr, int jobv, int l, int r, int i)
    {
        if (l >= jobl && r <= jobr)
        {
            update_lazy(i, jobv, r - l + 1);
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

            up(i, mid - l + 1, r - mid);
        }
    }

    void rever(int jobl, int jobr, int l, int r, int i)
    {
        if (l >= jobl && r <= jobr)
        {
            reverse_lazy(i, r - l + 1);
        }
        else
        {
            int mid = l + ((r - l) >> 1);
            down(i, mid - l + 1, r - mid);

            if (jobl <= mid)
            {
                rever(jobl, jobr, l, mid, i << 1);
            }

            if (jobr >= mid + 1)
            {
                rever(jobl, jobr, mid + 1, r, i << 1 | 1);
            }

            up(i, mid - l + 1, r - mid);
        }
    }

    int query_sum(int jobl, int jobr, int l, int r, int i)
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
            ans += query_sum(jobl, jobr, l, mid, i << 1);
        }

        if (jobr >= mid + 1)
        {
            ans += query_sum(jobl, jobr, mid + 1, r, i << 1 | 1);
        }

        return ans;
    }

    vi query_len(int jobl, int jobr, int l, int r, int i)
    {
        if (l >= jobl && r <= jobr)
        {
            return vi{len1[i], pre1[i], suf1[i]};
        }

        int mid = l + ((r - l) >> 1);
        down(i, mid - l + 1, r - mid);

        if (jobr <= mid)
        {
            return query_len(jobl, jobr, l, mid, i << 1);
        }

        if (jobl >= mid + 1)
        {
            return query_len(jobl, jobr, mid + 1, r, i << 1 | 1);
        }

        vi l3 = query_len(jobl, jobr, l, mid, i << 1);
        vi r3 = query_len(jobl, jobr, mid + 1, r, i << 1 | 1);

        int llen = l3[0], lpre = l3[1], lsuf = l3[2];
        int rlen = r3[0], rpre = r3[1], rsuf = r3[2];

        int len = max(max(llen, rlen), lsuf + rpre);
        int pre = (llen < mid - max(l, jobl) + 1? lpre: (lpre + rpre));
        int suf = (rlen < min(r, jobr) - mid? rsuf: (lsuf + rsuf));

        return vi{len, pre, suf};
    }
}

int n, m, op, l, r;

int main()
{
    cin >> n >> m;
    for (int i = 1; i <= n; i++)
    {
        cin >> arr[i];
    }

    ST::build(1, n, 1);

    while (m--)
    {
        cin >> op >> l >> r;
        l++, r++;

        if (op == 0)
        {
            ST::update(l, r, 0, 1, n, 1);
        }
        else if (op == 1)
        {
            ST::update(l, r, 1, 1, n, 1);
        }
        else if (op == 2)
        {
            ST::rever(l, r, 1, n, 1);
        }
        else if (op == 3)
        {
            cout << ST::query_sum(l, r, 1, n, 1) << endl;
        }
        else
        {
            cout << ST::query_len(l, r, 1, n, 1)[0] << endl;
        }
    }
}