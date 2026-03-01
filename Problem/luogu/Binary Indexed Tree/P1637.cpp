#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vll = vector<ll>;

const int MAXN = 30010, MAXM = 100010;
vll diff(MAXN);
ll n, m;

namespace BIT
{
    vll up1(MAXM), up2(MAXM);

    int lowbit(int i)
    {
        return i & -i;
    }

    void add(vll &tree, int i, int v)
    {
        while (i <= m)
        {
            tree[i] += v;
            i += lowbit(i);
        }
    }

    ll sum(vll &tree, int i)
    {
        ll ans = 0;
        while (i > 0)
        {
            ans += tree[i];
            i -= lowbit(i);
        }

        return ans;
    }

    ll query(int i)
    {
        add(up1, i, 1);
        add(up2, i, sum(up1, i - 1));
        return sum(up2, i - 1);
    }
}

int main()
{
    cin >> n;
    for (int i = 1; i <= n; i++)
    {
        cin >> diff[i];
        m = max(m, diff[i]);
    }

    ll ans = 0;
    for (int i = 1; i <= n; i++)
    {
        ans += BIT::query(diff[i]);
    }

    cout << ans << endl;
}