#include <bits/stdc++.h>
using namespace std;

using vi = vector<int>;

const int MAXN = 1010;
vi dp(MAXN), w(MAXN), v(MAXN);
int n, p, s, maxw, ans = -1;

bool check(int m)
{
    fill(dp.begin(), dp.end(), 0);

    for (int i = 0; i < n; i++)
    {
        if (w[i] <= m)
        {
            for (int j = s; j >= w[i]; j--)
            {
                dp[j] = max(dp[j], dp[j - w[i]] + v[i]);
            }
        }
    }

    return dp[s] >= p;
}

int main()
{
    cin >> n >> p >> s;
    for (int i = 0; i < n; i++)
    {
        cin >> w[i] >> v[i];
        maxw = max(maxw, w[i]);
    }

    for (int l = 0, r = maxw, m; l <= r;)
    {
        m = l + ((r - l) >> 1);
        if (check(m))
        {
            ans = m;
            r = m - 1;
        }
        else
        {
            l = m + 1;
        }
    }

    if (ans != -1)
    {
        cout << ans << endl;
    }
    else
    {
        cout << "No Solution!" << endl;
    }
}