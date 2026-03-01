#include <bits/stdc++.h>
using namespace std;

const int LIMIT = 100000;
vector<long long> dp(LIMIT + 1);
vector<int> value(4), cnt(4);
int n = 0, s = 0;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    cin >> value[0] >> value[1] >> value[2] >> value[3];
    cin >> n;

    dp[0] = 1;
    for (int i = 0; i <= 3; i++)
    {
        for (int j = value[i]; j <= LIMIT; j++)
        {
            dp[j] += dp[j - value[i]];
        }
    }

    for (int i = 1; i <= n; i++)
    {
        cin >> cnt[0] >> cnt[1] >> cnt[2] >> cnt[3];
        cin >> s;

        long long illegal = 0;
        for (int status = 1; status <= 15; status++)
        {
            long long t = s;
            int sign = -1;

            for (int j = 0; j <= 3; j++)
            {
                if (((status >> j) & 1) == 1)
                {
                    t -= value[j] * (cnt[j] + 1);
                    sign = -sign;
                }
            }

            if (t >= 0)
            {
                illegal += dp[t] * sign;
            }
        }

        cout << dp[s] - illegal << endl;
    }
}