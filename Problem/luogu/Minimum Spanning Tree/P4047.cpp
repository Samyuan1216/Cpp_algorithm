#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1010, MAXM = 1000010;
vector<vector<int>> points(MAXN, vector<int>(2));
vector<tuple<int, int, double>> edges(MAXM);
vector<int> father(MAXN);
int n = 0, k = 0, x = 0, y = 0, s = 0, cnt = 0;

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
    int ua = find(a), ub = find(b);
    if (ua != ub)
    {
        father[ua] = ub;
        s--;
    }
}

double dis(vector<int> &a, vector<int> &b)
{
    return sqrt(pow(a[0] - b[0], 2) + pow(a[1] - b[1], 2));
}

int main()
{
    scanf("%d %d", &n, &k);
    s = n;

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
            get<2>(edges[cnt++]) = dis(points[i], points[j]);
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

    int i = 0;
    for (i; i < cnt && s > k; i++)
    {
        if (same_set(get<0>(edges[i]), get<1>(edges[i])) == false)
        {
            un(get<0>(edges[i]), get<1>(edges[i]));
        }
    }

    for (i; same_set(get<0>(edges[i]), get<1>(edges[i])) == true; i++);

    printf("%.2f\n", get<2>(edges[i]));
}