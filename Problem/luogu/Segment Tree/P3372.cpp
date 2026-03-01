#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vll = vector<ll>;

const int MAXN = 100010;
vll diff(MAXN);
int n, m, a, x, y;
ll k;

namespace ST
{
    vll sum(MAXN << 2), ad(MAXN << 2);

    void lazy(int i, ll v, int n)
    {
        sum[i] += v * n;
        ad[i] += v;
    }

    void up(int i)
    {
        sum[i] = sum[i << 1] + sum[i << 1 | 1];
    }

    void down(int i, int ln, int rn)
    {
        if (ad[i] != 0)
        {
            lazy(i << 1, ad[i], ln);
            lazy(i << 1 | 1, ad[i], rn);

            ad[i] = 0;
        }
    }

    void build(int l, int r, int i)
    {
        if (l == r)
        {
            sum[i] = diff[l];
        }
        else
        {
            int mid = l + ((r - l) >> 1);
            build(l, mid, i << 1);
            build(mid + 1, r, i << 1 | 1);

            up(i);
        }

        ad[i] = 0;
    }

    ll query(int &jobl, int &jobr, int l, int r, int i)
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
            ans += query(jobl, jobr, l, mid, i << 1);
        }
        
        if (jobr >= mid + 1)
        {
            ans += query(jobl, jobr, mid + 1, r, i << 1 | 1);
        }

        return ans;
    }

    void add(int &jobl, int &jobr, ll &jobv, int l, int r, int i)
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
                add(jobl, jobr, jobv, l, mid, i << 1);
            }

            if (jobr >= mid + 1)
            {
                add(jobl, jobr, jobv, mid + 1, r, i << 1 | 1);
            }

            up(i);
        }
    }
}

int main()
{
    cin >> n >> m;
    for (int i = 1; i <= n; i++)
    {
        cin >> diff[i];
    }

    ST::build(1, n, 1);

    for (int i = 1; i <= m; i++)
    {
        cin >> a;
        if (a == 1)
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