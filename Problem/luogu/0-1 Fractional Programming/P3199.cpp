#include <bits/stdc++.h>

using vi = std::vector<int>;
using vd = std::vector<double>;

const int MAXN = 3010, MAXM = 10010;
const double MAXE = 1e7, SML = 1e-9;
vi head(MAXN), next(MAXM), to(MAXM);
vd weight(MAXM), value(MAXN);
bool path[MAXN];
int n, m, cnt = 1;

void add_edge(int u, int v, double w)
{
    next[cnt] = head[u];
    to[cnt] = v;
    weight[cnt] = w;
    head[u] = cnt++;
}

bool dfs(int u, double x)
{
    if (u == 0)
    {
        for (int i = 1; i <= n; i++)
        {
            if (dfs(i, x))
            {
                return true;
            }
        }
    }
    else
    {
        path[u] = true;
        for (int ei = head[u]; ei > 0; ei = next[ei])
        {
            int v = to[ei];
            double w = weight[ei] - x;

            if (value[u] + w < value[v])
            {
                value[v] = value[u] + w;
                if (path[v] || dfs(v, x))
                {
                    return true;
                }
            }
        }

        path[u] = false;
    }

    return false;
}

bool check(double x)
{
    std::fill(value.begin() + 1, value.begin() + n + 1, 0);
    std::fill(path + 1, path + n + 1, false);

    return dfs(0, x);
}

double find()
{
    double ans = 0, l = -MAXE, r = MAXE, mid;
    while (l < r && r - l >= SML)
    {
        mid = l + (r - l) / 2;
        if (check(mid))
        {
            r = mid - SML;
        }
        else
        {
            ans = mid;
            l = mid + SML;
        }
    }

    return ans;
}

int main()
{
    scanf("%d %d", &n, &m);
    for (int i = 1; i <= m; i++)
    {
        int u, v;
        double w;
        scanf("%d %d %lf", &u, &v, &w);

        add_edge(u, v, w);
    }

    printf("%.8lf\n", find());
}