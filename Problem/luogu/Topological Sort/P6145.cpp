#include <bits/stdc++.h>
using namespace std;

int main()
{
    ios::sync_with_stdio(false);

    int N = 0, M = 0, C = 0;
    cin >> N >> M >> C;

    vector<int> limits(N + 1);
    for (int i = 1; i <= N; i++)
    {
        cin >> limits[i];
    }

    vector<int> head(N + 1), next(C + 1), to(C + 1), weight(C + 1), indegree(N + 1);
    int cnt = 1;
    for (int i = 0; i < C; i++)
    {
        int a = 0, b = 0, x = 0;
        cin >> a >> b >> x;

        next[cnt] = head[a];
        to[cnt] = b;
        weight[cnt] = x;
        head[a] = cnt++;

        indegree[b]++;
    }

    vector<int> q(N + 1);
    int l = 0, r = 0;
    for (int i = 1; i <= N; i++)
    {
        if (indegree[i] == 0)
        {
            q[r++] = i;
        }
    }

    while (l < r)
    {
        int cur = q[l++];

        for (int i = head[cur]; i > 0; i = next[i])
        {
            limits[to[i]] = max(limits[to[i]], limits[cur] + weight[i]);

            indegree[to[i]]--;
            if (indegree[to[i]] == 0)
            {
                q[r++] = to[i];
            }
        }
    }

    for (int i = 1; i <= N; i++)
    {
        cout << limits[i] << endl;
    }
}