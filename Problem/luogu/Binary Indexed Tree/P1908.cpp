#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vi = vector<int>;

const int MAXN = 500010;
vi diff(MAXN), arr_s(MAXN);
int n, m;

namespace BIT
{
    vi tree(MAXN);

    int lowbit(int i)
    {
        return i & -i;
    }

    void add(int i)
    {
        while (i <= m)
        {
            tree[i]++;
            i += lowbit(i);
        }
    }

    ll query(int i)
    {
        ll ans = 0;
        while (i > 0)
        {
            ans += tree[i];
            i -= lowbit(i);
        }

        return ans;
    }
}

int fin(int v)
{
    int ans = 0;
    for (int l = 1, r = m, mid; l <= r;)
    {
        mid = l + ((r - l) >> 1);
        if (arr_s[mid] <= v)
        {
            ans = mid;
            l = mid + 1;
        }
        else
        {
            r = mid - 1;
        }
    }

    return ans;
}

int main()
{
    cin >> n;
    for (int i = 1; i <= n; i++)
    {
        cin >> diff[i];
        arr_s[i] = diff[i];
    }

    sort(arr_s.begin() + 1, arr_s.begin() + n);
    m = unique(arr_s.begin() + 1, arr_s.begin() + n) - arr_s.begin();

    for (int i = 1; i <= n; i++)
    {
        diff[i] = fin(diff[i]);
    }

    ll ans = 0;
    for (int i = n; i >= 1; i--)
    {
        ans += BIT::query(diff[i] - 1);
        BIT::add(diff[i]);
    }

    cout << ans << endl;
}