#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vi = vector<int>;
using vll = vector<ll>;

const int MAXN = 80010;

namespace ST
{
    vi left(MAXN), right(MAXN);
    vll sum(MAXN), ad(MAXN);
    int cnt = 1;

    void lazy(int i, ll v, int n)
    {
        sum[i] += v * n;
        ad[i] += v;
    }

    void up(int i, int l, int r)
    {
        sum[i] = sum[l] + sum[r];
    }

    void down(int i, int ln, int rn)
    {
        if (ad[i] != 0)
        {
            if (left[i] == 0)
            {
                left[i] = ++cnt;
            }

            if (right[i] == 0)
            {
                right[i] = ++cnt;
            }

            lazy(left[i], ad[i], ln);
            lazy(right[i], ad[i], rn);

            ad[i] = 0;
        }
    }

    void add(int jobl, int jobr, ll jobv, int l, int r, int i)
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
                if (left[i] == 0)
                {
                    left[i] = ++cnt;
                }

                add(jobl, jobr, jobv, l, mid, left[i]);
            }

            if (jobr >= mid + 1)
            {
                if (right[i] == 0)
                {
                    right[i] = ++cnt;
                }

                add(jobl, jobr, jobv, mid + 1, r, right[i]);
            }

            up(i, left[i], right[i]);
        }
    }

    ll query(int jobl, int jobr, int l, int r, int i)
    {
        if (l >= jobl && r <= jobr)
        {
            return sum[i];
        }

        int mid = l + ((r - l) >> 1);
        down(i, mid - l + 1, r - mid);

        ll ans = 0;
        if (jobl <= mid && left[i] != 0)
        {
            ans += query(jobl, jobr, l, mid, left[i]);
        }

        if (jobr >= mid + 1 && right[i] != 0)
        {
            ans += query(jobl, jobr, mid + 1, r, right[i]);
        }

        return ans;
    }
}

int n, m, op, l, r;
ll k;

int main()
{
    cin >> n >> m;
    while (m--)
    {
        cin >> op;
        if (op == 1)
        {
            cin >> l >> r >> k;
            ST::add(l, r, k, 1, n, 1);
        }
        else
        {
            cin >> l >> r;
            cout << ST::query(l, r, 1, n, 1) << endl;
        }
    }
}