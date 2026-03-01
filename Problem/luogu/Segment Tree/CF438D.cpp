#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vll = vector<ll>;

const int MAXN = 100010;
vll diff(MAXN);

namespace ST
{
    vll sum(MAXN << 2), maxa(MAXN << 2);
    
    void up(int i)
    {
        sum[i] = sum[i << 1] + sum[i << 1 | 1];
        maxa[i] = max(maxa[i << 1], maxa[i << 1 | 1]);
    }

    void build(int l, int r, int i)
    {
        if (l == r)
        {
            sum[i] = maxa[i] = diff[l];
        }
        else
        {
            int mid = l + ((r - l) >> 1);
            build(l, mid, i << 1);
            build(mid + 1, r, i << 1 | 1);

            up(i);
        }
    }

    ll query(int &jobl, int &jobr, int l, int r, int i)
    {
        if (l >= jobl && r <= jobr)
        {
            return sum[i];
        }
        
        int mid = l + ((r - l) >> 1);

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

    void mod(int &jobl, int &jobr, int &jobv, int l, int r, int i)
    {
        if (maxa[i] >= jobv)
        {
            if (l == r)
            {
                sum[i] %= jobv;
                maxa[i] %= jobv;
            }
            else
            {
                int mid = l + ((r - l) >> 1);

                if (jobl <= mid)
                {
                    mod(jobl, jobr, jobv, l, mid, i << 1);
                }

                if (jobr >= mid + 1)
                {
                    mod(jobl, jobr, jobv, mid + 1, r, i << 1 | 1);
                }

                up(i);
            }
        }
    }

    void update(int &jobl, int &jobr, int &jobv, int l, int r, int i)
    {
        if (l == r)
        {
            sum[i] = maxa[i] = jobv;
        }
        else
        {
            int mid = l + ((r - l) >> 1);

            if (jobl <= mid)
            {
                update(jobl, jobr, jobv, l, mid, i << 1);
            }

            if (jobr >= mid + 1)
            {
                update(jobl, jobr, jobv, mid + 1, r, i << 1 | 1);
            }

            up(i);
        }
    }
}

int main()
{
    int n, m;
    cin >> n >> m;
    for (int i = 1; i <= n; i++)
    {
        cin >> diff[i];
    }

    ST::build(1, n, 1);

    while (m--)
    {
        int op;
        cin >> op;

        if (op == 1)
        {
            int l, r;
            cin >> l >> r;

            cout << ST::query(l, r, 1, n, 1) << endl;
        }
        else if (op == 2)
        {
            int l, r, x;
            cin >> l >> r >> x;

            ST::mod(l, r, x, 1, n, 1);
        }
        else
        {
            int k, x;
            cin >> k >> x;

            ST::update(k, k, x, 1, n, 1);
        }
    }
}