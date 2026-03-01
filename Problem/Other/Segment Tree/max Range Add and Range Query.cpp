#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vll = vector<ll>;

const int MAXN = 100010;
vll diff(MAXN);

namespace ST
{
    vll maxa(MAXN << 2), ad(MAXN << 2);

    void lazy(int i, ll v)
    {
        maxa[i] += v;
        ad[i] += v;
    }

    void up(int i)
    {
        maxa[i] = max(maxa[i << 1], maxa[i << 1 | 1]);
    }

    void down(int i)
    {
        if (ad[i] != 0)
        {
            lazy(i << 1, ad[i]);
            lazy(i << 1 | 1, ad[i]);

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
            int m = l + ((r - l) >> 1);
            build(l, m, i << 1);
            build(m + 1, r, i << 1 | 1);

            up(i);
        }

        ad[i] = 0;
    }

    ll query(int &jobl, int &jobr, int l, int r, int i)
    {
        if (l >= jobl && r <= jobr)
        {
            return maxa[i];
        }
        
        down(i);

        ll ans = INT64_MIN;
        int m = l + ((r - l) >> 1);
        if (jobl <= m)
        {
            ans = max(ans, query(jobl, jobr, l, m, i << 1));
        }

        if (jobr >= m + 1)
        {
            ans = max(ans, query(jobl, jobr, m + 1, r, i << 1 | 1));
        }

        return ans;
    }

    void add(int &jobl, int &jobr, ll &jobv, int l, int r, int i)
    {
        if (l >= jobl && r <= jobr)
        {
            lazy(i, jobv);
        }
        else
        {
            down(i);

            int m = l + ((r - l) >> 1);
            if (jobl <= m)
            {
                add(jobl, jobr, jobv, l, m, i << 1);
            }

            if (jobr >= m + 1)
            {
                add(jobl, jobr, jobv, m + 1, r, i << 1 | 1);
            }

            up(i);
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
        diff[i] = dis(gen) * v;
    }
}

ll check_query(vll &check, int jobl, int jobr)
{
    ll ans = INT64_MIN;
    for (int i = jobl; i <= jobr; i++)
    {
        ans = max(ans, check[i]);
    }

    return ans;
}

void check_add(vll &check, int jobl, int jobr, ll jobv)
{
    for (int i = jobl; i <= jobr; i++)
    {
        check[i] += jobv;
    }
}

int main()
{
    int n = 1000, v = 2000, t = 5000000;
    random_array(n, v);
    ST::build(1, n, 1);

    vll check(n + 1);
    for (int i = 1; i <= n; i++)
    {
        check[i] = diff[i];
    }

    cout << "测试开始" << endl;
    for (int i = 1; i <= t; i++)
    {
        int op = dis(gen) * 2, a = dis(gen) * n + 1, b = dis(gen) * n + 1;
        int jobl = min(a, b), jobr = max(a, b);

        if (op == 0)
        {
            ll jobv = dis(gen) * 2 * v - v;
            
            ST::add(jobl, jobr, jobv, 1, n, 1);
            check_add(check, jobl, jobr, jobv);
        }
        else
        {
            ll ans1 = ST::query(jobl, jobr, 1, n, 1), ans2 = check_query(check, jobl, jobr);
            if (ans1 != ans2)
            {
                cout << "出错了！" << endl;
                break;
            }
        }
    }
    cout << "测试结束" << endl;
}