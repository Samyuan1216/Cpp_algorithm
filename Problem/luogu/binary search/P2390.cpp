#include <bits/stdc++.h>
using namespace std;

const int MAXN = 50010;
vector<int> p(MAXN);
int t = 0, n = 0;
double x = 0;

bool ok(int m)
{
    for (int l = 0, r = m; r < n; l++, r++)
    {
        if (p[r] <= 0 && abs(p[l]) <= t)
        {
            return true;
        }

        if (p[l] >= 0 && p[r] <= t)
        {
            return true;
        }

        if (min(2 * p[r] + abs(p[l]), 2 * abs(p[l]) + p[r]) <= t)
        {
            return true;
        }
    }

    return false;
}

int main()
{
    cin >> t >> n;

    for (int i = 0; i < n; i++)
    {
        cin >> p[i];
    }

    sort(p.begin(), p.begin() + n);

    int ans = 0;
    for (int l = 0, r = n - 1, m = 0; l <= r;)
    {
        m = l + ((r - l) >> 1);
        if (ok(m) == true)
        {
            ans = m + 1;
            l = m + 1;
        }
        else
        {
            r = m - 1;
        }
    }

    cout << ans << endl;
}