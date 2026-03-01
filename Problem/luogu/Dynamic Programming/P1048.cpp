#include <bits/stdc++.h>
using namespace std;

const int MAXT = 1010, MAXM = 110;
vector<int> dp(MAXT);
int t = 0, m = 0, a = 0, b = 0;

int main()
{
    cin >> t >> m;

    for (int i = 1; i <= m; i++)
    {
        cin >> a >> b;
        for (int j = t; j >= a; j--)
        {
            dp[j] = max(dp[j], dp[j - a] + b);
        }
    }

    cout << dp[t] << endl;
}