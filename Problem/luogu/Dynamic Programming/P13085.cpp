#include <bits/stdc++.h>
using namespace std;

using vll = vector<long long>;
using vvll = vector<vll>;
using vvvll = vector<vvll>;

const int MAXLEN = 20;
vvvll dp(MAXLEN, vvll(11, vll(2)));
long long a, b;

void build()
{
    for (int i = 0; i < MAXLEN; i++)
    {
        for (int j = 0; j < 11; j++)
        {
            dp[i][j][0] = -1;
            dp[i][j][1] = -1;
        }
    }
}

long long dfs(long long n, long long offset, int len, int pre, int free)
{
    if (len == 0)
    {
        return 1;
    }

    if (dp[len][pre][free] != -1)
    {
        return dp[len][pre][free];
    }

    long long ans = 0;
    int cur = n / offset % 10;
    if (free == 0)
    {
        if (pre == 10)
        {
            ans += dfs(n, offset / 10, len - 1, 10, 1);
            for (int i = 1; i < cur; i++)
            {
                ans += dfs(n, offset / 10, len - 1, i, 1);
            }
            ans += dfs(n, offset / 10, len - 1, cur, 0);
        }
        else
        {
            for (int i = 0; i <= 9; i++)
            {
                if (i <= pre - 2 || i >= pre + 2)
                {
                    if (i < cur)
                    {
                        ans += dfs(n, offset / 10, len - 1, i, 1);
                    }
                    else if (i == cur)
                    {
                        ans += dfs(n, offset / 10, len - 1, cur, 0);
                    }
                }
            }
        }
    }
    else
    {
        if (pre == 10)
        {
            for (int i = 1; i <= 10; i++)
            {
                ans += dfs(n, offset / 10, len - 1, i, 1);
            }
        }
        else
        {
            for (int i = 0; i <= 9; i++)
            {
                if (i <= pre - 2 || i >= pre + 2)
                {
                    ans += dfs(n, offset / 10, len - 1, i, 1);
                }
            }
        }
    }

    dp[len][pre][free] = ans;
    return ans;
}

long long compute(long long n)
{
    if (n == 0)
    {
        return 1;
    }

    long long offset = 1, len = 1, tmp = n / 10;
    while (tmp)
    {
        len++;
        offset *= 10;
        tmp /= 10;
    }

    build();
    return dfs(n, offset, len, 10, 0);
}

int main()
{
    cin >> a >> b;
    cout << compute(b) - compute(a - 1) << endl;
}