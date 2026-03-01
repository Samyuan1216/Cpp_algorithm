#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vi = vector<int>;
using vll = vector<ll>;

const int MAXN = 500010;
const ll LOWEST = INT64_MIN;
vi arr(MAXN);

namespace ST
{
    vi cnt(MAXN << 2);
    vll sum(MAXN << 2);
    vll maxa(MAXN << 2), sem(MAXN << 2), max_add(MAXN << 2), other_add(MAXN << 2);
    vll max_history(MAXN << 2), max_add_top(MAXN << 2), other_add_top(MAXN << 2);

    void lazy(int i, int n, ll max_add_v, ll other_add_v, ll max_up_v, ll other_up_v)
    {
        max_history[i] = max(max_history[i], maxa[i] + max_up_v);
        max_add_top[i] = max(max_add_top[i], max_add[i] + max_up_v);
        other_add_top[i] = max(other_add_top[i], other_add[i] + other_up_v);

        sum[i] += max_add_v * cnt[i] + other_add_v * (n - cnt[i]);
        maxa[i] += max_add_v;
        sem[i] += (sem[i] == LOWEST? 0: other_add_v);

        max_add[i] += max_add_v;
        other_add[i] += other_add_v;
    }

    void up(int i)
    {
        int l = i << 1, r = i << 1 | 1;
        max_history[i] = max(max_history[l], max_history[r]);
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

    void down(int i, int ln, int rn)
    {
        int l = i << 1, r = i << 1 | 1;

        ll tmp = max(maxa[l], maxa[r]);
        if (tmp == maxa[l])
        {
            lazy(l, ln, max_add[i], other_add[i], max_add_top[i], other_add_top[i]);
        }
        else
        {
            lazy(l, ln, other_add[i], other_add[i], other_add_top[i], other_add_top[i]);
        }

        if (tmp == maxa[r])
        {
            lazy(r, rn, max_add[i], other_add[i], max_add_top[i], other_add_top[i]);
        }
        else
        {
            lazy(r, rn, other_add[i], other_add[i], other_add_top[i], other_add_top[i]);
        }

        max_add[i] = other_add[i] = max_add_top[i] = other_add_top[i] = 0;
    }

    void build(int l, int r, int i)
    {
        if (l == r)
        {
            sum[i] = maxa[i] = max_history[i] = arr[l];
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

        max_add[i] = other_add[i] = max_add_top[i] = other_add_top[i] = 0;
    }

    void add(int jobl, int jobr, ll jobv, int l, int r, int i)
    {
        if (l >= jobl && r <= jobr)
        {
            lazy(i, r - l + 1, jobv, jobv, jobv, jobv);
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

    void set_min(int jobl, int jobr, ll jobv, int l, int r, int i)
    {
        if (jobv >= maxa[i])
        {
            return;
        }

        if (l >= jobl && r <= jobr && jobv > sem[i])
        {
            lazy(i, r - l + 1, jobv - maxa[i], 0, jobv - maxa[i], 0);
        }
        else
        {
            int mid = l + ((r - l) >> 1);
            down(i, mid - l + 1, r - mid);

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

    ll query_sum(int jobl, int jobr, int l, int r, int i)
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
            ans += query_sum(jobl, jobr, l, mid, i << 1);
        }

        if (jobr >= mid + 1)
        {
            ans += query_sum(jobl, jobr, mid + 1, r, i << 1 | 1);
        }

        return ans;
    }

    ll query_max(int jobl, int jobr, int l, int r, int i)
    {
        if (l >= jobl && r <= jobr)
        {
            return maxa[i];
        }

        int mid = l + ((r - l) >> 1);
        down(i, mid - l + 1, r - mid);

        ll ans = INT64_MIN;
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

    ll query_history_max(int jobl, int jobr, int l, int r, int i)
    {
        if (l >= jobl && r <= jobr)
        {
            return max_history[i];
        }

        int mid = l + ((r - l) >> 1);
        down(i, mid - l + 1, r - mid);

        ll ans = INT64_MIN;
        if (jobl <= mid)
        {
            ans = max(ans, query_history_max(jobl, jobr, l, mid, i << 1));
        }

        if (jobr >= mid + 1)
        {
            ans = max(ans, query_history_max(jobl, jobr, mid + 1, r, i << 1 | 1));
        }

        return ans;
    }
}

int n, m, op, l, r;
ll x;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    for (int i = 1; i <= n; i++)
    {
        cin >> arr[i];
    }

    ST::build(1, n, 1);

    while (m--)
    {
        cin >> op;
        if (op == 1)
        {
            cin >> l >> r >> x;

            ST::add(l, r, x, 1, n, 1);
        }
        else if (op == 2)
        {
            cin >> l >> r >> x;

            ST::set_min(l, r, x, 1, n, 1);
        }
        else if (op == 3)
        {
            cin >> l >> r;
            cout << ST::query_sum(l, r, 1, n, 1) << endl;
        }
        else if (op == 4)
        {
            cin >> l >> r;
            cout << ST::query_max(l, r, 1, n, 1) << endl;
        }
        else
        {
            cin >> l >> r;
            cout << ST::query_history_max(l, r, 1, n, 1) << endl;
        }
    }
}