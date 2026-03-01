#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vi = vector<int>;
using vll = vector<ll>;

const int MAXN = 1000010, LOWEST = -1;
vi arr(MAXN);

namespace ST
{
    vll sum(MAXN << 2);
    vi maxa(MAXN << 2), cnt(MAXN << 2), sem(MAXN << 2);

    void lazy(int i, int v)
    {
        if (v < maxa[i])
        {
            sum[i] -= ((ll)maxa[i] - v) * cnt[i];
            maxa[i] = v;
        }
    }

    void up(int i)
    {
        int l = i << 1, r = i << 1 | 1;
        sum[i] = sum[l] + sum[r];
        maxa[i] = max(maxa[l], maxa[r]);

        if (maxa[l] > maxa[r])
        {
            cnt[i] = cnt[l];
            sem[i] = max(sem[l], maxa[r]);
        }
        else if (maxa[l] < maxa[r])
        {
            cnt[i] = cnt[r];
            sem[i] = max(maxa[l], sem[r]);
        }
        else
        {
            cnt[i] = cnt[l] + cnt[r];
            sem[i] = max(sem[l], sem[r]);
        }
    }

    void down(int i)
    {
        lazy(i << 1, maxa[i]);
        lazy(i << 1 | 1, maxa[i]);
    }

    void build(int l, int r, int i)
    {
        if (l == r)
        {
            sum[i] = maxa[i] = arr[l];
            sem[i] = LOWEST;
            cnt[i] = 1;
        }
        else
        {
            int mid = l + ((r - l) >> 1);
            build(l, mid, i << 1);
            build(mid + 1, r, i << 1 | 1);

            up(i);
        }
    }

    void set_min(int jobl, int jobr, int jobv, int l, int r, int i)
    {
        if (jobv >= maxa[i])
        {
            return;
        }

        if (l >= jobl && r <= jobr && jobv > sem[i])
        {
            lazy(i, jobv);
        }
        else
        {
            int mid = l + ((r - l) >> 1);
            down(i);

            if (jobl <= mid)
            {
                set_min(jobl, jobr, jobv, l, mid, i << 1);
            }

            if (jobr >= mid + 1)
            {
                set_min(jobl, jobr, jobv, mid + 1, r, i << 1 | 1);
            }

            up(i);
        }
    }

    int query_max(int jobl, int jobr, int l, int r, int i)
    {
        if (l >= jobl && r <= jobr)
        {
            return maxa[i];
        }
        else
        {
            int mid = l + ((r - l) >> 1);
            down(i);

            int ans = INT32_MIN;
            if (jobl <= mid)
            {
                ans = max(ans, query_max(jobl, jobr, l, mid, i << 1));
            }

            if (jobr >= mid + 1)
            {
                ans = max(ans, query_max(jobl, jobr, mid + 1, r, i << 1 | 1));
            }

            return ans;
        }
    }

    ll query_sum(int jobl, int jobr, int l, int r, int i)
    {
        if (l >= jobl && r <= jobr)
        {
            return sum[i];
        }
        else
        {
            int mid = l + ((r - l) >> 1);
            down(i);

            ll ans = 0;
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
    }
}

int T, n, m, op, x, y, t;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    cin >> T;
    while (T--)
    {
        cin >> n >> m;
        for (int i = 1; i <= n; i++)
        {
            cin >> arr[i];
        }

        ST::build(1, n, 1);

        while (m--)
        {
            cin >> op;
            if (op == 0)
            {
                cin >> x >> y >> t;
                ST::set_min(x, y, t, 1, n, 1);
            }
            else if (op == 1)
            {
                cin >> x >> y;
                cout << ST::query_max(x, y, 1, n, 1) << endl;
            }
            else
            {
                cin >> x >> y;
                cout << ST::query_sum(x, y, 1, n, 1) << endl;
            }
        }
    }
}