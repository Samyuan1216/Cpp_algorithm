#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vll = vector<ll>;

const int MAXN = 1000010;
vll diff(MAXN);
int n, q, op, a, b;
ll x;

namespace ST
{
    vll maxa(MAXN << 2), ad(MAXN << 2), change(MAXN << 2);
    bool upd[MAXN << 2];

    void add_lazy(int i, ll v)
    {
        maxa[i] += v;
        ad[i] += v;
    }

    void update_lazy(int i, ll v)
    {
        maxa[i] = v;
        ad[i] = 0;
        change[i] = v;
        upd[i] = true;
    }

    void up(int i)
    {
        maxa[i] = max(maxa[i << 1], maxa[i << 1 | 1]);
    }

    void down(int i)
    {
        if (upd[i])
        {
            update_lazy(i << 1, change[i]);
            update_lazy(i << 1 | 1, change[i]);

            upd[i] = false;
        }

        if (ad[i] != 0)
        {
            add_lazy(i << 1, ad[i]);
            add_lazy(i << 1 | 1, ad[i]);

            ad[i] = 0;
        }
    }

    void build(int l, int r, int i)
    {
        if (l == r)
        {
            maxa[i] = diff[l];
        }
        else
        {
            int mid = l + ((r - l) >> 1);
            build(l, mid, i << 1);
            build(mid + 1, r, i << 1 | 1);

            up(i);
        }

        ad[i] = 0;
        change[i] = 0;
        upd[i] = false;
    }

    ll query(int &jobl, int &jobr, int l, int r, int i)
    {
        if (l >= jobl && r <= jobr)
        {
            return maxa[i];
        }
        
        int mid = l + ((r - l) >> 1);
        down(i);

        ll ans = INT64_MIN;
        if (jobl <= mid)
        {
            ans = max(ans, query(jobl, jobr, l, mid, i << 1));
        }

        if (jobr >= mid + 1)
        {
            ans = max(ans, query(jobl, jobr, mid + 1, r, i << 1 | 1));
        }

        return ans;
    }

    void add(int &jobl, int &jobr, ll &jobv, int l, int r, int i)
    {
        if (l >= jobl && r <= jobr)
        {
            add_lazy(i, jobv);
        }
        else
        {
            int mid = l + ((r - l) >> 1);
            down(i);

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

    void update(int &jobl, int &jobr, ll &jobv, int l, int r, int i)
    {
        if (l >= jobl && r <= jobr)
        {
            update_lazy(i, jobv);
        }
        else
        {
            int mid = l + ((r - l) >> 1);
            down(i);

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
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    cin >> n >> q;
    for (int i = 1; i <= n; i++)
    {
        cin >> diff[i];
    }

    ST::build(1, n, 1);

    while (q--)
    {
        cin >> op;
        if (op == 1)
        {
            cin >> a >> b >> x;
            ST::update(a, b, x, 1, n, 1);
        }
        else if (op == 2)
        {
            cin >> a >> b >> x;
            ST::add(a, b, x, 1, n, 1);
        }
        else if (op == 3)
        {
            cin >> a >> b;
            cout << ST::query(a, b, 1, n, 1) << endl;
        }
    }
}