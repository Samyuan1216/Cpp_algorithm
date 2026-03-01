#include <bits/stdc++.h>
using namespace std;

const int MAXN = 50010;
vector<vector<int>> mod(7, vector<int>(2, -1));
vector<int> sum(MAXN);
int n = 0, x = 0, ans = 0;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    cin >> n;

    mod[0][0] = 0;
    for (int i = 1; i <= n; i++)
    {
        cin >> x;
        sum[i] = (sum[i - 1] + sum[i] + x) % 7;

        if (mod[sum[i]][0] == -1)
        {
            mod[sum[i]][0] = i;
        }

        if (mod[sum[i]][1] < i)
        {
            mod[sum[i]][1] = i;
        }
    }

    for (auto &a: mod)
    {
        ans = max(ans, a[1] - a[0]);
    }

    cout << ans << endl;
}