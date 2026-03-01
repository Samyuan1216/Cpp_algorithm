#include <bits/stdc++.h>
using namespace std;

using vi = vector<int>;

const int MAXN = 100010;
vi diff(MAXN), dp(MAXN, -1), eds(MAXN), ans(MAXN, INT32_MAX);
int n, len = -1;

int main()
{
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        cin >> diff[i];
    }

    for (int i = n - 1; i >= 0; i--)
    {
        if (len == -1 || diff[i] < eds[len])
        {
            eds[++len] = diff[i];
            dp[i] = len;
        }
        else
        {
            int index = len;
            for (int l = 0, r = len - 1, m; l <= r;)
            {
                m = l + ((r - l) >> 1);
                if (eds[m] <= diff[i])
                {
                    index = m;
                    r = m - 1;
                }
                else
                {
                    l = m + 1;
                }
            }

            eds[index] = diff[i];
            dp[i] = index;
        }
    }

    for (int i = 0; i < n; i++)
    {
        if (dp[i] == len)
        {
            ans[0] = diff[i];
        }
        else
        {
            if (ans[len - dp[i] - 1] < diff[i])
            {
                ans[len - dp[i]] = diff[i];
            }
        }
    }

    for (int i = 0; i <= len; i++)
    {
        cout << ans[i] << " \n"[i == len];
    }
}