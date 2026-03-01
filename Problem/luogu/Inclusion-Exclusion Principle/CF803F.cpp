#include <bits/stdc++.h>
using namespace std;

const int MOD = 1000000007, LIMIT = 100010;
vector<long long> dp(LIMIT), cnt(LIMIT), pow2(LIMIT);
int n = 0, a = 0;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    pow2[0] = 1;
    for (int i = 1; i < LIMIT; i++)
    {
        pow2[i] = (pow2[i - 1] * 2) % MOD;
    }

    cin >> n;
    for (int i = 0; i < n; i++)
    {
        cin >> a;
        cnt[a]++;
    }

    for (int i = LIMIT - 1; i >= 1; i--)
    {
        long long count = 0;
        for (int j = i; j < LIMIT; j += i)
        {
            count += cnt[j];
        }

        dp[i] = (pow2[count] - 1 + MOD) % MOD;
        for (int j = i * 2; j < LIMIT; j += i)
        {
            dp[i] = (dp[i] - dp[j] + MOD) % MOD;
        }
    }

    cout << dp[1] << endl;
}