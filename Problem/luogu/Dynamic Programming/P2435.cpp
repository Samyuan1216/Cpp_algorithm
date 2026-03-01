#include <bits/stdc++.h>

const int LIMIT1 = 100010, LIMIT2 = 10, MOD = 376544743;
int start[LIMIT1], end[LIMIT1], dp[LIMIT2][1 << (LIMIT2 << 1)];
int n, m, k, maxs, start_status, end_status;

int get(int s, int j)
{
    return (s >> (j << 1)) & 3;
}

int set(int s, int j, int v)
{
    return (s & (~(3 << (j << 1)))) | (v << (j << 1));
}

bool different(int a, int b)
{
    for (int i = 0; i < m; i++)
    {
        if (get(a, i) == get(b, i))
        {
            return false;
        }
    }

    return true;
}

int main()
{
    std::cin >> n >> m >> k;
    maxs = 1 << (m << 1);

    for (int i = 0; i < m; i++)
    {
        std::cin >> start[i];
    }

    for (int i = 0; i < m; i++)
    {
        std::cin >> end[i];
    }

    if (k == 2)
    {
        int ans = 1;
        if ((n & 1) == 0)
        {
            for (int i = 0; i < m; i++)
            {
                if (start[i] == end[i])
                {
                    ans = 0;
                    break;
                }
            }
        }
        else
        {
            for (int i = 0; i < m; i++)
            {
                if (start[i] != end[i])
                {
                    ans = 0;
                    break;
                }
            }
        }

        std::cout << ans << std::endl;

        return 0;
    }

    for (int i = 0; i < m; i++)
    {
        start_status = set(start_status, i, start[i]);
        end_status = set(end_status, i, end[i]);
    }

    for (int s = 0; s < maxs; s++)
    {
        dp[0][s] = (different(s, end_status)? 1: 0);
    }

    for (int i = n - 2; i >= 1; i--)
    {
        for (int s = 0; s < maxs; s++)
        {
            dp[m][s] = dp[0][s];
        }

        for (int j = m - 1; j >= 0; j--)
        {
            for (int s = 0, ans; s < maxs; s++)
            {
                ans = 0;
                for (int color = 0; color < k; color++)
                {
                    if ((j == 0 || get(s, j - 1) != color) && get(s, j) != color)
                    {
                        ans = (ans + dp[j + 1][set(s, j, color)]) % MOD;
                    }
                }

                dp[j][s] = ans;
            }
        }
    }

    std::cout << dp[0][start_status] << std::endl;
}