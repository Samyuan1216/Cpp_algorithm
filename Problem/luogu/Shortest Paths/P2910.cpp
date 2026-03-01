#include <bits/stdc++.h>
using namespace std;

const int MAXN = 110, MAXM = 10010;
vector<vector<int>> dis(MAXN, vector<int>(MAXN));
vector<int> path(MAXM);
int n = 0, m = 0, ans = 0;

void floyd()
{
    for (int bridge = 1; bridge <= n; bridge++)
    {
        for (int i = 1; i <= n; i++)
        {
            for (int j = 1; j <= n; j++)
            {
                if (dis[i][j] > dis[i][bridge] + dis[bridge][j])
                {
                    dis[i][j] = dis[i][bridge] + dis[bridge][j];
                }
            }
        }
    }
}

int main()
{
    ios::sync_with_stdio(false);

    cin >> n >> m;
    
    for (int i = 0; i < m; i++)
    {
        cin >> path[i];
    }

    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            cin >> dis[i][j];
        }
    }

    floyd();

    for (int i = 1; i < m; i++)
    {
        ans += dis[path[i - 1]][path[i]];
    }

    cout << ans << endl;
}