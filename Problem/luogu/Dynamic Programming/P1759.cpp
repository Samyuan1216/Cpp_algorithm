#include <bits/stdc++.h>
using namespace std;

using vi = vector<int>;
using vvi = vector<vi>;
using vs = vector<string>;
using vvs = vector<vs>;

const int MAXN = 110, MAXM = 210;
vi a(MAXN), b(MAXN), c(MAXN);
vvi dp(MAXM, vi(MAXM));
vvs path(MAXM, vs(MAXM));
int n, m, v;
string p;

int main()
{
    cin >> m >> v >> n;
    for (int i = 1; i <= n; i++)
    {
        cin >> a[i] >> b[i] >> c[i];
    }

    for (int i = 1; i <= n; i++)
    {
        for (int j = m; j >= a[i]; j--)
        {
            for (int k = v; k >= b[i]; k--)
            {
                if (path[j - a[i]][k - b[i]].empty())
                {
                    p = to_string(i);
                }
                else
                {
                    p = path[j - a[i]][k - b[i]] + " " + to_string(i);
                }

                if (dp[j][k] < dp[j - a[i]][k - b[i]] + c[i])
                {
                    dp[j][k] = dp[j - a[i]][k - b[i]] + c[i];
                    path[j][k] = p;
                }
                else if (dp[j][k] == dp[j - a[i]][k - b[i]] + c[i])
                {
                    if (p < path[j][k])
                    {
                        path[j][k] = p;
                    }
                }
            }
        }
    }

    cout << dp[m][v] << endl;
    cout << path[m][v] << endl;
}