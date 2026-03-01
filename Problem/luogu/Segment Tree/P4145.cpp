#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vll = vector<ll>;

const int MAXN = 100010;
vll diff(MAXN);
int n, m, op, a, b;

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
            sum[i] = diff[l];
            maxa[i] = diff[l];
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

    void sq(int &jobl, int &jobr, int l, int r, int i)
    {
        if (maxa[i] != 1)
        {
            if (l == r)
            {
                sum[i] = sqrt(sum[i]);
                maxa[i] = sum[i];
            }
            else
            {
                int mid = l + ((r - l) >> 1);

                if (jobl <= mid)
                {
                    sq(jobl, jobr, l, mid, i << 1);
                }

                if (jobr >= mid + 1)
                {
                    sq(jobl, jobr, mid + 1, r, i << 1 | 1);
                }

                up(i);
            }
        }
    }
}

int main()
{
    cin >> n;
    for (int i = 1; i <= n; i++)
    {
        cin >> diff[i];
    }

    ST::build(1, n, 1);

    cin >> m;
    while (m--)
    {
        cin >> op >> a >> b;
        
        int l = min(a, b), r = max(a, b);
        if (op == 0)
        {
            ST::sq(l, r, 1, n, 1);
        }
        else
        {
            cout << ST::query(l, r, 1, n, 1) << endl;
        }
    }
}