// @lc code=start
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 510, MAXX = 1000010;
vector<long long> dp(MAXX), cost(MAXN), val(MAXN);
long long ans = 0, happy = 0;
int n = 0, x = 0, m = 1;

int main()
{
    cin >> n >> x;
    for (int i = 1, pre = 0, cur = 0, well = 0; i <= n; i++)
    {
        cin >> pre >> cur >> happy;

        well = pre - cur - cur;
        if (well >= 0)
        {
            x += well;
            ans += happy;
        }
        else
        {
            cost[m] = -well;
            val[m++] = happy;
        }
    }

    for (int i = 1; i <= m; i++)
    {
        for (int j = x; j >= cost[i]; j--)
        {
            dp[j] = max(dp[j], dp[j - cost[i]] + val[i]);
        }
    }

    ans += dp[x];

    cout << ans << endl;
}
// @lc code=end