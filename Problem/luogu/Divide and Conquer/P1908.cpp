#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vi = vector<int>;

const int MAXN = 500010;
vi diff(MAXN), help(MAXN);
int n;

ll merge(int l, int m, int r)
{
    ll ans = 0;
    for (int i = m, j = r; i >= l; i--)
    {
        while (j >= m + 1 && diff[i] <= diff[j])
        {
            j--;
        }

        ans += j - m;
    }

    int i = l, a = l, b = m + 1;
    while (a <= m && b <= r)
    {
        help[i++] = (diff[a] <= diff[b]? diff[a++]: diff[b++]);
    }

    while (a <= m)
    {
        help[i++] = diff[a++];
    }

    while (b <= r)
    {
        help[i++] = diff[b++];
    }

    for (i = l; i <= r; i++)
    {
        diff[i] = help[i];
    }

    return ans;
}

ll dfs(int l, int r)
{
    if (l == r)
    {
        return 0;
    }

    int m = l + ((r - l) >> 1);
    return dfs(l, m) + dfs(m + 1, r) + merge(l, m, r);
}

int main()
{
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        cin >> diff[i];
    }

    cout << dfs(0, n - 1) << endl;
}