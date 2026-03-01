#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vi = vector<int>;
using vll = vector<ll>;

const int MAXN = 100010;
vi arr(MAXN);
int n, q, m, op, x, y;
ll k;

namespace ST
{
    vll sum(MAXN << 2), ad(MAXN << 2), mut(MAXN << 2);

    void add_lazy(int i, ll v, int n)
    {
        sum[i] = (sum[i] + (n * v) % m) % m;
        ad[i] = (ad[i] + v) % m;
    }

    void multiply_lazy(int i, ll v)
    {
        sum[i] = (sum[i] * v) % m;
        mut[i] = (mut[i] * v) % m;
        ad[i] = (ad[i] * v) % m;
    }

    void up(int i)
    {
        sum[i] = (sum[i << 1] + sum[i << 1 | 1]) % m;
    }

    void down(int i, int ln, int rn)
    {
        if (mut[i] != 1)
        {
            multiply_lazy(i << 1, mut[i]);
            multiply_lazy(i << 1 | 1, mut[i]);

            mut[i] = 1;
        }

        if (ad[i] != 0)
        {
            add_lazy(i << 1, ad[i], ln);
            add_lazy(i << 1 | 1, ad[i], rn);

            ad[i] = 0;
        }
    }

    void build(int l, int r, int i)
    {
        if (l == r)
        {
            sum[i] = arr[l];
        }
        else
        {
            int mid = l + ((r - l) >> 1);
            build(l, mid, i << 1);
            build(mid + 1, r, i << 1 | 1);

            up(i);
        }

        ad[i] = 0;
        mut[i] = 1;
    }

    void add(int jobl, int jobr, ll jobv, int l, int r, int i)
    {
        if (l >= jobl && r <= jobr)
        {
            add_lazy(i, jobv, r - l + 1);
        }
        else
        {
            int mid = l + ((r - l) >> 1);
            down(i, mid - l + 1, r - mid);

            if (jobl <= mid)
            {
                add(jobl, jobr, jobv, l, mid, i << 1);
            }

            if (jobr >= mid + 1)
            {
                add(jobl, jobr, jobv, mid + 1, r, i << 1 | 1);
            }

            up(i);
        }
    }

    void multiply(int jobl, int jobr, ll jobv, int l, int r, int i)
    {
        if (l >= jobl && r <= jobr)
        {
            multiply_lazy(i, jobv);
        }
        else
        {
            int mid = l + ((r - l) >> 1);
            down(i, mid - l + 1, r - mid);

            if (jobl <= mid)
            {
                multiply(jobl, jobr, jobv, l, mid, i << 1);
            }

            if (jobr >= mid + 1)
            {
                multiply(jobl, jobr, jobv, mid + 1, r, i << 1 | 1);
            }

            up(i);
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
        if (jobl <= mid)
        {
            ans = (ans + query(jobl, jobr, l, mid, i << 1)) % m;
        }

        if (jobr >= mid + 1)
        {
            ans = (ans + query(jobl, jobr, mid + 1, r, i << 1 | 1)) % m;
        }

        return ans;
    }
}

int main()
{
    cin >> n >> q >> m;
    for (int i = 1; i <= n; i++)
    {
        cin >> arr[i];
    }

    ST::build(1, n, 1);

    while (q--)
    {
        cin >> op;
        if (op == 1)
        {
            cin >> x >> y >> k;
            ST::multiply(x, y, k, 1, n, 1);
        }
        else if (op == 2)
        {
            cin >> x >> y >> k;
            ST::add(x, y, k, 1, n, 1);
        }
        else
        {
            cin >> x >> y;
            cout << ST::query(x, y, 1, n, 1) << endl;
        }
    }
}