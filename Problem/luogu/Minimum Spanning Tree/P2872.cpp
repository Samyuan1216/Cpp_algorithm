#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1010, MAXM = 2000010;
vector<vector<int>> points(MAXN, vector<int>(2));
vector<tuple<int, int, double>> edges(MAXM);
vector<int> father(MAXN);
int cnt = 0, n = 0, m = 0, u = 0, v = 0;
double ans = 0;

int find(int i)
{
    if (i != father[i])
    {
        father[i] = find(father[i]);
    }

    return father[i];
}

bool same_set(int a, int b)
{
    return find(a) == find(b);
}

void un(int a, int b)
{
    father[find(a)] = find(b);
}

double dis(int a, int b, int x, int y)
{
    return sqrt(pow(a - x, 2) + pow(b - y, 2));
}

int main()
{
    scanf("%d %d", &n, &m);

    for (int i = 1; i <= n; i++)
    {
        scanf("%d %d", &points[i][0], &points[i][1]);
    }

    for (int i = 1; i <= n; i++)
    {
        for (int j = i + 1; j <= n; j++)
        {
            get<0>(edges[cnt]) = i;
            get<1>(edges[cnt]) = j;
            get<2>(edges[cnt++]) = dis(points[i][0], points[i][1], points[j][0], points[j][1]);
        }
    }

    sort(edges.begin(), edges.begin() + cnt, [](tuple<int, int, double> &a, tuple<int, int, double> &b)
    {
        return get<2>(a) < get<2>(b);
    });

    for (int i = 1; i <= n; i++)
    {
        father[i] = i;
    }

    for (int i = 1; i <= m; i++)
    {
        cin >> u >> v;
        un(u, v);
    }

    for (int i = 0; i < cnt; i++)
    {
        if (same_set(get<0>(edges[i]), get<1>(edges[i])) == false)
        {
            un(get<0>(edges[i]), get<1>(edges[i]));
            ans += get<2>(edges[i]);
        }
    }

    printf("%.2f", ans);
}