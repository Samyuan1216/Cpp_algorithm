#include <bits/stdc++.h>

using vi = std::vector<int>;
using vd = std::vector<double>;
using v2d = std::vector<vd>;

const int MAXN = 3010, LIMIT = 10000;
const double NA = -1e9, SML = 1e-6;
vi head(MAXN), next(MAXN), to(MAXN), cost(MAXN), strength(MAXN), dfn(MAXN), size(MAXN);
v2d dp(MAXN, vd(MAXN));
vd value(MAXN);
int k, n, dfn_cnt, edge_cnt = 1;

void add_edge(int u, int v)
{
    next[edge_cnt] = head[u];
    to[edge_cnt] = v;
    head[u] = edge_cnt++;
}

int dfs(int u)
{
    int i = ++dfn_cnt;
    dfn[u] = i;
    size[i] = 1;

    for (int ei = head[u], v; ei > 0; ei = next[ei])
    {
        v = to[ei];
        size[i] += dfs(v);
    }

    return size[i];
}

bool check(double x)
{
    for (int i = 0; i <= n; i++)
    {
        value[dfn[i]] = (double)strength[i] - x * cost[i];
    }

    for (int j = 1; j <= k; j++)
    {
        dp[dfn_cnt + 1][j] = NA;
    }

    for (int i = dfn_cnt; i >= 2; i--)
    {
        for (int j = 1; j <= k; j++)
        {
            dp[i][j] = std::max(dp[i + size[i]][j], dp[i + 1][j - 1] + value[i]);
        }
    }

    return dp[2][k] >= 0;
}

double find()
{
    double ans = 0, l = 0, r = LIMIT, mid;
    while (l < r && r - l >= SML)
    {
        mid = l + (r - l) / 2;
        if (check(mid))
        {
            ans = mid;
            l = mid + SML;
        }
        else
        {
            r = mid - SML;
        }
    }

    return ans;
}

int main()
{
    scanf("%d %d", &k, &n);
    for (int i = 1, u; i <= n; i++)
    {
        scanf("%d %d %d", &cost[i], &strength[i], &u);

        add_edge(u, i);
    }

    dfs(0);
    printf("%.3lf\n", find());
}