// https://vjudge.net/problem/POJ-2728

#include <bits/stdc++.h>

using vi = std::vector<int>;
using vd = std::vector<double>;
using v2d = std::vector<vd>;

const int MAXN = 1010;
const double SML = 1e-6;
vi x(MAXN), y(MAXN), z(MAXN);
v2d dist(MAXN, vd(MAXN)), cost(MAXN, vd(MAXN));
vd value(MAXN);
bool visited[MAXN];
int n;

bool check(double x)
{
    for (int i = 1; i <= n; i++)
    {
        visited[i] = false;
        value[i] = cost[1][i] - x * dist[1][i];
    }

    visited[1] = true;

    double sum = 0;
    for (int i = 1; i <= n - 1; i++)
    {
        double min_dist = DBL_MAX;
        int next = 0;
        for (int j = 1; j <= n; j++)
        {
            if (!visited[j] && value[j] < min_dist)
            {
                min_dist = value[j];
                next = j;
            }
        }

        sum += min_dist;
        visited[next] = true;

        for (int j = 1; j <= n; j++)
        {
            if (!visited[j] && cost[next][j] - x * dist[next][j] < value[j])
            {
                value[j] = cost[next][j] - x * dist[next][j];
            }
        }
    }

    return sum <= 0;
}

double find()
{
    double ans = 0, l = 0, r = 100, mid;
    while (l < r && r - l >= SML)
    {
        mid = l + (r - l) / 2;
        if (check(mid))
        {
            ans = mid;
            r = mid - SML;
        }
        else
        {
            l = mid + SML;
        }
    }

    return ans;
}

int main()
{
    scanf("%d", &n);
    while (n != 0)
    {
        for (int i = 1; i <= n; i++)
        {
            scanf("%d %d %d", &x[i], &y[i], &z[i]);
        }

        for (int i = 1; i <= n; i++)
        {
            for (int j = 1; j <= n; j++)
            {
                if (i != j)
                {
                    dist[i][j] = std::sqrt(std::pow(x[i] - x[j], 2) + std::pow(y[i] - y[j], 2));
                    cost[i][j] = std::abs(z[i] - z[j]);
                }
            }
        }

        printf("%.3lf\n", find());

        scanf("%d", &n);
    }
}