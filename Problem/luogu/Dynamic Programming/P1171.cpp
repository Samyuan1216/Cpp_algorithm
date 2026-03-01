#include <bits/stdc++.h>
using namespace std;

using vi = vector<int>;
using vvi = vector<vector<int>>;

const int MAXN = 20;
vvi graph(MAXN, vi(MAXN)), dp(1 << MAXN, vi(MAXN, -1));
int n;

int dfs(int s, int i)
{
    if (s == (1 << n) - 1)
    {
        return graph[i][0];
    }

    if (dp[s][i] != -1)
    {
        return dp[s][i];
    }

    int ans = INT32_MAX;
    for (int j = 0; j < n; j++)
    {
        if ((s & (1 << j)) == 0)
        {
            ans = min(ans, graph[i][j] + dfs(s | (1 << j), j));
        }
    }

    dp[s][i] = ans;
    return ans;
}

int main()
{
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cin >> graph[i][j];
        }
    }

    cout << dfs(1, 0) << endl;
}