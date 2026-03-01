#include <bits/stdc++.h>
using namespace std;

using vi = vector<int>;

const int MAXN = 50010;
int t, n, m;

namespace ST
{
    vi sum(MAXN << 2), change(MAXN << 2);
    bool upd[MAXN << 2];

    void lazy(int i, int v, int n)
    {
        sum[i] = v * n;
        change[i] = v;
        upd[i] = true;
    }

    void up(int i)
    {
        sum[i] = sum[i << 1] + sum[i << 1 | 1];
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
            sum[i] = 0;
        }
        else
        {
            int mid = l + ((r - l) >> 1);
            build(l, mid, i << 1);
            build(mid + 1, r, i << 1 | 1);

            up(i);
        }

        change[i] = 0;
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

    void update(int &jobl, int &jobr, int jobv, int l, int r, int i)
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

            up(i);
        }
    }
}

int find_zero(int s, int k)
{
    int ans = 0;
    for (int l = s, r = n, mid; l <= r;)
    {
        mid = l + ((r - l) >> 1);
        if (mid - s + 1 - ST::query(s, mid, 1, n, 1) >= k)
        {
            ans = mid;
            r = mid - 1;
        }
        else
        {
            l = mid + 1;
        }
    }

    return ans;
}

vi insert(int free, int flowers)
{
    int zero = n - free + 1 - ST::query(free, n, 1, n, 1), start, ed;
    if (zero == 0)
    {
        start = 0;
        ed = 0;
    }
    else
    {
        start = find_zero(free, 1);
        ed = find_zero(free, min(zero, flowers));

        ST::update(start, ed, 1, 1, n, 1);
    }

    return vi{start, ed};
}

int clear(int l, int r)
{
    int ans = ST::query(l, r, 1, n, 1);
    ST::update(l, r, 0, 1, n, 1);

    return ans;
}

void solve()
{
    cin >> n >> m;
    ST::build(1, n, 1);

    while (m--)
    {
        int k, a, b;
        cin >> k >> a >> b;

        if (k == 1)
        {
            vi ans = insert(a + 1, b);
            if (ans[0] == 0)
            {
                cout << "Can not put any one." << endl;
            }
            else
            {
                cout << ans[0] - 1 << " " << ans[1] - 1 << endl;
            }
        }
        else
        {
            cout << clear(a + 1, b + 1) << endl;
        }
    }
}

int main()
{
    cin >> t;

    while (t--)
    {
        solve();
        cout << endl;
    }
}