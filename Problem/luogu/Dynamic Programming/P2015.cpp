#include <bits/stdc++.h>
using namespace std;

using vi = vector<int>;
using vvi = vector<vi>;

const int MAXN = 110, MAXM = 2 * MAXN;
vi head(MAXN), ne(MAXM), to(MAXM), weight(MAXM), dfn(MAXN), val(MAXN), siz(MAXN);
vvi dp(MAXN, vi(MAXN));
int n, q, dfn_cnt, edge_cnt = 1;

void dfs(int u, int p, int w)
{
    int i = ++dfn_cnt;
    dfn[u] = i;
    val[i] = w;
    siz[i] = 1;

    for (int j = head[u]; j > 0; j = ne[j])
    {
        if (to[j] != p)
        {
            dfs(to[j], u, weight[j]);

            val[i] += val[dfn[to[j]]];
            siz[i] += siz[dfn[to[j]]];
        }
    }
}

int main()
{
    cin >> n >> q;
    for (int i = 0, a, b, c; i < n - 1; i++)
    {
        cin >> a >> b >> c;
        
        ne[edge_cnt] = head[a];
        to[edge_cnt] = b;
        weight[edge_cnt] = c;
        head[a] = edge_cnt++;

        ne[edge_cnt] = head[b];
        to[edge_cnt] = a;
        weight[edge_cnt] = c;
        head[b] = edge_cnt++;
    }

    dfs(1, 0, 0);

    fill(dp[dfn_cnt + 1].begin() + 1, dp[dfn_cnt + 1].end(), INT32_MAX);

    for (int i = dfn_cnt; i >= 2; i--)
    {
        for (int j = 1; j < n - q; j++)
        {
            dp[i][j] = dp[i + 1][j];
            if (j - siz[i] >= 0)
            {
                dp[i][j] = min((long long)dp[i][j], (long long)val[i] + dp[i + siz[i]][j - siz[i]]);
            }
        }
    }

    cout << val[1] - dp[2][n - q - 1] << endl;
}