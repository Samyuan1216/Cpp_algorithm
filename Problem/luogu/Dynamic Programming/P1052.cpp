#include <bits/stdc++.h>

const int MAXN = 110, MAXL = 100010;
int arr[MAXN], where[MAXN], dp[MAXL];
bool stone[MAXL];
int n, s, t, m, ans, safe = 210;

int main()
{
    std::cin >> n >> s >> t >> m;
    for (int i = 1; i <= m; i++)
    {
        std::cin >> arr[i];
    }

    std::sort(arr + 1, arr + m + 1);
    
    if (s == t)
    {
        ans = 0;
        for (int i = 1; i <= m; i++)
        {
            if (arr[i] % s == 0)
            {
                ans++;
            }
        }
    }
    else
    {
        for (int i = 1; i <= m; i++)
        {
            where[i] = where[i - 1] + std::min(arr[i] - arr[i - 1], safe);
            stone[where[i]] = true;
        }

        n = where[m] + safe;
        std::fill(dp + 1, dp + n + 1, MAXN);

        for (int i = 1; i <= n; i++)
        {
            for (int j = std::max(i - t, 0); j <= i - s; j++)
            {
                dp[i] = std::min(dp[i], dp[j] + (stone[i]? 1: 0));
            }
        }

        ans = MAXN;
        for (int i = where[m] + 1; i <= n; i++)
        {
            ans = std::min(ans, dp[i]);
        }
    }

    std::cout << ans << std::endl;
}