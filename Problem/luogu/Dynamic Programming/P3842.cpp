#include <bits/stdc++.h>
using namespace std;

int main()
{
    ios::sync_with_stdio(false);

    int n = 0;
    cin >> n;

    vector<pair<int, int>> mp(n);
    for (auto &p: mp)
    {
        cin >> p.first >> p.second;
        p.first--;
        p.second--;
    }

    vector<vector<int>> dp(n, vector<int>(2));
    dp[0][0] = 2 * mp[0].second - mp[0].first;
    dp[0][1] = mp[0].second;

    for (int i = 1; i < n; i++)
    {
        dp[i][0] = min(dp[i - 1][0] + mp[i].second - mp[i].first + abs(mp[i].second - mp[i - 1].first), dp[i - 1][1] + mp[i].second - mp[i].first + abs(mp[i].second - mp[i - 1].second)) + 1;
        dp[i][1] = min(dp[i - 1][0] + mp[i].second - mp[i].first + abs(mp[i].first - mp[i - 1].first), dp[i - 1][1] + mp[i].second - mp[i].first + abs(mp[i].first - mp[i - 1].second)) + 1;
    }

    cout << min(dp[n - 1][0] + n - mp[n - 1].first, dp[n - 1][1] + n - mp[n - 1].second) - 1 << endl;
}