#include <bits/stdc++.h>
using namespace std;

const int MAXN = 100010, MAXW = 1010, ENOUGH = 1010;
vector<int> v(MAXN), w(MAXN), dp(MAXW);
int hour1 = 0, minute1 = 0, hour2 = 0, minute2 = 0, t = 0, n = 0, m = 0;

int main()
{
    scanf("%d:%d %d:%d %d", &hour1, &minute1, &hour2, &minute2, &n);

    if (minute1 > minute2)
    {
        hour2--;
        minute2 += 60;
    }
    t = (hour2 - hour1) * 60 + minute2 - minute1;

    for (int i = 1, cost = 0, val = 0, cnt = 0; i <= n; i++)
    {
        cin >> cost >> val >> cnt;
        if (cnt == 0)
        {
            cnt = ENOUGH;
        }

        for (int k = 1; k <= cnt; k <<= 1)
        {
            v[++m] = k * val;
            w[m] = k * cost;
            cnt -= k;
        }

        if (cnt > 0)
        {
            v[++m] = cnt * val;
            w[m] = cnt * cost;
        }
    }

    for (int i = 1; i <= m; i++)
    {
        for (int j = t; j >= w[i]; j--)
        {
            dp[j] = max(dp[j], dp[j - w[i]] + v[i]);
        }
    }

    printf("%d\n", dp[t]);
}