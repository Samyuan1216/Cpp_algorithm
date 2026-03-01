#include <bits/stdc++.h>
using namespace std;

const int MAXN = 310, MAXM = 8010;
vector<int> father(MAXN);
vector<vector<int>> edges(MAXM, vector<int>(3));
int n = 0, m = 0;

int find(int i)
{
    if (i != father[i])
    {
        father[i] = find(father[i]);
    }

    return father[i];
}

bool un(int a, int b)
{
    int ua = find(a), ub = find(b);
    if (ua != ub)
    {
        father[ua] = ub;
        return true;
    }
    else
    {
        return false;
    }
}

int main()
{
    ios::sync_with_stdio(false);

    cin >> n >> m;

    for (int i = 1; i <= n; i++)
    {
        father[i] = i;
    }

    for (int i = 0; i < m; i++)
    {
        cin >> edges[i][0] >> edges[i][1] >> edges[i][2];
    }

    sort(edges.begin(), edges.begin() + m, [](vector<int> &a, vector<int> &b)
    {
        return a[2] < b[2];
    });

    int ans = 0, edge_cnt = 0;
    for (int i = 0; i < m; i++)
    {
        if (un(edges[i][0], edges[i][1]) == true)
        {
            edge_cnt++;
            ans = max(ans, edges[i][2]);
        }

        if (edge_cnt == n - 1)
        {
            break;
        }
    }

    cout << n - 1 << " " << ans << endl;
}