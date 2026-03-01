#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vll = vector<ll>;

const long long MAXN = 100010;
long long n, m;

namespace BIT
{
    vll info1(MAXN), info2(MAXN);

    long long lowbit(long long i)
    {
        return i & -i;
    }

    void add(vll &tree, long long i, long long v)
    {
        while (i <= n)
        {
            tree[i] += v;
            i += lowbit(i);
        }
    }

    void add(long long l, long long r, long long v)
    {
        add(info1, l, v);
        add(info1, r + 1, -v);
        add(info2, l, (l - 1) * v);
        add(info2, r + 1, -r * v);
    }

    ll sum(vll &tree, long long i)
    {
        ll ans = 0;
        while (i > 0)
        {
            ans += tree[i];
            i -= lowbit(i);
        }

        return ans;
    }

    ll query(long long l, long long r)
    {
        return (sum(info1, r) * r - sum(info2, r)) - (sum(info1, l - 1) * (l - 1) - sum(info2, l - 1));
    }
}

int main()
{
    cin >> n >> m;
    for (long long i = 1, x; i <= n; i++)
    {
        cin >> x;
        BIT::add(i, i, x);
    }

    for (long long i = 1, a, x, y, k; i <= m; i++)
    {
        cin >> a;
        if (a == 1)
        {
            cin >> x >> y >> k;
            BIT::add(x, y, k);
        }
        else
        {
            cin >> x >> y;
            cout << BIT::query(x, y) << endl;
        }
    }
}