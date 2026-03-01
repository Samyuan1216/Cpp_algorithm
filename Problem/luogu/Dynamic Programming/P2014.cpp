#include <bits/stdc++.h>
using namespace std;

// 最优解
using vi = vector<int>;
using vvi = vector<vector<int>>;

const int MAXN = 310;
vi head(MAXN), ne(MAXN), to(MAXN), nums(MAXN), val(MAXN), siz(MAXN);
vvi dp(MAXN + 2, vi(MAXN));
int edge_cnt = 1, dfn_cnt, n, m;

int f(int u)
{
    int i = ++dfn_cnt;
    val[i] = nums[u];
    siz[i] = 1;

    for (int j = head[u]; j > 0; j = ne[j])
    {
        siz[i] += f(to[j]);
    }

    return siz[i];
}

int main()
{
    cin >> n >> m;
    for (int i = 1, pre; i <= n; i++)
    {
        cin >> pre >> nums[i];

        ne[edge_cnt] = head[pre];
        to[edge_cnt] = i;
        head[pre] = edge_cnt++;
    }

    f(0);

    for (int i = n + 1; i >= 2; i--)
    {
        for (int j = 1; j <= m; j++)
        {
            dp[i][j] = max(dp[i + siz[i]][j], dp[i + 1][j - 1] + val[i]);
        }
    }

    cout << dp[2][m] << endl;
}

// 普通解
// using vi = vector<int>;
// using vvi = vector<vector<int>>;
// using vvvi = vector<vector<vector<int>>>;

// const int MAXN = 310;
// vi nums(MAXN);
// vvi graph(MAXN, vi());
// vvvi dp(MAXN);
// int n, m;

// int f(int i, int j, int k)
// {
//     if (k == 0)
//     {
//         return 0;
//     }

//     if (j == 0 || k == 1)
//     {
//         return nums[i];
//     }

//     if (dp[i][j][k] != -1)
//     {
//         return dp[i][j][k];
//     }

//     int ans = f(i, j - 1, k);

//     int v = graph[i][j - 1];
//     for (int s = 1; s < k; s++)
//     {
//         ans = max(ans, f(i, j - 1, k - s) + f(v, graph[v].size(), s));
//     }

//     dp[i][j][k] = ans;
//     return ans;
// }

// int main()
// {
//     cin >> n >> m;
//     m++;

//     for (int i = 1, pre; i <= n; i++)
//     {
//         cin >> pre >> nums[i];
//         graph[pre].push_back(i);
//     }

//     for (int i = 0; i <= n; i++)
//     {
//         dp[i] = vvi(graph[i].size() + 1, vi(m + 1, -1));
//     }

//     cout << f(0, graph[0].size(), m) << endl;
// }