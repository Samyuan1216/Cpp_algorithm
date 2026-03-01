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
    vll sum(MAXN << 2), maxa(MAXN << 2), sem(MAXN << 2), max_add(MAXN << 2), other_add(MAXN << 2);
    vi cnt(MAXN << 2);

    void lazy(int i, int n, ll max_add_v, ll other_add_v)
    {
        sum[i] += max_add_v * cnt[i] + other_add_v * (n - cnt[i]);
        maxa[i] += max_add_v;
        sem[i] += (sem[i] == LOWEST? 0: other_add_v);

        max_add[i] += max_add_v;
        other_add[i] += other_add_v;
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

    void down(int i, int ln, int rn)
    {
        int l = i << 1, r = i << 1 | 1;
        ll tmp = max(maxa[l], maxa[r]);

        if (tmp == maxa[l])
        {
            lazy(l, ln, max_add[i], other_add[i]);
        }
        else
        {
            lazy(l, ln, other_add[i], other_add[i]);
        }

        if (tmp == maxa[r])
        {
            lazy(r, rn, max_add[i], other_add[i]);
        }
        else
        {
            lazy(r, rn, other_add[i], other_add[i]);
        }

        max_add[i] = 0;
        other_add[i] = 0;
    }

    void build(int l, int r, int i)
    {
        if (l == r)
        {
            sum[i] = maxa[i] = arr[l];
            cnt[i] = 1;
            sem[i] = LOWEST;
        }
        else
        {
            int mid = l + ((r - l) >> 1);
            build(l, mid, i << 1);
            build(mid + 1, r, i << 1 | 1);

            up(i);
        }

        max_add[i] = 0;
        other_add[i] = 0;
    }

    void add(int jobl, int jobr, ll jobv, int l, int r, int i)
    {
        if (l >= jobl && r <= jobr)
        {
            lazy(i, r - l + 1, jobv, jobv);
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
            lazy(i, r - l + 1, jobv - maxa[i], 0);
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
        else
        {
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
    }
}

random_device rd;
mt19937 gen(rd());
uniform_real_distribution dis(0.0, 1.0);

void random_array(int n, int v)
{
    for (int i = 1; i <= n; i++)
    {
        arr[i] = dis(gen) * 2 * v - v;
    }
}

void check_add(vll &check, int jobl, int jobr, ll jobv)
{
    for (int i = jobl; i <= jobr; i++)
    {
        check[i] += jobv;
    }
}

void check_set_min(vll &check, int jobl, int jobr, ll jobv)
{
    for (int i = jobl; i <= jobr; i++)
    {
        check[i] = min(check[i], jobv);
    }
}

ll check_query_sum(vll &check, int jobl, int jobr)
{
    ll ans = 0;
    for (int i = jobl; i <= jobr; i++)
    {
        ans += check[i];
    }

    return ans;
}

ll check_query_max(vll &check, int jobl, int jobr)
{
    ll ans = INT64_MIN;
    for (int i = jobl; i <= jobr; i++)
    {
        ans = max(ans, check[i]);
    }

    return ans;
}

int main()
{
    int n = 2000, v = 5000, t = 1000000;
    random_array(n, v);

    vll check(n + 1);
    for (int i = 1; i <= n; i++)
    {
        check[i] = arr[i];
    }

    ST::build(1, n, 1);

    cout << "测试开始" << endl;
    for (int i = 1, op, a, b, jobl, jobr, jobv; i <= t; i++)
    {
        op = dis(gen) * 4;
        a = dis(gen) * n + 1;
        b = dis(gen) * n + 1;

        jobl = min(a, b);
        jobr = max(a, b);

        if (op == 0)
        {
            jobv = dis(gen) * v * 2 - v;

            ST::add(jobl, jobr, (ll)jobv, 1, n, 1);
            check_add(check, jobl, jobr, (ll)jobv);
        }
        else if (op == 1)
        {
            jobv = dis(gen) * v * 2 - v;

            ST::set_min(jobl, jobr, (ll)jobv, 1, n, 1);
            check_set_min(check, jobl, jobr, (ll)jobv);
        }
        else if (op == 2)
        {
            ll ans1 = ST::query_max(jobl, jobr, 1, n, 1);
            ll ans2 = check_query_max(check, jobl, jobr);

            if (ans1 != ans2)
            {
                cout << "出错了" << endl;
                break;
            }
        }
        else
        {
            ll ans1 = ST::query_sum(jobl, jobr, 1, n, 1);
            ll ans2 = check_query_sum(check, jobl, jobr);

            if (ans1 != ans2)
            {
                cout << "出错了" << endl;
                break;
            }
        }
    }
    cout << "测试结束" << endl;
}